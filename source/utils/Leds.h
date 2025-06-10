/*
 * Leds.h
 *
 *  Created on: 5 Jun 2025
 *      Author: adibh
 */

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdint.h>

void leds_init(void);
void led_on(uint8_t led_number);
void led_off(uint8_t led_number);

#endif

