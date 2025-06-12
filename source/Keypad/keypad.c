#include "keypad.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "fsl_reset.h"

const uint8_t row_pins[KEYPAD_ROWS] = {12, 13, 14, 15}; // GPIO1_12 to 15
const uint8_t col_pins[KEYPAD_COLS] = {29, 11, 6, 7};   // GPIO1_29, 11, 6, 7

static const char keymap[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void Keypad_Init(void)
{
    // Enable clock and release reset for PORT1
	CLOCK_EnableClock(kCLOCK_GateGPIO1);
    RESET_ReleasePeripheralReset(kGPIO1_RST_SHIFT_RSTn);
    RESET_ReleasePeripheralReset(kPORT1_RST_SHIFT_RSTn);

    gpio_pin_config_t row_config = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t col_config = {kGPIO_DigitalInput, 0};

    for (int i = 0; i < KEYPAD_ROWS; i++)
    {
        PORT1->PCR[row_pins[i]] = (PORT1->PCR[row_pins[i]] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1);
        GPIO_PinInit(GPIO1, row_pins[i], &row_config);
        GPIO_PinWrite(GPIO1, row_pins[i], 1);
    }

    for (int i = 0; i < KEYPAD_COLS; i++)
    {
        PORT1->PCR[col_pins[i]] = (PORT1->PCR[col_pins[i]] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1);
        GPIO_PinInit(GPIO1, col_pins[i], &col_config);
    }
}

char Keypad_Scan(void)
{
    for (int row = 0; row < KEYPAD_ROWS; row++)
    {
        // Set all rows high
        for (int i = 0; i < KEYPAD_ROWS; i++)
            GPIO_PinWrite(GPIO1, row_pins[i], 1);

        // Pull current row low
        GPIO_PinWrite(GPIO1, row_pins[row], 0);

        for (int col = 0; col < KEYPAD_COLS; col++)
        {
            if (GPIO_PinRead(GPIO1, col_pins[col]) == 0)
            {
                // simple debounce delay
                for (volatile int d = 0; d < 10000; d++);
                if (GPIO_PinRead(GPIO1, col_pins[col]) == 0)
                    return keymap[row][col];
            }
        }
    }
    return 0;
}
