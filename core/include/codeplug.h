/*
 * OpenCommRadio codeplug format structures
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

#define CHANNEL_NAME_LEN 16
#define MAX_CALLSIGN_LEN 12
#define CHANNEL_COUNT    16

typedef struct {
    uint32_t rx_freq;
    uint32_t tx_freq;
    char channel_name[CHANNEL_NAME_LEN];
} oc_channel_t;

typedef struct {
    char      callsign[MAX_CALLSIGN_LEN];
    channel_t channels[CHANNEL_COUNT];
} oc_codeplug_t
