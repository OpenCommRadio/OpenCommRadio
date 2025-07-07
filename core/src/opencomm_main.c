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

		// and now we setup the correct frequency for that channel
		hal_set_frequency(oc_cur_chan_freq);

		// and finally, another wait, just to be sure, and then we switch into the relevant mode
		hal_delay_ms(1000);
		if(hal_is_uart_connected()) {
			oc_current_state = OC_STATE_DATA_IDLE;
		} else {
			oc_current_state = OC_STATE_ANALOGUE_IDLE;
		}
	break;

	case OC_STATE_ANALOGUE_IDLE:

	break;

	case OC_STATE_ANALOGUE_TX:
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

