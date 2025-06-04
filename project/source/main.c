#include <MCXA153.h>
#include <stdio.h>
#include <board.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lpuart0_interrupt.h"
#include "lpuart2_interrupt.h"

#include "utils/keypad.h"
#include "utils/oled_ui.h"
#include "games/trivia.h"

#include "utils/delay.h"
#include "utils/GPS.h"
#include "games/game_control.h"
#include "games/gps_location.game.h"
#include "games/gps_proximity.game.h"

// -----------------------------------------------------------------------------
// Local variables
// -----------------------------------------------------------------------------
static uint16_t secret_code;
static bool code_shown = false;

// -----------------------------------------------------------------------------
// Game handlers
// -----------------------------------------------------------------------------
static void handle_code_memory_game(game_controller_t *gc);
static void handle_trivia_game(game_controller_t *gc);
static void handle_final_unlock(game_controller_t *gc);

// -----------------------------------------------------------------------------
// Main application
// -----------------------------------------------------------------------------
int main(void)
{
    // Initialize hardware peripherals
    Keypad_Init();
    OLED_Init();

    // Initialize UART and game components
    lpuart0_init(115200);
    lpuart2_init(9600);
    game_controller_t *gameControl = initGameControl();
    GPS_t *GPS = initGPS();
    initGPSLocationGame();
    initGPSProximityGame();

    directions_t *directions;

    // Main loop
    while (1)
    {
        GPS->updateData();
        directions = GPS->getCurrentDirections();
        checkGameStatus();

        switch (gameControl->currentGame) {
        case TUTORIAL:
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
        srand(SysTick->VAL);  // Use current timer value as seed
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
        Delay_ms(2000);  // Show failure state
        gc->gameFailFlag = false; // Reset for retry
    }
}

static void handle_final_unlock(game_controller_t *gc)
{
    uint16_t entered_code = 0;
    char buffer[16];

    OLED_ShowMessage("ENTER CODE:", 0);

    while (1) {
        char key = Keypad_Scan();

        if (key >= '0' && key <= '9') {
            entered_code = entered_code * 10 + (key - '0');
            snprintf(buffer, sizeof(buffer), "%04d", entered_code);
            OLED_ShowCodeScreen(buffer);
        }

        if (key == '#') {
            if (entered_code == secret_code) {
    OLED_ShowMessage("UNLOCKED!", "");
                GAME_STATUS_SUCCESS();
                gc->gameSuccessFlag = true;
                break;
            } else {
    OLED_ShowMessage("WRONG CODE!", "");
                GAME_STATUS_FAILURE();
                entered_code = 0;
                OLED_ShowMessage("ENTER CODE:", 0);
            }
        }
    }
}
