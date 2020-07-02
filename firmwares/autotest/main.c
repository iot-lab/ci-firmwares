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

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shell.h"
#include "xtimer.h"
#include "thread.h"
#include "mutex.h"
#include "msg.h"

#include "board.h"
#include "periph/gpio.h"
#include "periph/uart.h"
#ifdef MODULE_PERIPH_CPUID
#include "periph/cpuid.h"
#endif

#define NUM_LEDS              (3U)

static char blink_stack[THREAD_STACKSIZE_DEFAULT];

static int board_leds[NUM_LEDS] = { -1, -1, -1 };
static uint8_t leds_indices[NUM_LEDS] = { 0, 0, 0 };

static kernel_pid_t blink_pid;

typedef struct {
    bool blink;
    uint32_t delay;
    mutex_t lock;
} blink_state_t;

static blink_state_t blink_state;

static void _blink_start(uint32_t delay)
{
    mutex_lock(&blink_state.lock);
    blink_state.blink = true;
    blink_state.delay = delay;
    mutex_unlock(&blink_state.lock);
    msg_t msg;
    msg_send(&msg, blink_pid);
}

static void _blink_stop(void)
{
    mutex_lock(&blink_state.lock);
    blink_state.blink = false;
    blink_state.delay = 100;
    mutex_unlock(&blink_state.lock);
}

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

static void byte_to_binary(unsigned byte)
{
    for (unsigned i = 0; i < NUM_LEDS; ++i) {
        leds_indices[NUM_LEDS - i - 1] = 0;
        if (byte & (1 << i)) {
            leds_indices[NUM_LEDS - i - 1] = 1;
        }
    }

    return;
}

static void *blink_thread(void *arg)
{
    blink_state_t * state = (blink_state_t *)arg;
    state->delay = 100;

    xtimer_t blink_timer;
    while(1) {
        msg_t msg;
        msg_receive(&msg);
        if (state->blink) {
            toggle_leds_on();
            xtimer_usleep(state->delay * 1000U);
            toggle_leds_off();
            msg_t blink_msg;
            msg_send(&blink_msg, blink_pid);
            xtimer_set_msg(&blink_timer, state->delay * 1000U, &blink_msg, blink_pid);
        }
    }

    return NULL;
}

static int cmd_leds_on(int argc, char **argv)
{
    if (argc != 2) {
        puts("NACK leds_on: wrong number of arguments");
        return 1;
    }

    unsigned leds = atoi(argv[1]);
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

    unsigned int leds = atoi(argv[1]);
    byte_to_binary(leds);
    toggle_leds_off();

    _blink_stop();

    printf("ACK %s %d\n", argv[0], leds);
    return 0;
}

static int cmd_leds_blink(int argc, char **argv)
{
    if (argc != 3) {
        puts(
            "NACK leds_blink: wrong number of arguments\n"
            "Usage: leds_blink <leds> <delay ms>"
        );
        return 1;
    }

    unsigned int leds = atoi(argv[1]);
    byte_to_binary(leds);

    uint32_t delay = atoi(argv[2]);
    if (delay == 0) {
        toggle_leds_off();
        _blink_stop();
        printf("ACK %s STOP\n", argv[0]);
        return 0;
    }

    if (blink_state.delay > 10000) {
        delay = 10000;
    }

    toggle_leds_off();
    _blink_start(delay);

    printf("ACK %s %d %" PRIu32 "\n", argv[0], leds, delay);
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

#ifdef MODULE_PERIPH_CPUID
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
#endif

static const shell_command_t shell_commands[] = {
    { "echo",       "Simply write 'echo'",               cmd_echo},
    { "get_time",   "Print board time",                  cmd_get_time},
#ifdef MODULE_PERIPH_CPUID
    { "get_uid",    "Print board uid",                   cmd_get_uid},
#endif
    { "leds_on",    "Turn given leds on",                cmd_leds_on},
    { "leds_off",   "Turn given leds off",               cmd_leds_off},
    { "leds_blink", "Make leds blink",                   cmd_leds_blink},
    { NULL, NULL, NULL }
};

int main(void)
{
#ifdef LED0_PIN
    gpio_init(LED0_PIN, GPIO_OUT);
    board_leds[0] = LED0_PIN;
#endif

#ifdef LED1_PIN
    gpio_init(LED1_PIN, GPIO_OUT);
    board_leds[1] = LED1_PIN;
#endif

#ifdef LED2_PIN
    gpio_init(LED2_PIN, GPIO_OUT);
    board_leds[2] = LED2_PIN;
#endif

    blink_pid = thread_create(blink_stack, sizeof(blink_stack),
                              THREAD_PRIORITY_MAIN - 1,
                              THREAD_CREATE_STACKTEST, blink_thread,
                              &blink_state, "Leds blink thread");

    char buffer[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, buffer, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
