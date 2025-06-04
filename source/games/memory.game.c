#include "led_control.h"
#include "button_control.h"
#include "buzzer_pwm.h"
#include "MCXA153.h"
#include <stdlib.h>
#include <stdbool.h>

#define TOTAL_ROUNDS 6

void delay_ms(uint32_t ms); // Delay function prototype

void memory_game_start(void) {
    leds_init();
    buttons_init();
    buzzer_pwm_init();

    SysTick_Config(48000); // 1ms tick assuming 48MHz core clock

    uint8_t rounds_completed = 0;

    while (rounds_completed < TOTAL_ROUNDS) {
        uint8_t num_leds = rounds_completed + 1; // round 1: 1 LED, round 2: 2 LEDs, ...

        bool selected_leds[4] = {false};
        uint8_t selected_count = 0;

        while (selected_count < num_leds) {
            uint8_t led_index = rand() % 4;
            if (!selected_leds[led_index]) {
                selected_leds[led_index] = true;
                led_on(led_index + 1);
                selected_count++;
            }
        }

        // Wait for correct button inputs
        uint8_t pressed_count = 0;
        bool button_pressed[4] = {false};
        bool round_failed = false;

        while (pressed_count < num_leds && !round_failed) {
            for (uint8_t i = 0; i < 4; i++) {
                if (button_is_pressed(i + 1)) {
                    if (selected_leds[i] && !button_pressed[i]) {
                        button_pressed[i] = true;
                        pressed_count++;
                        delay_ms(300); // debounce
                    } else if (!selected_leds[i]) {
                        // wrong button
                        buzzer_beep_error();
                        delay_ms(500);
                        round_failed = true;
                        break;
                    }
                }
            }
        }

        // Turn off LEDs
        for (uint8_t i = 0; i < 4; i++) {
            led_off(i + 1);
        }

        if (round_failed) {
            rounds_completed = 0;
            continue;
        } else {
            rounds_completed++;
            delay_ms(500);
        }
    }

    // Game won
    buzzer_beep_win();
    while (1);
}

// Software delay using NOPs
void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 4800; i++) {
        __NOP();
    }
}
