#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;

void Display_Process(void);



void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}