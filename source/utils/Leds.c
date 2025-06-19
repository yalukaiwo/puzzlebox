/*
 * Leds.c
 *
 *  Created on: Jun 17, 2025
 *      Author: yalukaiwo
 */


#include "MCXA153.h"

void Leds_init(void) {
    GPIO3->PDDR |= (1 << 1) | (1 << 13) | (1 << 12);
    GPIO2->PDDR |= (1 << 5);

    PORT3->PCR[1] = PORT_PCR_MUX(0) | PORT_PCR_LK(1);
    PORT3->PCR[13] = PORT_PCR_MUX(0) | PORT_PCR_LK(1);
    PORT3->PCR[12] = PORT_PCR_MUX(0) |  PORT_PCR_LK(1);
    PORT2->PCR[5] = PORT_PCR_MUX(0) | PORT_PCR_LK(1);

	GPIO3->PSOR = (1 << 1);
    GPIO3->PSOR = (1 << 13);
    GPIO3->PSOR = (1 << 12);
    GPIO2->PSOR = (1 << 5);
}

void Leds_on(uint8_t led_number) {
    switch (led_number) {
        case 0: GPIO3->PCOR = (1 << 1); break;
        case 1: GPIO3->PCOR = (1 << 13); break;
        case 2: GPIO3->PCOR = (1 << 12); break;
        case 3: GPIO2->PCOR = (1 << 5); break;
    }
}

void Leds_off(uint8_t led_number) {
    switch (led_number) {
        case 0: GPIO3->PSOR = (1 << 1); break;
        case 1: GPIO3->PSOR = (1 << 13); break;
        case 2: GPIO3->PSOR = (1 << 12); break;
        case 3: GPIO2->PSOR = (1 << 5); break;
    }
}


void Leds_allOn() {
	Leds_on(1);
	Leds_on(2);
	Leds_on(3);
	Leds_on(0);
}

void Leds_allOff() {
	Leds_off(1);
	Leds_off(2);
	Leds_off(3);
	Leds_off(0);
}
