/*
 * Buttons.h
 *
 *  Created on: 5 Jun 2025
 *      Author: adibh
 */

#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

void buttons_init(void);
bool button_is_pressed(uint8_t button_number);

#endif

