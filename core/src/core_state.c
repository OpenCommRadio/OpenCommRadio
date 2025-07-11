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

#include <stddef.h>
#include <stdbool.h>

#include "core_state.h"

oc_fsm_state_t oc_current_state = OC_STATE_BOOT;

uint32_t oc_last_freq = 0;
uint16_t oc_last_chan = 0;


uint32_t oc_cur_freq      = 0;
uint32_t oc_cur_chan_freq = 0;
uint16_t oc_cur_chan_no   = 0;
char*    oc_cur_chan_name = NULL;


