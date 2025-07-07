/*
 * OpenCommRadio linux platform
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "hal.h"

void hal_platform_init() {
     fprintf(stderr,"hal_platform_init(): Booting!\n");
}

void hal_delay_ms(uint16_t ms) { 
     struct timespec ts;
     ts.tv_sec = ms / 1000;
     ts.tv_nsec = (ms % 1000) * 1000000L;
     nanosleep(&ts, NULL); 
}

void hal_delay_us(uint16_t us) { 
     struct timespec ts;
     ts.tv_sec  = us / 1000000;
     ts.tv_nsec = (us % 1000000) * 1000L;
     nanosleep(&ts, NULL); 
}

bool hal_ptt_is_down() { return false; }

bool hal_exit_button_pressed() { return false; }

static char status_bar[32];
static char display_lines[3][32];

void hal_display_clear() {
     memset(status_bar,0,sizeof(status_bar));
     memset(display_lines,0,sizeof(display_lines));
}

void hal_display_line(uint8_t line, char* text) {
     memset(display_lines[line-1],0,sizeof(display_lines[line-1]));
     snprintf(display_lines[line-1],sizeof(display_lines[line-1]),"%s",text);
}

void hal_display_status_text(char* text) {
     snprintf(status_bar,sizeof(status_bar),"%s",text);
}

void hal_display_update() {
     fprintf(stderr,"+%-32s+\n",status_bar);
     fprintf(stderr,"|%-32s|\n",display_lines[0]);
     fprintf(stderr,"|%-32s|\n",display_lines[1]);
     fprintf(stderr,"|%-32s|\n",display_lines[2]);

}

void hal_display_backlight_set(bool on) {
     if(on) {
        fprintf(stderr,"hal_display_backlight_set: backlight on\n");
     } else {
        fprintf(stderr,"hal_display_backlight_set: backlight off\n");
     }
}

__attribute__((weak))
bool hal_uart_data_available() { return false; }

__attribute__((weak))
uint8_t hal_uart_read() { return 0; }

__attribute__((weak))
void hal_uart_write(const uint8_t* data, size_t len) {}

__attribute__((weak))
bool hal_is_uart_connected() { return false; }


