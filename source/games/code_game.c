#include "lcdDriver/lcd.h"
#include "utils/delay.h"
#include "games/game_control.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

static uint16_t secret_code;
static bool code_shown = false;

void Game_Memory(game_controller_t *gc)
{
    if (!code_shown) {
    	srand(1234);
        secret_code = (rand() % 9000) + 1000;

        char code_str[5];
        snprintf(code_str, sizeof(code_str), "%04d", secret_code);

        for (uint8_t t = 8; t > 0; t--) {
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Remember The code:");
            lcd_set_cursor(1, 0);
            lcd_print(code_str);
            Delay_ms(1000);
        }

        lcd_clear();
        code_shown = true;
    }

    gc->gameSuccessFlag = true;
    GAME_STATUS_SUCCESS();
}
