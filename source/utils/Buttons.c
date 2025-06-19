/*
 * button.c
 *
 *  Created on: 12 Jun 2025
 *      Author: Adib
 */

#include "Buttons.h"

// -----------------------------------------------------------------------------
// Local function implementation
// -----------------------------------------------------------------------------
void Buttons_init(void)
{
    // Enable clock for PORT and GPIO
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT1(1);
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT2(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_PORT3(1);

    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_GPIO1(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_GPIO2(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_GPIO3(1);

    // Release from reset
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT1(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT2(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_PORT3(1);

    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO1(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO2(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO3(1);

    // Set pin function to GPIO and enable internal pull-up (if needed)
    PORT3->PCR[0] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1); // Button 0 - P3_0
    PORT2->PCR[4] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1); // Button 1 - P2_4
    PORT1->PCR[5] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1); // Button 2 - P1_5
    PORT1->PCR[4] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1); // Button 3 - P1_4

    // Set direction to input (clear bit = input)
    GPIO3->PDDR &= ~(1 << 0);  // P3_0
    GPIO2->PDDR &= ~(1 << 4);  // P2_4
    GPIO1->PDDR &= ~(1 << 5);  // P1_5
    GPIO1->PDDR &= ~(1 << 4);  // P1_4
}

bool Buttons_isPressed(int index)
{
    switch(index) {
        case 0: return !(GPIO3->PDIR & (1 << 0));  // Active low
        case 1: return !(GPIO2->PDIR & (1 << 4));
        case 2: return !(GPIO1->PDIR & (1 << 5));
        case 3: return !(GPIO1->PDIR & (1 << 4));
        default: return false;
    }
}

bool Buttons_isAnyPressed(void)
{
    return Buttons_isPressed(0) || Buttons_isPressed(1) ||
           Buttons_isPressed(2) || Buttons_isPressed(3);
}
