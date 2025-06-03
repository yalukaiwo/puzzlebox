#include "led_control.h"
#include "button_control.h"
#include "buzzer_pwm.h"
#include "MCXA153.h"
#include <stdlib.h>
#include <stdbool.h>

#define TOTAL_ROUNDS 6

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        count = 10000;
        while (count--) __NOP();
    }
}

void memory_game_start(void) {
    leds_init();
    buttons_init();
    buzzer_pwm_init();
    SysTick_Config(48000); // for delay_ms 1ms tick

    uint8_t rounds_completed = 0;
    bool used_combinations[16] = { false };

    while (rounds_completed < TOTAL_ROUNDS) {
        uint8_t num_leds = (rand() % 4) + 1;

        uint8_t combo_index;
        do {
            combo_index = rand() % 16;
        } while (used_combinations[combo_index] || __builtin_popcount(combo_index) != num_leds);

        used_combinations[combo_index] = true;

        for (uint8_t i = 0; i < 4; i++) {
            if (combo_index & (1 << i)) {
                led_on(i + 1);
            } else {
                led_off(i + 1);
            }
        }

        uint8_t button_press_count = 0;
        bool btn_pressed[4] = { false };

        while (button_press_count < num_leds) {
            for (uint8_t i = 0; i < 4; i++) {
                if (!btn_pressed[i] && button_is_pressed(i + 1)) {
                    btn_pressed[i] = true;
                    button_press_count++;
                    delay_ms(300);
                }
            }
        }

        delay_ms(1000);
        for (uint8_t i = 0; i < 4; i++) {
            if (!btn_pressed[i] && button_is_pressed(i + 1)) {
                buzzer_beep_error();
                delay_ms(1000);
                goto repeat_round;
            }
        }

        rounds_completed++;
    repeat_round:
        for (uint8_t i = 0; i < 4; i++) led_off(i + 1);
        delay_ms(500);
    }

    buzzer_beep_win();
    while (1);
}
