/*! ***************************************************************************
 *
 * \brief     Source for buzzer driver
 * \file      buzzer.c
 * \author    Hugo Arends (extended)
 * \date      February 2024
 *
 * \see       NXP. (2024). MCX A153, A152, A143, A142 Reference Manual. Rev. 4,
 *            01/2024. From:
 *            https://www.nxp.com/docs/en/reference-manual/MCXAP64M96FS3RM.pdf
 *
 * \copyright 2024 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************/

#include "buzzer.h"

// -----------------------------------------------------------------------------
// Function implementation
// -----------------------------------------------------------------------------

void Buzzer_buzz(int intensity_percent)
{
    if (intensity_percent < 0)
        intensity_percent = 0;
    else if (intensity_percent > 100)
        intensity_percent = 100;

    // Luka instructed to ensure correct MUX setup for PWM0_X2 on P3_14
    // This sets the correct pin function (ALT5) only once
    MRCC0->MRCC_GLB_CC1_SET = MRCC_MRCC_GLB_CC1_PORT3(1);    // Enable clock for PORT3
    MRCC0->MRCC_GLB_RST1_SET = MRCC_MRCC_GLB_RST1_PORT3(1);  // Release reset for PORT3
    PORT3->PCR[14] = PORT_PCR_MUX(5);  // Set P3_14 as PWM0_X2 (ALT5)

    // Convert intensity percentage to PWM duty cycle value
    uint16_t duty = (uint16_t)((intensity_percent * 1000) / 100);

    // Set the duty cycle on match register (MAT2 = VAL2)
    PWM0->SM[2].VAL2 = -duty;
}
