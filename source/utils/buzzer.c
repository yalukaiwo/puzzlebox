/*
 * buzzer.c
 *
 *  Created on: 12 Jun 2025
 *      Author: adibh
 */
#include <utils/Buzzer.h>

void Buzzer_init() {
	// MUX: [101] = CLK_1M
	    MRCC0->MRCC_CTIMER2_CLKSEL = MRCC_MRCC_CTIMER2_CLKSEL_MUX(0b101);

	    // HALT: [0] = Divider clock is running
	    // RESET: [0] = Divider isn't reset
	    // DIV: [0000] = divider value = (DIV+1) = 1
	    MRCC0->MRCC_CTIMER2_CLKDIV = 0;

	    // 2.
	    //
	    // CTIMER1_CLK_EN: [1] = CTIMER 1 function clock enabled
	    SYSCON->CTIMERGLOBALSTARTEN |= SYSCON_CTIMERGLOBALSTARTEN_CTIMER2_CLK_EN(1);

	    // 3.
	    //
	    // Enable modules and leave others unchanged
	    // CTIMER1: [1] = Peripheral clock is enabled
	    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_CTIMER2(1);

	    // Release modules from reset and leave others unchanged
	    // CTIMER1: [1] = Peripheral is released from reset
	    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_CTIMER2(1);

	    // 4.
	    //
	    // Not used

	    // 5.
	    //
	    // Specifies the prescale value. 1 MHz / 10 = 100 kHz
	    CTIMER2->PR = 10-1;

	    // Match value: 100 kHz / 100 = 1 kHz
	    //
	    // In PWM mode, use match channel 3 to set the PWM cycle length. The other
	    // channels can be used for matches
	    CTIMER2->MR[2] = 1000;
	    CTIMER2->MR[3] = 1000-1;

	    // MR2S: [0] = Does not stop Timer Counter (TC) if MR0 matches Timer Counter
	    //             (TC)
	    // MR2R: [0] = Resets Timer Counter (TC) if MR0 matches its value.
	    // MR2I: [0] = No interrupt when MR0 matches the value in Timer
	    //             Counter (TC).
	    // MR3S: [0] = Does not stop Timer Counter (TC) if MR3 matches Timer Counter
	    //             (TC)
	    // MR3R: [1] = Resets Timer Counter (TC) if MR3 matches its value.
	    // MR3I: [0] = No interrupt when MR3 matches the value in Timer
	    //             Counter (TC).
	    CTIMER2->MCR |= CTIMER_MCR_MR3R(1);

	    // Configure match outputs as PWM outputs.
	    CTIMER2->PWMC |= CTIMER_PWMC_PWMEN3(1) | CTIMER_PWMC_PWMEN2(1);

	    // Enable modules and leave others unchanged
	    // PORT3: [1] = Peripheral clock is enabled
	    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT2(1);

	    // Release modules from reset and leave others unchanged
	    // PORT3: [1] = Peripheral is released from reset
	    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT2(1);

	    // Configure P3_12
	    // LK : [1] = Locks this PCR
	    // INV: [0] = Does not invert
	    // IBE: [0] = Disables
	    // MUX: [0100] = Alternative 4 (CT1_MAT2)
	    // DSE: [0] = low drive strength is configured on the corresponding pin,
	    //            if the pin is configured as a digital output
	    // ODE: [0] = Disables
	    // SRE: [0] = Fast
	    // PE:  [0] = Disables
	    // PS:  [0] = n.a.
	    PORT2->PCR[2] = PORT_PCR_LK(1) | PORT_PCR_MUX(5);
	    // 6.
	    //
	    // Not used.

	    // CEN: [1] = Enables the counters.
	    CTIMER2->TCR |= CTIMER_TCR_CEN(1);
}

void Buzzer_buzz(int intensity)
{
    if (intensity < 0) intensity = 0;
    if (intensity > 1000) intensity = 1000;

    CTIMER2->MR[2] = 1000 - intensity;
}


