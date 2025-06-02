#include "buzzer_pwm.h"
#include "MCXA153.h"

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        count = 10000;
        while (count--) __NOP();
    }
}

void buzzer_pwm_init(void) {
    SysTick_Config(48000);  // 1ms tick

    // Clock setup for CTIMER2
    MRCC0->MRCC_CTIMER2_CLKSEL = MRCC_MRCC_CTIMER2_CLKSEL_MUX(0b101);
    MRCC0->MRCC_CTIMER2_CLKDIV = 0;
    SYSCON->CTIMERGLOBALSTARTEN |= SYSCON_CTIMERGLOBALSTARTEN_CTIMER2_CLK_EN(1);

    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_CTIMER2(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_CTIMER2(1);

    CTIMER2->PR = 4;
    CTIMER2->MR[1] = 50;         // Duty cycle
    CTIMER2->MR[3] = 100 - 1;    // Period

    CTIMER2->MCR |= CTIMER_MCR_MR3R(1);
    CTIMER2->PWMC |= CTIMER_PWMC_PWMEN1(1);

    // Enable and configure P3_14 as CTIMER2_MAT1 (ALT4)
    MRCC0->MRCC_GLB_CC0_SET = (1U << 3);   // Enable clock for PORT3
    MRCC0->MRCC_GLB_RST0_SET = (1U << 3);  // Release reset for PORT3
    PORT3->PCR[14] = PORT_PCR_LK(1) | PORT_PCR_MUX(4); // Set ALT4
}

void buzzer_on(void) {
    PORT3->PCR[14] = PORT_PCR_LK(1) | PORT_PCR_MUX(4); // PWM Mode
    CTIMER2->TCR |= CTIMER_TCR_CEN(1); // Enable Timer
}

void buzzer_off(void) {
    CTIMER2->TCR &= ~CTIMER_TCR_CEN(1); // Disable Timer
    PORT3->PCR[14] = PORT_PCR_LK(1) | PORT_PCR_MUX(0); // GPIO Mode
    GPIO3->PDDR |= (1 << 14);   // Output
    GPIO3->PCOR = (1 << 14);    // Drive LOW
}
