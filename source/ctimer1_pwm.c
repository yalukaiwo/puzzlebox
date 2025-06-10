/*
 * ctimer1_pwm.c
 *
 *  Created on: 7 Jun 2025
 *      Author: adibh
 */
#include "ctimer1_pwm.h"
#include "fsl_clock.h"
#include "fsl_iocon.h"
#include "fsl_ctimer.h"

#define CTIMER            CTIMER1
#define CTIMER_MAT_OUT    kCTIMER_Match_0
#define PWM_FREQ_HZ       5000

void PWM_Init(void) {
    CLOCK_EnableClock(kCLOCK_Ctimer1);
    IOCON_PinMuxSet(IOCON, 3, 14, IOCON_FUNC4); // P3_14 as CTIMER1_MAT0

    ctimer_config_t config;
    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(CTIMER, &config);

    CTIMER_SetupPwm(CTIMER, CTIMER_MAT_OUT, PWM_FREQ_HZ, 0.5f, false);
    CTIMER_StartTimer(CTIMER);
}

void PWM_SetDutyCycle(uint8_t dutyCyclePercent) {
    float dutyCycle = (float)dutyCyclePercent / 100.0f;
    CTIMER_UpdatePwmDutycycle(CTIMER, CTIMER_MAT_OUT, dutyCycle);
}
