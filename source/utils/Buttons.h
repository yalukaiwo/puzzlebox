/*
 * button.h
 *
 *  Created on: 12 Jun 2025
 *      Author: Adib
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <MCXA153.h>
#include <stdbool.h>

void Buttons_init(void);               // Initializes all 4 buttons
bool Buttons_isPressed(int index);        // Check if specific button (0–3) is pressed
bool Buttons_isAnyPressed(void);          // Check if any button is pressed

#endif /* BUTTONS_H_ */
