/*
 * Buttons.c
 *
 *  Created on: 7 Jun 2025
 *      Author: adibh
 */
#include "Buttons.h"
#include "MCXA153.h"

void buttons_init(void) {
    GPIO3->PDDR &= ~(1 << 0);
    GPIO2->PDDR &= ~(1 << 4);
    GPIO1->PDDR &= ~(1 << 5);
    GPIO1->PDDR &= ~(1 << 4);

    PORT3->PCR[0] = PORT_PCR_MUX(1);
    PORT2->PCR[4] = PORT_PCR_MUX(1);
    PORT1->PCR[5] = PORT_PCR_MUX(1);
    PORT1->PCR[4] = PORT_PCR_MUX(1);
}

bool button_is_pressed(uint8_t button_number) {
    switch (button_number) {
        case 1: return !(GPIO3->PDIR & (1 << 0));
        case 2: return !(GPIO2->PDIR & (1 << 4));
        case 3: return !(GPIO1->PDIR & (1 << 5));
        case 4: return !(GPIO1->PDIR & (1 << 4));
        default: return false;
    }
}



