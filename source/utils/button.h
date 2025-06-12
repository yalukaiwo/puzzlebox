/*
 * button.h
 *
 *  Created on: 12 Jun 2025
 *      Author: adibh
 */

// buttons.h
#ifndef BUTTON_H_
#define BUTTON_H_

#include <MCXA153.h>
#include <stdbool.h>

void gpio_input_init(void);               // Initializes all 4 buttons
bool Buttons_isPressed(int index);        // Check if specific button (0–3) is pressed
bool Buttons_isAnyPressed(void);          // Check if any button is pressed

#endif /* BUTTON_H_ */

