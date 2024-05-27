//------------------------------------------------------------------------------
//
//  Description: This file contains the initilization for display and LEDS
//
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
extern char *display[NUMBEROFLINES];
extern volatile unsigned char update_display;



void Init_LEDs(void);
void Init_Conditions(void);

void Init_Conditions(void){  // initilizes display
//------------------------------------------------------------------------------

  int i;
  for(i=BEGINNING;i<DISPLAYLENGTH;i++){
    display_line[FIRSTLINE][i] = RESET_STATE;
    display_line[SECONDLINE][i] = RESET_STATE;
    display_line[THIRDLINE][i] = RESET_STATE;
    display_line[FOURTHLINE][i] = RESET_STATE;
  }
  display_line[FIRSTLINE][LASTCHARFORDISPLAY] = CLEAR;
  display_line[SECONDLINE][LASTCHARFORDISPLAY] = CLEAR;
  display_line[THIRDLINE][LASTCHARFORDISPLAY] = CLEAR;
  display_line[FOURTHLINE][LASTCHARFORDISPLAY] = CLEAR;

  display[FIRSTLINE] = &display_line[FIRSTLINE][CLEAR];
  display[SECONDLINE] = &display_line[SECONDLINE][CLEAR];
  display[THIRDLINE] = &display_line[THIRDLINE][CLEAR];
  display[FOURTHLINE] = &display_line[FOURTHLINE][CLEAR];
  update_display = FALSE;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}