/*
 * OpenCommsRadio HAL Interface
 *
 * This file is part of the OpenCommsRadio project.
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

#ifndef OPENCOMMSRADIO_HAL_H
#define OPENCOMMSRADIO_HAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Init and main loop
void hal_init();
void hal_main_loop_iter();   // this is the actual main loop, it's an infinite loop and never returns
void hal_background_tick();  // Optional: for timers, watchdogs, etc

// Radio control
void hal_set_frequency(uint32_t hz);
void hal_set_ctcss(uint16_t hz);

// Power info
uint8_t hal_get_battery_level();   // 0–100% represented as 0x00 - 0xFF

// Display interface
void hal_display_clear();
void hal_display_line(uint8_t line, char* text);
void hal_display_status_text(char* text);
void hal_display_tx(bool on);
void hal_display_battery(uint8_t percent);

// LEDs
void hal_set_led_tx(bool led_on);

// UART interface
bool    hal_uart_data_available();
uint8_t hal_uart_read();
void    hal_uart_write(const uint8_t* data, size_t len);
bool    hal_is_uart_connected();


// Callback types
typedef void (*opencomm_channel_changed_cb_t)(uint8_t new_channel);
typedef void (*opencomm_ptt_cb_t)(bool pressed);
typedef void (*opencomm_exit_cb_t)();
typedef bool (*opencomm_hal_uart_conn_cb_t)();

// Default callbacks
void opencomm_on_channel_change(uint8_t new_channel);
void opencomm_on_ptt_change(bool pressed);
void opencomm_on_exit_button();
bool opencomm_hal_uart_conn();


// externs from the core
extern void opencomm_main_fsm();
#endif // OPENCOMMSRADIO_HAL_H

