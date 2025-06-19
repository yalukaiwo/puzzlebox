/*
 * Leds.h
 *
 *  Created on: Jun 17, 2025
 *      Author: yalukaiwo
 */

#ifndef UTILS_LEDS_H_
#define UTILS_LEDS_H_

#include <stdint.h>

void Leds_init(void);
void Leds_on(uint8_t led_number);
void Leds_off(uint8_t led_number);
void Leds_allOn();
void Leds_allOff();


#endif /* UTILS_LEDS_H_ */
