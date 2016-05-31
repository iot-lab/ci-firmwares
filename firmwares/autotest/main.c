/*
 * Copyright (C) 2016 IoT-Lab
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v3. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 * @brief iotlab autotest program
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "shell.h"
#include "xtimer.h"
#include "periph/uart.h"
#include "periph/gpio.h"

#define NUM_LEDS (3U)

static int board_leds[NUM_LEDS] = { -1, -1, -1 };
static int leds_indices[NUM_LEDS] = { 0, 0, 0 };

static void byte_to_binary(int x)
{
    for (unsigned int i = 0; i < NUM_LEDS; ++i) {
        leds_indices[NUM_LEDS - i - 1] = 0;
        if (x & (1 << i)) {
            leds_indices[NUM_LEDS - i - 1] = 1;
        }
    }
    
    return;
}

static int cmd_led_on(int argc, char **argv)
{
    unsigned int led = 0;
    if (argc != 2) {
        return 1;
    }
    
    if (1 != sscanf(argv[1], "%u", &led)) {
        return 1;
    }

    byte_to_binary(led);
    for (unsigned int i = 0; i < NUM_LEDS; ++i) {
        if (board_leds[i] != -1) {
            gpio_write(board_leds[i], 1 - leds_indices[i]);        
        }
    }
    
    printf("ACK %s %x\n", argv[0], led);
    return 0;
}

static int cmd_led_off(int argc, char **argv)
{
    unsigned int led = 0;
    if (argc != 2) {
        return 1;
    }

    if (!sscanf(argv[1], "%u", &led)) {
        return 1;
    }

    byte_to_binary(led);
    for (unsigned int i = 0; i < NUM_LEDS; ++i) {
        if (board_leds[i] != -1) {
            gpio_write(board_leds[i], leds_indices[i]);        
        }
    }

    printf("ACK %s %x\n", argv[0], led);
    return 0;
}

static int cmd_echo(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    for (int i = 1; i < argc - 1; ++i) {
        printf("%s ", argv[i]);
    }
    printf("%s\n", argv[argc - 1]);

    return 0;
}

static int cmd_get_time(int argc, char **argv)
{
    if (argc != 1) {
        return 1;
    }

    printf("ACK %s %u ticks_32khz\n", argv[0], (unsigned int)xtimer_now());

    return 0;
}

static const shell_command_t shell_commands[] = {
    { "echo",       "Simply write 'echo'",               cmd_echo},
    { "get_time",   "Simply return current timer value", cmd_get_time},
    { "leds_on",    "Turn led on",                       cmd_led_on},
    { "leds_off",   "Turn led off",                      cmd_led_off},
    { NULL, NULL, NULL }
};

int main(void)
{   
#ifdef LED0_PIN
    board_leds[0] = LED0_PIN;
#endif

#ifdef LED1_PIN
    board_leds[1] = LED1_PIN;
#endif

#ifdef LED2_PIN
    board_leds[2] = LED2_PIN;
#endif

    char buffer[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, buffer, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
