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
#include <stdbool.h>

#include "hal.h"

bool running = true;

void linux_main_loop() {
     while(running) {
        hal_main_loop_iter();
     }
}

int main(int argc, char** argv) {
    fprintf(stderr,"OpenComm core v%s\n", OPENCOMM_CORE_VER);
    fprintf(stderr,"OpenComm HAL v%s\n",  OPENCOMM_HAL_VER);
    fprintf(stderr,"OpenComm linux platform v%\n", OPENCOMM_PLATFORM_LINUX_VER);
    linux_main_loop();
    return 0;
}
