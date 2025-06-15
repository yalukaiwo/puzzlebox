#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

void Keypad_Init(void);
char Keypad_Scan(void);

#endif
