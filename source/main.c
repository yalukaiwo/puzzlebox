#include <MCXA153.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lpuart0_interrupt.h"
#include "lpuart2_interrupt.h"
#include "lcdDriver/lpi2c0_controller_polling.h"
#include "gpio_output.h"

#include "utils/GPS.h"
#include "Keypad/keypad.h"
#include "utils/Logger.h"
#include "utils/SD.h"

#include "lcdDriver/oled_ui.h"
#include "lcdDriver/delay.h"

#include "games/game_control.h"
#include "games/gps_location.game.h"
#include "games/gps_proximity.game.h"
#include "games/trivia.h"

// -----------------------------------------------------------------------------
// Local type definitions
// -----------------------------------------------------------------------------
#ifdef DEBUG
#define TARGETSTR "Debug"
#else
#define TARGETSTR "Release"
#endif

// -----------------------------------------------------------------------------
// Local variables
// -----------------------------------------------------------------------------
static uint16_t secret_code;
static bool code_shown = false;
static volatile long ms = 0;

// -----------------------------------------------------------------------------
// Local function prototypes
// -----------------------------------------------------------------------------
static void handle_code_memory_game(game_controller_t *gc);
static void handle_trivia_game(game_controller_t *gc);
static void handle_final_unlock(game_controller_t *gc);

// -----------------------------------------------------------------------------
// Main application
// -----------------------------------------------------------------------------
int main(void)
{
    // === Init Hardware ===
	OLED_Init();
	SysTick_Config(48000);
    lpuart0_init(115200);
    lpuart2_init(9600);
    lpi2c0_controller_init();
    gpio_output_init();
    Keypad_Init();
    // SD_Init(); // Uncomment if needed

    // === Init Software ===
    game_controller_t *gameControl = initGameControl();
    initGPSLocationGame();
    initGPSProximityGame();

    directions_t *directions;
    __enable_irq();

    // === Main Loop ===
    while (1)
    {
        GPS_updateData();
        directions = GPS_getCurrentDirections();
        checkGameStatus();

        if (ms >= 60000) {
            Logger_updateData();
            ms = 0;
        }

        switch (gameControl->currentGame) {
        case TUTORIAL:
            OLED_ShowMessage("Welcome", "Start Walking");
            break;

        case LOCATION:
            gpsLocationGame();
            break;

        case MEMORY:
            handle_code_memory_game(gameControl);
            break;

        case QUIZ:
            handle_trivia_game(gameControl);
            break;

        case PROXIMITY:
            gpsProximityGame();
            break;

        case PIN:
            handle_final_unlock(gameControl);
            break;

        case VICTORY:
            OLED_ShowMessage("Congrats!", "Puzzle Solved");
            break;

        default:
            gameControl->gameFailFlag = true;
            break;
        }
    }
}

// -----------------------------------------------------------------------------
// Game implementations
// -----------------------------------------------------------------------------
static void handle_code_memory_game(game_controller_t *gc)
{
    if (!code_shown) {
        srand(SysTick->VAL);
        secret_code = (rand() % 9000) + 1000;

        char code_str[5];
        snprintf(code_str, sizeof(code_str), "%04d", secret_code);

        for (uint8_t t = 8; t > 0; t--) {
            OLED_ShowCodeScreen(code_str);
            Delay_ms(1000);
        }
        code_shown = true;
    }

    gc->gameSuccessFlag = true;
    GAME_STATUS_SUCCESS();
}

static void handle_trivia_game(game_controller_t *gc)
{
    bool result = Trivia_RunGame();
    gc->gameSuccessFlag = result;

    if (result) {
        GAME_STATUS_SUCCESS();
    } else {
        GAME_STATUS_FAILURE();
        Delay_ms(2000);
        gc->gameFailFlag = false;  // Reset for retry
    }
}

static void handle_final_unlock(game_controller_t *gc)
{
    OLED_ShowMessage("ENTER CODE:", "");

    char pin[5] = {0};   // To store 4-digit PIN
    char stars[5] = {0}; // To show ****
    int index = 0;

    while (1) {
        char key = Keypad_Scan();

        if (key >= '0' && key <= '9' && index < 4) {
            pin[index] = key;
            stars[index] = '*';  // Add asterisk
            index++;

            OLED_ShowMessage("ENTER CODE:", stars);
            Delay_ms(200); // debounce
        }

        if (key == '*' && index > 0) {  // Optional: delete/backspace
            index--;
            pin[index] = '\0';
            stars[index] = '\0';
            OLED_ShowMessage("ENTER CODE:", stars);
            Delay_ms(200);
        }

        if (index == 4 && key == '#') {
            pin[4] = '\0';  // Null-terminate

            char correct_code[5];
            snprintf(correct_code, sizeof(correct_code), "%04d", secret_code);

            if (strcmp(pin, correct_code) == 0) {
                OLED_ShowMessage("UNLOCKED!", "");
                GAME_STATUS_SUCCESS();
                gc->gameSuccessFlag = true;
                break;
            } else {
                OLED_ShowMessage("WRONG CODE!", "");
                Delay_ms(2000);

                // Reset input
                index = 0;
                memset(pin, 0, sizeof(pin));
                memset(stars, 0, sizeof(stars));
                OLED_ShowMessage("ENTER CODE:", "");
            }
        }
    }
}

// -----------------------------------------------------------------------------
// System Tick Handler
// -----------------------------------------------------------------------------
void SysTick_Handler(void)
{
    ms++;
}
