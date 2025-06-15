#include "keypad.h"
#include "fsl_device_registers.h"

// Your final pin map
static const uint8_t row_pins[KEYPAD_ROWS]  = {10, 11, 12, 13};     // PORT1
static const uint8_t col_ports[KEYPAD_COLS] = {2, 2, 3, 3};
static const uint8_t col_pins[KEYPAD_COLS]  = {0, 29, 30, 31};      // PORT2 + PORT3

static const char keymap[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void Keypad_Init(void) {
    // Enable clocks for PORT1, PORT2, PORT3
    MRCC0->MRCC_GLB_CC0_SET  = (1 << 1) | (1 << 2) | (1 << 3);
    MRCC0->MRCC_GLB_RST0_CLR = (1 << 1) | (1 << 2) | (1 << 3);

    // Configure ROWS (PORT1) as outputs
    for (int i = 0; i < KEYPAD_ROWS; i++) {
        PORT1->PCR[row_pins[i]] &= ~PORT_PCR_MUX_MASK;
        PORT1->PCR[row_pins[i]] |= PORT_PCR_MUX(1);
        GPIO1->PDDR |= (1 << row_pins[i]);     // Set as output
        GPIO1->PSOR  = (1 << row_pins[i]);     // Set high
    }

    // Configure COLUMNS (PORT2 + PORT3) as inputs with pull-up
    for (int i = 0; i < KEYPAD_COLS; i++) {
        if (col_ports[i] == 2) {
            PORT2->PCR[col_pins[i]] &= ~PORT_PCR_MUX_MASK;
            PORT2->PCR[col_pins[i]] |= PORT_PCR_MUX(1);
            PORT2->PCR[col_pins[i]] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
            GPIO2->PDDR &= ~(1 << col_pins[i]);
        } else if (col_ports[i] == 3) {
            PORT3->PCR[col_pins[i]] &= ~PORT_PCR_MUX_MASK;
            PORT3->PCR[col_pins[i]] |= PORT_PCR_MUX(1);
            PORT3->PCR[col_pins[i]] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
            GPIO3->PDDR &= ~(1 << col_pins[i]);
        }
    }
}

char Keypad_Scan(void) {
    for (int row = 0; row < KEYPAD_ROWS; row++) {
        // Set all rows high
        for (int i = 0; i < KEYPAD_ROWS; i++)
            GPIO1->PSOR = (1 << row_pins[i]);

        // Pull current row low
        GPIO1->PCOR = (1 << row_pins[row]);

        for (int col = 0; col < KEYPAD_COLS; col++) {
            uint32_t pin_mask = (1 << col_pins[col]);
            uint32_t pin_state;

            if (col_ports[col] == 2)
                pin_state = GPIO2->PDIR & pin_mask;
            else
                pin_state = GPIO3->PDIR & pin_mask;

            if (!pin_state) {
                for (volatile int d = 0; d < 100000; d++);  // Longer debounce

                // Re-read pin state properly
                if (col_ports[col] == 2)
                    pin_state = GPIO2->PDIR & pin_mask;
                else
                    pin_state = GPIO3->PDIR & pin_mask;

                if (!pin_state) {
                    return keymap[row][col];
                }
            }


        }
    }
    return '\0'; // No key pressed
}
