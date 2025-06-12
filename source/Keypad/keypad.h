#ifndef KEYPAD_H
#define KEYPAD_H

#include "fsl_gpio.h"
#include <stdint.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

extern const uint8_t row_pins[KEYPAD_ROWS];
extern const uint8_t col_pins[KEYPAD_COLS];

void Keypad_Init(void);
char Keypad_Scan(void);

#endif
