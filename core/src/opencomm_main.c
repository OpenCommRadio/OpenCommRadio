/*
 * OpenCommRadio core
 *
 * This file is part of the OpenCommRadio project.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2025 Gwen Nelson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "hal.h"
#include "core_state.h"

/*typedef enum {
    EVENT_NONE,
    EVENT_SERIAL_DATA,
    EVENT_AT_COMMAND,
    EVENT_DATA_RECEIVED,
    EVENT_DATA_TO_SEND,
    EVENT_TX_DONE,
    EVENT_RX_START,
    EVENT_RX_END,
    EVENT_PTT_PRESS,
    EVENT_PTT_RELEASE,
    EVENT_ERROR
} fsm_event_t;*/

static char freq_str[16];

#include <stdio.h>
#include <stdint.h>

static void format_frequency(char *out, size_t out_size, uint32_t hz) {
     snprintf(out, out_size, "%u.%06u MHz", hz / 1000000, hz % 1000000);

}

static void render_state_analogue_idle() {
	hal_display_clear();
	hal_display_status_text("OPENCOMM A");
	hal_display_line(1,"VOICE MODE");
	hal_display_line(2,hal_get_channel_name(hal_get_channel()));
	format_frequency(freq_str, sizeof(freq_str), hal_get_frequency());
	hal_display_line(3,freq_str);
	hal_display_update();
}

void opencomm_main_fsm() {
     switch(oc_current_state) {
        case OC_STATE_BOOT:
		// first display all the bootup text
		hal_display_clear();
		hal_display_status_text("OPENCOMM");
		hal_display_line(1,"Booting...");
		hal_display_battery(hal_get_battery_level());
		hal_display_update();

		if(hal_get_channel_count()==0) {
			hal_load_default_codeplug();  // if no channels loaded, we need to load the default codeplug
			hal_delay_ms(250);            // and we delay 0.25s just to be sure it loads nicely, some platforms can be weird
		}

		// now we load the default channel (0)
		oc_cur_chan_no = 0;
		oc_cur_chan_name = hal_get_channel_name(oc_cur_chan_no);
		oc_cur_chan_freq = hal_get_channel_freq(oc_cur_chan_no);

		// set the last channel correctly
		oc_last_freq = oc_cur_freq;
		oc_last_chan = oc_cur_chan_no;

		// delay before we switch
		hal_delay_ms(1000);

		if(hal_is_uart_connected()) {
			oc_current_state = OC_STATE_DATA_IDLE;
		} else {
			oc_current_state = OC_STATE_ANALOGUE_ENTER;
		}

	break;

	case OC_STATE_ANALOGUE_ENTER:
		// set the frequency etc correctly
		hal_set_frequency(oc_cur_chan_freq);
		
		// render it here, because otherwise it won't be rendered
		render_state_analogue_idle();

		// now we delay a little bit again and idle
		hal_delay_ms(250);
		oc_current_state = OC_STATE_ANALOGUE_IDLE;
	break;

	case OC_STATE_ANALOGUE_IDLE:
		// if we changed frequency or channel, re-render the display
		if((oc_last_freq != oc_cur_freq)||(oc_last_chan != oc_cur_chan_no)) render_state_analogue_idle();
	break;

	case OC_STATE_ANALOGUE_TX_ENTER:
		hal_set_led_rx(false); // otherwise it's just wrong and confusing
		hal_set_led_tx(true);
		hal_set_radio_tx_voice(true); // TODO - handle RX-only stuff here, maybe show an error message
		
		// TODO - handle split TX/RX for repeaters rather than plain simplex
		// update the UI appropriately
		hal_display_status_text("OPENCOMM A-TX");
		hal_display_update();
	break;

	case OC_STATE_ANALOGUE_TX:
	break;

	case OC_STATE_ANALOGUE_TX_LEAVE:
		hal_set_led_tx(false);
		hal_set_radio_tx_voice(false);
	break;

	case OC_STATE_DATA_IDLE:
	break;

	case OC_STATE_DATA_CMD:
	break;

	case OC_STATE_DATA_TX:
	break;

	case OC_STATE_ERROR:
	break;
     }
}

