#include "buzzer_pwm.h"
#include "MCXA153.h"

void delay_ms(uint32_t ms);

void buzzer_pwm_init(void) {
    SysTick_Config(48000); // 1ms tick

    // Configure P3_14 as PWM output (CTIMER2_MAT1)
    PORT3->PCR[14] = PORT_PCR_MUX(2); // Alt2 for CTIMER2_MAT1
    GPIO3->PDDR |= (1 << 14);

    // Setup CTIMER2
    CTIMER2->PR = 4;        // Prescale
    CTIMER2->MR[1] = 50;    // Match register for PWM
    CTIMER2->PWMC = (1 << 1);   // Enable PWM on channel 1
    CTIMER2->MCR = (1 << 3);    // Reset on MR1
    CTIMER2->TCR = 1;       // Enable timer
}

void buzzer_beep_error(void) {
    CTIMER2->EMR = (3 << 6); // Toggle output
    delay_ms(300);
    CTIMER2->EMR = 0;
}

void buzzer_beep_win(void) {
    for (int i = 0; i < 3; i++) {
        CTIMER2->EMR = (3 << 6); // Toggle output
        delay_ms(150);
        CTIMER2->EMR = 0;
        delay_ms(150);
    }
}
