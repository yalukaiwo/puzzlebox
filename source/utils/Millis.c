/*
 * Millis.c
 *
 *  Created on: Jun 13, 2025
 *      Author: yalukaiwo
 */


#include "Millis.h"

static volatile long ms = 0;

void Millis_init() {
	SysTick_Config(48000);
}

long millis() {
	return ms;
}

void SysTick_Handler(void)
{
    ms++;
}
