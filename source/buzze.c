#include <MCXA153.h>
#include <stdint.h>

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        count = 10000;
        while (count--) __NOP();
    }
}

void buzzer_pwm_init(void) {
    SysTick_Config(48000); // 1ms tick

    // Clock for CTIMER2
    MRCC0->MRCC_CTIMER2_CLKSEL = MRCC_MRCC_CTIMER2_CLKSEL_MUX(0b101);
    MRCC0->MRCC_CTIMER2_CLKDIV = 0;
    SYSCON->CTIMERGLOBALSTARTEN |= SYSCON_CTIMERGLOBALSTARTEN_CTIMER2_CLK_EN(1);

    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_CTIMER2(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_CTIMER2(1);

    CTIMER2->PR = 4;
    CTIMER2->MR[1] = 50;
    CTIMER2->MR[3] = 100 - 1;

    CTIMER2->MCR |= CTIMER_MCR_MR3R(1);
    CTIMER2->PWMC |= CTIMER_PWMC_PWMEN1(1);

    // Enable and set P1_11 to ALT4 (CTIMER2_MAT1)
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT1(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT1(1);
    PORT1->PCR[11] = PORT_PCR_LK(1) | PORT_PCR_MUX(4); // ALT4 for PWM
}

void buzzer_on(void) {
    // Set to PWM mode (ALT4) and start timer
    PORT1->PCR[11] = PORT_PCR_LK(1) | PORT_PCR_MUX(4);
    CTIMER2->TCR |= CTIMER_TCR_CEN(1);
}

void buzzer_off(void) {
    CTIMER2->TCR &= ~CTIMER_TCR_CEN(1); // Stop timer

    // Reconfigure P1_11 as GPIO
    PORT1->PCR[11] = PORT_PCR_LK(1) | PORT_PCR_MUX(0); // ALT0 = GPIO

    // Set P1_11 as output and drive LOW
    GPIO1->PDDR |= (1 << 11);   // Set as output
    GPIO1->PCOR = (1 << 11);    // Clear output (drive LOW)
}


int main(void) {
    buzzer_pwm_init();

    while (1) {
        buzzer_on();  // Sound
        delay_ms(2000);

        buzzer_off(); // Silence
        delay_ms(2000);
    }
}
