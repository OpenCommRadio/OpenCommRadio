/*
 * OpenCommRadio HAL Interface
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
#include <string.h>

// --- Internal state ---

static uint8_t last_channel = 0xFF;
static bool    last_ptt     = false;
static bool    last_exit    = false;

// --- Weak platform overrides ---

__attribute__((weak))
void hal_platform_init() {}

__attribute__((weak))
uint8_t hal_get_channel() { return 0; }

__attribute__((weak))
bool hal_ptt_is_down() { return false; }

__attribute__((weak))
bool hal_exit_button_pressed() { return false; }

__attribute__((weak))
void hal_background_tick() {}

__attribute__((weak))
void hal_set_frequency(uint32_t hz) {}

__attribute__((weak))
void hal_set_ctcss(uint16_t hz) {}

__attribute__((weak))
uint8_t hal_get_battery_level() { return 255; }

__attribute__((weak))
void hal_display_clear() {}

__attribute__((weak))
void hal_display_line(uint8_t line, char* text) {}

__attribute__((weak))
void hal_display_status_text(char* text) {}

__attribute__((weak))
void hal_display_tx(bool on) {}

__attribute__((weak))
void hal_display_battery(uint8_t percent) {}

__attribute__((weak))
void hal_set_led_tx(bool led_on) {}

__attribute__((weak))
bool hal_uart_data_available() { return false; }

__attribute__((weak))
uint8_t hal_uart_read() { return 0; }

__attribute__((weak))
void hal_uart_write(const uint8_t* data, size_t len) {}

__attribute__((weak))
bool hal_uart_connected() { return false; }


void hal_init() {
     hal_platform_init();
     last_channel = hal_get_channel();
     last_ptt     = hal_ptt_is_down();
     last_exit    = hal_exit_button_pressed();
}


void hal_main_loop(void) {
     for (;;) {
         uint8_t ch = hal_get_channel();
         if (ch != last_channel) {
             last_channel = ch;
             opencomm_on_channel_change(ch);
         }

         // PTT
         bool ptt = hal_ptt_is_down();
         if (ptt != last_ptt) {
             last_ptt = ptt;
             opencomm_on_ptt_change(ptt);
         }

         // Exit button
         bool exit = hal_exit_button_pressed();
         if (exit && !last_exit) {
             opencomm_on_exit_button();
         }
         last_exit = exit;

         hal_background_tick();
         opencomm_main_fsm();
     }
}
