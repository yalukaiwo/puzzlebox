#include "lcdDriver/lcd.h"
#include "Keypad/keypad.h"
#include "games/game_control.h"
#include "utils/delay.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

extern uint16_t secret_code;

void Game_Unlock(game_controller_t *gc)
{
    static char pin[5] = {0};
    static char stars[5] = {0};
    static int index = 0;
    static bool init = true;

    if (init) {
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print("Enter code:");
        memset(pin, 0, sizeof(pin));
        memset(stars, 0, sizeof(stars));
        index = 0;
        init = false;
        return;
    }

    char key = Keypad_Scan();

    if (key >= '0' && key <= '9' && index < 4) {
        pin[index] = key;
        stars[index] = '*';
        index++;

        lcd_set_cursor(1, 0);
        lcd_print(stars);
        Delay_ms(200);
        return;
    }

    if (key == '*' && index > 0) {
        index--;
        pin[index] = '\0';
        stars[index] = '\0';

        lcd_set_cursor(1, 0);
        lcd_print(stars);
        Delay_ms(200);
        return;
    }

    if (index == 4 && key == '#') {
        char correct_code[5];
        snprintf(correct_code, sizeof(correct_code), "%04d", secret_code);

        if (strcmp(pin, correct_code) == 0) {
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Unlocked!");
            GAME_STATUS_SUCCESS();
            gc->gameSuccessFlag = true;
            init = true;  // reset for next time
        } else {
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Wrong Code!");
            Delay_ms(2000);

            memset(pin, 0, sizeof(pin));
            memset(stars, 0, sizeof(stars));
            index = 0;

            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("Enter code:");
        }
    }
}
