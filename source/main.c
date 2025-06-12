#include <MCXA153.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lpuart0_interrupt.h"
#include "lpuart2_interrupt.h"
#include "lcdDriver/lcd.h"
#include "gpio_output.h"
#include "utils/GPS.h"
#include "Keypad/keypad.h"
#include "utils/Logger.h"
#include "utils/SD.h"

#include "games/game_control.h"
#include "games/gps_location.game.h"
#include "games/gps_proximity.game.h"
#include "games/trivia.h"

#include "games/code_game.h"
#include "games/trivia_game.h"
#include "games/pin_game.h"

// Global for PIN comparison
uint16_t secret_code;
volatile long ms = 0;

void update_system(game_controller_t *gc);

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
int main(void)
{
    SysTick_Config(48000);
    lpuart0_init(115200);
    lpuart2_init(9600);
    lpi2c0_controller_init();

    lcd_init();
    lcd_clear();
    lcd_set_cursor(0, 0); lcd_send_string("Hello Boss!");
    lcd_set_cursor(1, 0); lcd_send_string("-- Goblin Gang!");
    Delay_ms(15000);
    lcd_clear();

    gpio_output_init();
    Keypad_Init();
    // SD_Init(); // if needed

    game_controller_t *gc = initGameControl();
    initGPSLocationGame();
    initGPSProximityGame();

    __enable_irq();

    while (1) {
        update_system(gc);
        Delay_ms(10);
    }
}

void update_system(game_controller_t *gc)
{
    GPS_updateData();
    checkGameStatus();

    if (ms >= 60000) {
        Logger_updateData();
        ms = 0;
    }

    switch (gc->currentGame) {
        case TUTORIAL:
            lcd_clear();
            lcd_set_cursor(0, 0); lcd_send_string("Welcome!");
            lcd_set_cursor(1, 0); lcd_send_string("Start walking...");
            break;

        case LOCATION:
            gpsLocationGame();
            break;

        case MEMORY:
            Game_Memory(gc);
            break;

        case QUIZ:
            Game_Trivia(gc);
            break;

        case PROXIMITY:
            gpsProximityGame();
            break;

        case PIN:
            Game_Unlock(gc);
            break;

        case VICTORY:
            lcd_clear();
            lcd_set_cursor(0, 0); lcd_send_string("Congrats!");
            lcd_set_cursor(1, 0); lcd_send_string("Puzzle Solved");
            break;

        default:
            gc->gameFailFlag = true;
            break;
    }
}

// -----------------------------------------------------------------------------
void SysTick_Handler(void)
{
    ms++;
}
