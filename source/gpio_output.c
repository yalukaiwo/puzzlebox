/*
 * gpio_output.c
 *
 *  Created on: Apr 11, 2025
 *      Author: yalukaiwo
 */

#include "gpio_output.h"

void gpio_output_init(void)
{
    // GPIO3: [1] = Peripheral clock is enabled
    // PORT3: [1] = Peripheral clock is enabled
    MRCC0->MRCC_GLB_CC1 |= MRCC_MRCC_GLB_CC1_GPIO1(1);
    MRCC0->MRCC_GLB_CC0 |= MRCC_MRCC_GLB_CC0_PORT1(1);

    // GPIO3: [1] = Peripheral is released from reset
    // PORT3: [1] = Peripheral is released from reset
    MRCC0->MRCC_GLB_RST1 |= MRCC_MRCC_GLB_RST1_GPIO1(1);
    MRCC0->MRCC_GLB_RST0 |= MRCC_MRCC_GLB_RST0_PORT1(1);

    //
    // Configure P1_5
    // LK : [1] = Locks this PCR
    // INV: [0] = Does not invert
    // IBE: [0] = Disables
    // MUX: [0000] = Alternative 0 (GPIO)
    // DSE: [0] = low drive strength is configured on the corresponding pin,
    //            if the pin is configured as a digital output
    // ODE: [0] = Disables
    // SRE: [0] = Fast
    // PE:  [0] = Disables
    // PS:  [0] = n.a.
    PORT1->PCR[7] |= PORT_PCR_LK(1) | PORT_PCR_MUX(0);

    // From section 12.5 Initialization (NXP, 2024)
    //
    // 1. Initialize the GPIO pins for the output function:
    //    a. Configure the output logic value for each pin by using Port Data
    //       Output (PDOR).
    //    b. Configure the direction for each pin by using Port Data Direction
    //       (PDDR).
    // 2. Interrupt function not used.

    // 1. a.
    //
    // PDO13: [1] = Logic level 1 – LEDs off
    GPIO1->PCOR = (1 << 7);
}
