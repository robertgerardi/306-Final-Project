#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

unsigned int sw1_position = RELEASED;
unsigned int okay_to_look_at_switch1 = OKAY;
unsigned int count_debounce_SW1;
extern char event;
char prev_event;
extern char display_line[4][11];
extern volatile unsigned char display_changed;
//------------------------------------------------------------------------------
void Switches_Process (void){
//------------------------------------------------------------------------------
// This function calls the individual Switch Functions
//------------------------------------------------------------------------------
Switch1_Process();

} 
//--


void Switch1_Process(void){
//------------------------------------------------------------------------------
// Switch 1 Configurations
//------------------------------------------------------------------------------
if (okay_to_look_at_switch1 && sw1_position){
if (!(P4IN & SW1)){
sw1_position = PRESSED;
okay_to_look_at_switch1 = NOT_OKAY;
count_debounce_SW1 = DEBOUNCE_RESTART;
 if (event == IDLE){
        event = CIRCLE;
        prev_event = CIRCLE;
        strcpy(display_line[0], "  CIRCLE  ");
        strcpy(display_line[1], "          ");
        strcpy(display_line[2], "   STATE  ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
      }
      else if (prev_event == CIRCLE){
        event = FIGURE8;
        prev_event = FIGURE8;
        strcpy(display_line[0], "   FIG 8  ");
        strcpy(display_line[1], "          ");
        strcpy(display_line[2], "   STATE  ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
      }
      else if (prev_event == FIGURE8){
        event = TRIANGLE;
        prev_event = TRIANGLE;
        strcpy(display_line[0], " TRIANGLE ");
        strcpy(display_line[1], "          ");
        strcpy(display_line[2], "   STATE  ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
      }

}
}
if (count_debounce_SW1 <= DEBOUNCE_TIME){
count_debounce_SW1++;
}else{
okay_to_look_at_switch1 = OKAY;
if (P4IN & SW1){
sw1_position = RELEASED;
}
}
}
//-----