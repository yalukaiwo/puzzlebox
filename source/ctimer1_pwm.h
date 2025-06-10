/*
 * ctimer1_pwm.h
 *
 *  Created on: 5 Jun 2025
 *      Author: adibh
 */

#ifndef CTIMER1_PWM_H_
#define CTIMER1_PWM_H_

#include <stdint.h>

void PWM_Init(void);
void PWM_SetDutyCycle(uint8_t dutyCyclePercent);

#endif /* CTIMER1_PWM_H_ */
