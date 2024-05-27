//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupts for timer B0 and B1
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

extern volatile unsigned int interrupt_counter = ZERO;
extern volatile unsigned int timerfordisplay = ZERO;
extern volatile unsigned int blacklinetimer = ZERO;
extern volatile unsigned int countDBS1 = ZERO;
extern volatile unsigned int countDBS2 = ZERO;
extern volatile unsigned char update_display;
extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
extern volatile unsigned char display_changed;
extern volatile unsigned int blkline_detect = ZERO;
extern volatile unsigned int Tangent_on = ZERO;

extern volatile unsigned int TimerFlag = ZERO;
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------

 interrupt_counter = interrupt_counter + TEN_MS_COUNT; // interrupt counter incrementing by 1 (10ms) used for various timing purposes
  
 timerfordisplay = timerfordisplay + TEN_MS_COUNT; // timer that is used to display seconds onto the screen
 TimerFlag = TRUE; // timer flag to display time to screen and perform HEXtoBCD Operations
 
 blacklinetimer = blacklinetimer + TEN_MS_COUNT; // timer used to navigate the black line
  
update_display = TRUE;
TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
//----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
case 0: break; // No interrupt
case 2: // CCR1 not used
//...... Add What you need happen in the interrupt ......

  if (countDBS1++ > DEBOUNCE_TIME){ //Swtich 1 debounce timer, if its debounced then the switch interrupt is reenabled 
  TB0CCTL1 &= ~CCIE; // CCR1 enable interrupt
  P4IFG &= ~SW1;
  P4IE |= SW1;
  countDBS1 = ZERO;
  


   
  
}

TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
break;
case 4: // CCR2 not used

  if (countDBS2++ > DEBOUNCE_TIME){ //Swtich 2 debounce timer, if its debounced then the switch interrupt is reenabled 
  TB0CCTL2 &= ~CCIE; // CCR1 enable interrupt
  P2IFG &= ~SW2;
  P2IE |= SW2;
  
  countDBS2 = ZERO;
  
  
 
}
TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR1
break;
case 14: // overflow
//...... Add What you need happen in the interrupt ......
break;
default: break; 
}
//----------------------------------------------------------------------------
}