#include "led_control.h"
#include "MCXA153.h"

void leds_init(void) {
    // Set as output: LED1 - P3_1, LED2 - P3_13, LED3 - P3_12, LED4 - P2_5
    GPIO3->PDDR |= (1 << 1) | (1 << 13) | (1 << 12);  // P3_1, P3_13, P3_12
    GPIO2->PDDR |= (1 << 5);                         // P2_5

    // Set as GPIO mode
    PORT3->PCR[1] = PORT_PCR_MUX(1);
    PORT3->PCR[13] = PORT_PCR_MUX(1);
    PORT3->PCR[12] = PORT_PCR_MUX(1);
    PORT2->PCR[5] = PORT_PCR_MUX(1);
}

void led_on(uint8_t led_number) {
    switch (led_number) {
        case 1: GPIO3->PCOR = (1 << 1); break;
        case 2: GPIO3->PCOR = (1 << 13); break;
        case 3: GPIO3->PCOR = (1 << 12); break;
        case 4: GPIO2->PCOR = (1 << 5); break;
    }
}

void led_off(uint8_t led_number) {
    switch (led_number) {
        case 1: GPIO3->PSOR = (1 << 1); break;
        case 2: GPIO3->PSOR = (1 << 13); break;
        case 3: GPIO3->PSOR = (1 << 12); break;
        case 4: GPIO2->PSOR = (1 << 5); break;
    }
}
