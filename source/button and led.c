#include "led_control.h"
#include "MCXA153.h"

int main(void) {
    leds_init();

    // Button pins: P3_0, P2_4, P1_5, P1_4 as input
    GPIO3->PDDR &= ~(1 << 0);  // P3_0
    GPIO2->PDDR &= ~(1 << 4);  // P2_4
    GPIO1->PDDR &= ~(1 << 5);  // P1_5
    GPIO1->PDDR &= ~(1 << 4);  // P1_4

    // Set as GPIO mode
    PORT3->PCR[0] = PORT_PCR_MUX(1);
    PORT2->PCR[4] = PORT_PCR_MUX(1);
    PORT1->PCR[5] = PORT_PCR_MUX(1);
    PORT1->PCR[4] = PORT_PCR_MUX(1);

    while (1) {
        // Button 1
        if (!(GPIO3->PDIR & (1 << 0))) led_on(1); else led_off(1);
        // Button 2
        if (!(GPIO2->PDIR & (1 << 4))) led_on(2); else led_off(2);
        // Button 3
        if (!(GPIO1->PDIR & (1 << 5))) led_on(3); else led_off(3);
        // Button 4
        if (!(GPIO1->PDIR & (1 << 4))) led_on(4); else led_off(4);
    }
}
