/*
 * utils.c
 *
 *  Created on: 7 Jun 2025
 *      Author: adibh
 */
/*
 * utils.c
 *
 *  Created on: 4 Jun 2025
 *      Author: adibh
 */


#include "utils.h"
#include "fsl_clock.h"  // Needed for NXP SDK-based devices

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        for (count = 0; count < 4000; count++) {
            __asm("NOP");
        }
    }
}


