//------------------------------------------------------------------------------
//
//  Description: This file contains the display process commands to update the LCD
//
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------


#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;

void Display_Process(void);



void Display_Process(void){ //this function updates the display
  if(update_display){
    update_display = FLASE; 
    if(display_changed){
      display_changed = FALSE;
      Display_Update(CLEAR,CLEAR,CLEAR,CLEAR);
    }
  }
}