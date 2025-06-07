/*
 * memory.game.c
 *
 *  Created on: 7 Jun 2025
 *      Author: adibh
 */
#include "memory_game.h"
#include "button_control.h"
#include "led_control.h"
#include "buzzer_pwm.h"
#include "utils.h"
#include <stdlib.h>

#define TOTAL_ROUNDS 6
#define MAX_LEDS     4

static uint8_t rounds_completed = 0;
static uint8_t current_leds[MAX_LEDS];

// Generate a random sequence of LEDs for each round
static void generate_random_leds(uint8_t round) {
    uint8_t used[MAX_LEDS] = {0};
    uint8_t count = 0;

    while (count < round) {
        uint8_t rnd = rand() % MAX_LEDS;

        // Prevent duplicate LEDs before round 5
        if (round <= MAX_LEDS && used[rnd])
            continue;

        current_leds[count++] = rnd;
        used[rnd] = 1;
    }
}

// Initialize all game components
void memory_game_init(void) {
    buttons_init();
    leds_init();
    buzzer_pwm_init();
    rounds_completed = 0;
}

// Run the main game loop
void memory_game_loop(void) {
    while (rounds_completed < TOTAL_ROUNDS) {
        uint8_t round = rounds_completed + 1;
        generate_random_leds(round);

        // Show LED sequence to player
        for (uint8_t i = 0; i < round; i++) {
            led_on(current_leds[i] + 1);  // LEDs use 1-based index
            delay_ms(300);
            led_off(current_leds[i] + 1);
            delay_ms(200);
        }

        // Wait for correct button presses
        uint8_t correct_presses = 0;
        while (correct_presses < round) {
            for (uint8_t i = 0; i < round; i++) {
                if (button_is_pressed(current_leds[i] + 1)) {
                    correct_presses++;
                    delay_ms(300);  // Debounce
                    while (button_is_pressed(current_leds[i] + 1));
                    delay_ms(300);
                }
            }

            // Check for incorrect button press
            for (uint8_t btn = 1; btn <= MAX_LEDS; btn++) {
                uint8_t valid = 0;
                for (uint8_t j = 0; j < round; j++) {
                    if (btn == current_leds[j] + 1) {
                        valid = 1;
                        break;
                    }
                }
                if (!valid && button_is_pressed(btn)) {
                    buzzer_beep_error();
                    rounds_completed = 0;  // Restart game
                    delay_ms(500);
                    return;
                }
            }
        }

        rounds_completed++;
        delay_ms(500);
    }

    // Player completed all rounds successfully
    buzzer_beep_win();
}


