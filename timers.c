//------------------------------------------------------------------------------
//
//  Description: This file initializes Timer B0
//
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

//------------------------------------------------------------------------------
// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
void Init_Timer_B0(void) {
TB0CTL = TBSSEL__SMCLK; // SMCLK source
TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
TB0CTL |= MC__CONTINOUS; // Continuous up
TB0CTL |= ID__2; // Divide clock by 2
TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
TB0CCTL0 |= CCIE; // CCR0 enable interrupt
// TB0CCR1 = TB0CCR1_INTERVAL; // CCR1 
// TB0CCTL1 |= CCIE; // CCR1 enable interrupt
// TB0CCR2 = TB0CCR2_INTERVAL; // CCR2 
// TB0CCTL2 |= CCIE; // CCR2 enable interrupt
TB0CTL &= ~TBIE; // Disable Overflow Interrupt
TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}
//-