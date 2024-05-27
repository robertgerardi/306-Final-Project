//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupts for Switches
//
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
extern volatile unsigned char update_display;
extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
extern volatile unsigned char display_changed;

//------------------------------------------------------------------------------
// Port 4 interrupt for switch 1, it is disabled for the duration
// of the debounce time. Debounce time is set for 1 second
#pragma vector=PORT4_VECTOR
__interrupt void switch1_interrupt(void) {
// Switch 1
if (P4IFG & SW1) {
  

P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
P4IE &= ~SW1;  // disables interrupt 
TB0CCR1 = TB0R + TB0CCR1_INTERVAL; // adds interval time
TB0CCTL1 |= CCIE; //rennables CCTL1 interrupt



}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
// Port 2 interrupt for switch 2, it is disabled for the duration
// of the debounce time. Debounce time is set for 1 second
#pragma vector=PORT2_VECTOR
__interrupt void switch2_interrupt(void) {
// Switch 2
if (P2IFG & SW2) {
  /*
1. Disable Switch 2
2. Clear Switch 2 Flag
3. Clear TimerB0 Interrupt Flag for Capture Compare Register 2
4. Add Interval to TB0R for TB0CCR2
5. Enable TimerB0_2
*/
  
P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
P2IE &= ~SW2; 
TB0CCR2 = TB0R + TB0CCR2_INTERVAL;
TB0CCTL2 |= CCIE; 







}
}
//