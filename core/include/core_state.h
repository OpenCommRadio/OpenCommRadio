/*
 * OpenCommRadio core state
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

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
	OC_STATE_BOOT,               // first state, just started up
	OC_STATE_ANALOGUE_ENTER,     // init of the analogue voice mode
	OC_STATE_ANALOGUE_IDLE,      // idling in analogue voice mode
	OC_STATE_ANALOGUE_TX_ENTER,  // start transmission
	OC_STATE_ANALOGUE_TX,        // transmitting in analogue voice mode
	OC_STATE_ANALOGUE_TX_LEAVE,  // end transmission
	OC_STATE_DATA_ENTER,         // entering data mode
	OC_STATE_DATA_IDLE,          // idling in data mode, ready to receive data
	OC_STATE_DATA_CMD,           // data mode, AT hayes commands
	OC_STATE_DATA_TX,            // data mode, transmitting data
	OC_STATE_ERROR               // generic error state
} oc_fsm_state_t;

extern oc_fsm_state_t oc_current_state;

extern uint32_t oc_last_freq;
extern uint16_t oc_last_chan;

extern uint32_t oc_cur_freq;
extern uint32_t oc_cur_chan_freq;
extern uint16_t oc_cur_chan_no;
extern char*    oc_cur_chan_name;

