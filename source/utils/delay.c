#include "utils/delay.h"
#include "cmsis_gcc.h"

#include <stdint.h>

extern volatile long ms;

void Delay_ms(uint32_t delay_ms)
{
    long start = ms;
    while ((ms - start) < delay_ms) {
        __NOP(); // Prevent aggressive compiler optimization
    }
}
