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
    char pin[5] = {0};
    char stars[5] = {0};
    int index = 0;

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Enter code:");

    while (1) {
        char key = Keypad_Scan();

        if (key >= '0' && key <= '9' && index < 4) {
            pin[index] = key;
            stars[index] = '*';
            index++;

            lcd_set_cursor(1, 0);
            lcd_print(stars);
            Delay_ms(200);
        }

        if (key == '*' && index > 0) {
            index--;
            pin[index] = '\0';
            stars[index] = '\0';
            lcd_set_cursor(1, 0);
            lcd_print(stars);
            Delay_ms(200);
        }

        if (index == 4 && key == '#') {
            pin[4] = '\0';

            char correct_code[5];
            snprintf(correct_code, sizeof(correct_code), "%04d", secret_code);

            if (strcmp(pin, correct_code) == 0) {
                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("Unlocked!");
                GAME_STATUS_SUCCESS();
                gc->gameSuccessFlag = true;
                break;
            } else {
                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("Wrong Code!");
                Delay_ms(2000);

                index = 0;
                memset(pin, 0, sizeof(pin));
                memset(stars, 0, sizeof(stars));
                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("Enter code:");
            }
        }
    }
}
