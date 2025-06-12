/*
 * button.c
 *
 *  Created on: 12 Jun 2025
 *      Author: adibh
 */
// buttons.c
// Utility module for handling multiple button inputs
// Author: Adib
// Date: June 2025

#include "button.h"

// -----------------------------------------------------------------------------
// Local type definitions
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Local function prototypes
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Local variables
// -----------------------------------------------------------------------------
static volatile uint32_t button_flags[4] = {0};

// -----------------------------------------------------------------------------
// Local function implementation
// -----------------------------------------------------------------------------
void gpio_input_init(void)
{
    // From section 14.3 Functional description (NXP, 2024)
    //
    // Before a module can be used, its clocks must be enabled (CC != 00) and it
    // must be released from reset (MRCC_GLB_RST [peripherals name] = 1). If a
    // module is not released from reset (MRCC_GLB_RST [peripherals name] = 0),
    // an attempt to access a register within that module is terminated with a
    // bus error.

    // Enable modules and leave others unchanged
    // PORT1: [1] = Peripheral clock is enabled
    // GPIO1: [1] = Peripheral clock is enabled
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT1(1);
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT2(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_PORT3(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_GPIO1(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_GPIO2(1);
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_GPIO3(1);

    // Release modules from reset and leave others unchanged
    // PORT1: [1] = Peripheral is released from reset
    // GPIO1: [1] = Peripheral is released from reset
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT1(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT2(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_PORT3(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO1(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO2(1);
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_GPIO3(1);

    // From section 11.4 Initialization (NXP, 2024)
    //
    // 1. Initialize the pin functions:
    //    -  Initialize single pin functions by writing appropriate values to
    //       PCRn
    //    -  Initialize multiple pins (up to 16) with the same configuration by
    //       writing appropriate values to Global Pin Control Low (GPCLR) or
    //       Global Pin Control High (GPCHR).
    // 2. Lock the configuration for a given pin, by writing 1 to PCRn [LK], so
    //    that it cannot be changed until the next reset.

    // 1. & 2.
    //
    // Configure pin P3_0
    PORT3->PCR[0] = PORT_PCR_LK(1) | PORT_PCR_IBE(1) | PORT_PCR_MUX(0);

    // Configure pin P2_4
    PORT2->PCR[4] = PORT_PCR_LK(1) | PORT_PCR_IBE(1) | PORT_PCR_MUX(0);

    // Configure pin P1_5
    PORT1->PCR[5] = PORT_PCR_LK(1) | PORT_PCR_IBE(1) | PORT_PCR_MUX(0);

    // Configure pin P1_4
    PORT1->PCR[4] = PORT_PCR_LK(1) | PORT_PCR_IBE(1) | PORT_PCR_MUX(0);

    // From section 12.5 Initialization (NXP, 2024)
    //
    // 1. n.a.
    // 2. Initialize the interrupt function by writing to Interrupt Control a
    //    (ICR0 - ICR31) for the corresponding pins and desired configuration.
    //    If the pin is previously used for a different function, first write
    //    0100_0000h to Interrupt Control a (ICR0 - ICR31) to disable the
    //    previous function and clear the flag.

    // 2.
    //
    // ISF: [1] = Clear the flag
    // IRQC : [1010] = ISF and interrupt on falling edge
    GPIO3->ICR[0] = GPIO_ICR_ISF(1) | GPIO_ICR_IRQC(0b1010);
    GPIO2->ICR[4] = GPIO_ICR_ISF(1) | GPIO_ICR_IRQC(0b1010);
    GPIO1->ICR[5] = GPIO_ICR_ISF(1) | GPIO_ICR_IRQC(0b1010);
    GPIO1->ICR[4] = GPIO_ICR_ISF(1) | GPIO_ICR_IRQC(0b1010);

    // Enable GPIO interrupts
    NVIC_SetPriority(GPIO3_IRQn, 3);
    NVIC_ClearPendingIRQ(GPIO3_IRQn);
    NVIC_EnableIRQ(GPIO3_IRQn);

    NVIC_SetPriority(GPIO2_IRQn, 3);
    NVIC_ClearPendingIRQ(GPIO2_IRQn);
    NVIC_EnableIRQ(GPIO2_IRQn);

    NVIC_SetPriority(GPIO1_IRQn, 3);
    NVIC_ClearPendingIRQ(GPIO1_IRQn);
    NVIC_EnableIRQ(GPIO1_IRQn);

    // Globally enable interrupts
    __enable_irq();
}

bool Buttons_isPressed(int index)
{
    if (index < 0 || index > 3) return false;

    if (button_flags[index]) {
        button_flags[index] = 0;
        return true;
    }
    return false;
}

bool Buttons_isAnyPressed(void)
{
    for (int i = 0; i < 4; i++) {
        if (button_flags[i]) {
            button_flags[i] = 0;
            return true;
        }
    }
    return false;
}

void GPIO3_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(GPIO3_IRQn);

    if((*(volatile uint32_t *)&GPIO3->ISFR & (1 << 0)) != 0)
    {
        *(volatile uint32_t *)&GPIO3->ISFR = (1 << 0);
        button_flags[0] = 1;
    }
}

void GPIO2_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(GPIO2_IRQn);

    if((*(volatile uint32_t *)&GPIO2->ISFR & (1 << 4)) != 0)
    {
        *(volatile uint32_t *)&GPIO2->ISFR = (1 << 4);
        button_flags[1] = 1;
    }
}

void GPIO1_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(GPIO1_IRQn);

    if((*(volatile uint32_t *)&GPIO1->ISFR & (1 << 5)) != 0)
    {
        *(volatile uint32_t *)&GPIO1->ISFR = (1 << 5);
        button_flags[2] = 1;
    }

    if((*(volatile uint32_t *)&GPIO1->ISFR & (1 << 4)) != 0)
    {
        *(volatile uint32_t *)&GPIO1->ISFR = (1 << 4);
        button_flags[3] = 1;
    }
}
