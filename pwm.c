//------------------------------------------------------------------------------
//
//  Description: This file contains the initilization for timer B3 and PWM
//
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"


void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 R_FORWARD
// TB3.2 P6.1 R_REVERSE
// TB3.3 P6.2 L_FORWARD
// TB3.4 P6.3 L_REVERSE
//------------------------------------------------------------------------------
TB3CTL = TBSSEL__SMCLK; // SMCLK
TB3CTL |= MC__UP; // Up Mode
TB3CTL |= TBCLR; // Clear TAR
TB3CCR0 = WHEEL_PERIOD; // PWM Period
TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM duty cycle
TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.1 Right Reverse PWM duty cycle
TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.2 Left Forward PWM duty cycle
TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}

