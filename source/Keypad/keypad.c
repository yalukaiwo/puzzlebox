
#include <Keypad/fsl_clock.h>
#include <Keypad/fsl_common.h>
#include <Keypad/fsl_gpio.h>
#include <Keypad/keypad.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

static const char keypad_map[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

static const uint32_t row_pins[KEYPAD_ROWS] = {0, 1, 2, 3}; // GPIO1: P0_0 to P0_3
static const uint32_t col_pins[KEYPAD_COLS] = {4, 5, 6, 7}; // GPIO1: P0_4 to P0_7

void Keypad_Init(void) {

    gpio_pin_config_t row_config = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t col_config = {kGPIO_DigitalInput, 0};

    for (int i = 0; i < KEYPAD_ROWS; i++) {
        GPIO_PinInit(GPIO1, row_pins[i], &row_config);
        GPIO_PinWrite(GPIO1, row_pins[i], 1); // set all rows high
    }

    for (int j = 0; j < KEYPAD_COLS; j++) {
        GPIO_PinInit(GPIO1, col_pins[j], &col_config);
    }
}

char Keypad_GetKey(void) {
    for (int i = 0; i < KEYPAD_ROWS; i++) {
        for (int r = 0; r < KEYPAD_ROWS; r++)
            GPIO_PinWrite(GPIO1, row_pins[r], 1);
        GPIO_PinWrite(GPIO1, row_pins[i], 0); // activate row

        for (int j = 0; j < KEYPAD_COLS; j++) {
            if (!GPIO_PinRead(GPIO1, col_pins[j])) {
                while (!GPIO_PinRead(GPIO1, col_pins[j])); // debounce
                return keypad_map[i][j];
            }
        }
    }
    return 0; // no key pressed
}

char Keypad_Scan(void) {
    return Keypad_GetKey();
}
