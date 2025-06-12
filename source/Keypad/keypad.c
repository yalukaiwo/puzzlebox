#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "keypad.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

static const char keypad_map[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// GPIO1: P1_0 to P1_7 (rows: P1_0–P1_3, cols: P1_4–P1_7)
static const uint32_t row_pins[KEYPAD_ROWS] = {0, 1, 2, 3}; // P1_0–P1_3
static const uint32_t col_pins[KEYPAD_COLS] = {4, 5, 6, 7}; // P1_4–P1_7

void Keypad_Init(void) {
    // Enable PORT1 clock and release from reset
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT1(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT1(1);

    gpio_pin_config_t row_config = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t col_config = {kGPIO_DigitalInput, 0};

    // Init row pins
    for (int i = 0; i < KEYPAD_ROWS; i++) {
        PORT1->PCR[row_pins[i]] = (PORT1->PCR[row_pins[i]] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1);
        GPIO_PinInit(GPIO1, row_pins[i], &row_config);
        GPIO_PinWrite(GPIO1, row_pins[i], 1);
    }

    // Init column pins with pull-up
    for (int j = 0; j < KEYPAD_COLS; j++) {
        PORT1->PCR[col_pins[j]] = (PORT1->PCR[col_pins[j]] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1);
        PORT1->PCR[col_pins[j]] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
        GPIO_PinInit(GPIO1, col_pins[j], &col_config);
    }
}


char Keypad_GetKey(void) {
    for (int i = 0; i < KEYPAD_ROWS; i++) {
        // Set all rows HIGH
        for (int r = 0; r < KEYPAD_ROWS; r++)
            GPIO_PinWrite(GPIO1, row_pins[r], 1);

        // Pull one row LOW to scan
        GPIO_PinWrite(GPIO1, row_pins[i], 0);

        // Check all columns
        for (int j = 0; j < KEYPAD_COLS; j++) {
            if (!GPIO_PinRead(GPIO1, col_pins[j])) {
                // Simple debounce
                while (!GPIO_PinRead(GPIO1, col_pins[j]));
                return keypad_map[i][j];
            }
        }
    }
    return 0; // No key pressed
}

char Keypad_Scan(void) {
    return Keypad_GetKey();
}
