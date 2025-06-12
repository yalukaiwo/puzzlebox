/*
 * buzzer.c
 *
 *  Created on: 12 Jun 2025
 *      Author: adibh
 */
#include "buzzer.h"
#include "ctimer1_pwm.h"

void Buzzer_buzz(int intensity)
{
    if (intensity < 0) intensity = 0;
    if (intensity > 1000) intensity = 1000;

    CTIMER1->MR[2] = 1000 - intensity;
    CTIMER1->MR[3] = 1000 - 1;

    CTIMER1->PWMC |= CTIMER_PWMC_PWMEN3(1) | CTIMER_PWMC_PWMEN2(1);
}


