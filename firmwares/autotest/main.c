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

#include "shell.h"
#include "xtimer.h"
#include "thread.h"

#include "board.h"
#include "periph/cpuid.h"
#include "periph/gpio.h"
#include "periph/uart.h"

#define NUM_LEDS              (3U)

static char blink_stack[THREAD_STACKSIZE_DEFAULT];

static int board_leds[NUM_LEDS] = { -1, -1, -1 };
static int leds_indices[NUM_LEDS] = { 0, 0, 0 };
static bool blink = false;
static int delay = 100;

static void toggle_leds_on(void)
{
    for (unsigned i = 0; i < NUM_LEDS; ++i) {
        if ( (board_leds[i] != -1) && (leds_indices[i])) {
            gpio_clear(board_leds[i]);
        }
    }
}

static void toggle_leds_off(void)
{
    for (unsigned i = 0; i < NUM_LEDS; ++i) {
        if ((board_leds[i] != -1) && (leds_indices[i])) {
            gpio_set(board_leds[i]);
        }
    }
}

static void byte_to_binary(unsigned x)
{
    for (unsigned i = 0; i < NUM_LEDS; ++i) {
        leds_indices[NUM_LEDS - i - 1] = 0;
        if (x & (1 << i)) {
            leds_indices[NUM_LEDS - i - 1] = 1;
        }
    }

    return;
}

static void *blink_thread(void *args)
{
    (void)args;
    while(1) {
        if (blink) {
            toggle_leds_on();
            xtimer_usleep(delay * 1000U);
            toggle_leds_off();
        }
        xtimer_usleep(delay * 1000U);
    }

    return NULL;
}

static int cmd_leds_on(int argc, char **argv)
{
    if (argc != 2) {
        puts("NACK leds_on: wrong number of arguments");
        return 1;
    }

    unsigned leds = 0;
    if (1 != sscanf(argv[1], "%u", &leds)) {
        puts("NACK leds_on: invalid led number");
        return 1;
    }

    byte_to_binary(leds);
    toggle_leds_on();

    printf("ACK %s %x\n", argv[0], leds);
    return 0;
}

static int cmd_leds_off(int argc, char **argv)
{
    if (argc != 2) {
        puts("NACK leds_off: wrong number of arguments");
        return 1;
    }

    unsigned int leds = 0;
    if (1 != sscanf(argv[1], "%u", &leds)) {
        puts("NACK leds_off: invalid led number");
        return 1;
    }

    byte_to_binary(leds);
    toggle_leds_off();

    blink = false;

    printf("ACK %s %d\n", argv[0], leds);
    return 0;
}

static int cmd_leds_blink(int argc, char **argv)
{
    if (argc != 3) {
        puts("NACK leds_blink: wrong number of arguments");
        return 1;
    }

    unsigned int leds = 0;
    if (1 != sscanf(argv[1], "%u", &leds)) {
        puts("NACK leds_blink: invalid led number");
        return 1;
    }
    byte_to_binary(leds);

    int delay_tmp;
    if (1 != sscanf(argv[2], "%i", &delay_tmp)) {
        puts("NACK leds_blink: invalid delay argument");
        return 1;
    }
    
    if (delay_tmp == 0) {
        toggle_leds_off();
        blink = false;
        printf("ACK %s STOP\n", argv[0]);
        return 0;
    }

    if (delay_tmp < 10 || delay_tmp > 10000) {
        puts("NACK leds_blink: delay too long or too short");
        return 1;
    }

    toggle_leds_off();
    delay = delay_tmp;
    blink = true;

    printf("ACK %s %d %d\n", argv[0], leds, delay);
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
    uint32_t now = xtimer_now().ticks32;

    printf("ACK %s %u ticks_32khz\n", argv[0], (unsigned int)now);

    return 0;
}

static int cmd_get_uid(int argc, char **argv)
{
    if (argc != 1) {
        return 1;
    }

    uint8_t id[CPUID_LEN];

    /* read the CPUID */
    cpuid_get(id);

    /* print the CPUID */
    printf("ACK %s ", argv[0]);
    for (unsigned int i = 0; i < CPUID_LEN; i++) {
        printf("%02x", id[i]);
    }
    puts("");

    return 0;
}

static const shell_command_t shell_commands[] = {
    { "echo",       "Simply write 'echo'",               cmd_echo},
    { "get_time",   "Print board time",                  cmd_get_time},
    { "get_uid",    "Print board uid",                   cmd_get_uid},
    { "leds_on",    "Turn given leds on",                cmd_leds_on},
    { "leds_off",   "Turn given leds off",               cmd_leds_off},
    { "leds_blink", "Make leds blink",                   cmd_leds_blink},
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

    thread_create(blink_stack, sizeof(blink_stack),
                  THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, blink_thread,
                  NULL, "Leds blink thread");

    char buffer[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, buffer, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
