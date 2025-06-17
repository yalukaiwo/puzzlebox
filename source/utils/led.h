/*
 * led_control.h
 *
 *  Created on: 13 Jun 2025
 *      Author: adibh
 */

#ifndef LED_H
#define LED_H

#include <stdint.h>

void leds_init(void);
void led_on(uint8_t led_number);
void led_off(uint8_t led_number);

#endif

