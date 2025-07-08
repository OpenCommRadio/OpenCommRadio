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
#include <pthread.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "hal.h"

bool running = true;

pthread_t opencomm_thread;
pthread_t cli_thread;

void* opencomm_main_loop(void* arg) {
      hal_init();
      while(running) {
         hal_main_loop_iter();
         hal_delay_us(1);
      }
}

void cli_handle_cmd(const char* cmd) {
     if(strcmp(cmd,"exit")==0) {
        running = false;
	return;
     } else if(strcmp(cmd,"ptt on")==0) {
        opencomm_on_ptt_change(true);
     } else if(strcmp(cmd,"ptt off")==0) {
        opencomm_on_ptt_change(false);
     }
}

void* opencomm_cli_loop(void* arg) {
      char* input;

      while (running && (input = readline("OpenComm>")) != NULL) {
         if(*input) add_history(input);
         cli_handle_cmd(input);
	 free(input);
      }
}


int main(int argc, char** argv) {
    fprintf(stderr,"OpenComm core v%s\n", OPENCOMM_CORE_VER);
    fprintf(stderr,"OpenComm HAL v%s\n",  OPENCOMM_HAL_VER);
    fprintf(stderr,"OpenComm linux platform v%s\n", OPENCOMM_PLATFORM_LINUX_VER);

    int ret = 0;
    ret = pthread_create(&opencomm_thread,NULL,&opencomm_main_loop,NULL);
    ret = pthread_create(&cli_thread,     NULL,&opencomm_cli_loop, NULL);

    pthread_join(opencomm_thread, NULL);
    pthread_join(cli_thread,      NULL);
    return 0;
}
