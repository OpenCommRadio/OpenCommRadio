/*
 * OpenCommRadio core callbacks
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

#include "hal.h"
#include "core_state.h"

#include <stddef.h>
#include <stdbool.h>

void opencomm_on_channel_change(uint16_t new_channel) {
     oc_last_chan = oc_cur_chan_no;
     oc_last_freq = oc_cur_chan_freq;
     
     oc_cur_chan_no   = new_channel;
     oc_cur_freq      = hal_get_channel_freq(new_channel);
     oc_cur_chan_name = hal_get_channel_name(new_channel);

}

void opencomm_on_ptt_change(bool pressed) {
     // here we just check if we're in analogue voice mode, otherwise we do nothing, we don't care

     if(oc_current_state==OC_STATE_ANALOGUE_IDLE && pressed) { // if we're idling in voice mode and PTT is down, we begin TX
        oc_current_state = OC_STATE_ANALOGUE_TX_ENTER; // TODO - we need to change this to support RX-only channels
     } else if(oc_current_state==OC_STATE_ANALOGUE_TX && !pressed) { // if we're currently transmitting and PTT is released, we stop TX
        oc_current_state = OC_STATE_ANALOGUE_TX_LEAVE;
     }

     // otherwise we don't give a fuck about that fucking PTT, what a fucking PTT button, fucking being pressed down or not
     // why the fuck should i care about you, you dumb fucking button

}

void opencomm_on_exit_button() {
}

bool opencomm_hal_uart_conn() {
}

void opencomm_modem_on_rx(uint8_t byte) {
     if(hal_is_uart_connected() && (oc_current_state==OC_STATE_DATA_IDLE)) {
        hal_uart_write(&byte, 1);
     }
}
