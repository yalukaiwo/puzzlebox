
#include "lcdDriver/delay.h"
#include "fsl_device_registers.h"
#include "Keypad/fsl_debug_console.h"
#include "Keypad/fsl_clock.h"

void Delay_us(uint32_t us) {
    uint32_t cycles_per_us = CLOCK_GetCoreSysClkFreq() / 1000000;
    for (volatile uint32_t i = 0; i < (us * cycles_per_us / 5); i++) {
        __NOP();
    }
}

void Delay_ms(uint32_t ms) {
    Delay_us(ms * 1000);
}
