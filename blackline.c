//------------------------------------------------------------------------------
//
//  Description: This file contains the black line navigation state machine
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

extern volatile unsigned int timerfordisplay;
extern volatile unsigned int blacklinetimer;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int blacklinestate = ONE;
unsigned int blacklinetemp;
unsigned int timereset = TRUE;
extern volatile unsigned char display_changed;
extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
unsigned int whitedetect = FALSE;
void blacklinenavigation(void){
  
  
  switch(blacklinestate){
    
    
  case TIMEWAITSTATE:
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
    }
    
    if(blacklinetimer>= FIVESEC){
      
      blacklinestate = blacklinetemp + ONE;
      
      timereset = TRUE;
    }
    break;
    
  case STARTMOVEMENT:
    strcpy(display_line[SECONDLINE], "          ");
    strcpy(display_line[THIRDLINE], " BL START ");
      display_changed = TRUE;
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
    }
    
    
    
    if(blacklinetimer>= THREESEC){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      timereset = TRUE;
    }else{
      
     RIGHT_FORWARD_SPEED = FASTERWHEELSPEED;
     LEFT_FORWARD_SPEED = FASTERWHEELSPEED;
      
    }
    break;
  case TURNTOBOARD:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
    }
    
    
    
    if(blacklinetimer>= ONESEC){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      timereset = TRUE;
      Init_ADC();
    }else{
      
     RIGHT_FORWARD_SPEED = FASTWHEELSPEED;
    
      
    }
    
    
    break;
    
    case BLACKLINEDETECTION:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
    }
    
    if(ADC_Left_Detect < WHITE_AREA2 && ADC_Right_Detect < WHITE_AREA2){
      
    whitedetect = TRUE;
     
    }
    
    if(ADC_Left_Detect > BLACK_LINE && ADC_Right_Detect > BLACK_LINE && whitedetect ){
      strcpy(display_line[THIRDLINE], "INTERCEPT ");
        display_changed = TRUE;
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      timereset = TRUE;
    }else{
      
     RIGHT_FORWARD_SPEED = FASTWHEELSPEED;
     LEFT_FORWARD_SPEED = SLOWWHEELSPEED;
      
    }
    
    
    break;
    case BLACKLINEADJUST :  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
    }
    
    
    if(blacklinetimer>= ONESEC){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      timereset = TRUE;
      Init_ADC();
    }else{
      
     LEFT_FORWARD_SPEED = FASTWHEELSPEED;
     RIGHT_FORWARD_SPEED = FASTWHEELSPEED;
    
      
    }
    
    
    break;
    
    case TURNONTOBLACKLINE:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
    }
    
    strcpy(display_line[THIRDLINE], " BL TURN  ");
      display_changed = TRUE;
    
    
    if(ADC_Right_Detect > BLACK_LINE){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      timereset = TRUE;
    }else{
      
     RIGHT_REVERSE_SPEED = SLOWWHEELSPEED;
     LEFT_FORWARD_SPEED = SLOWWHEELSPEED;
      
    }
    
    
    break;
    
    case BLACKLINETRAVEL:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
      RIGHT_FORWARD_SPEED = SLOWWHEELSPEED;
      LEFT_FORWARD_SPEED = SLOWWHEELSPEED;
    }
    
    
    strcpy(display_line[THIRDLINE], "BL TRAVEL ");
      display_changed = TRUE;
     if(ADC_Left_Detect < WHITE_AREA && ADC_Right_Detect > BLACK_LINE2){
      
     
     
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_FORWARD_SPEED = SLOWWHEELSPEED;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      
    }
    if(ADC_Left_Detect > BLACK_LINE2 && ADC_Right_Detect < WHITE_AREA){
      
      
     
      RIGHT_FORWARD_SPEED = SLOWWHEELSPEED;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      
    }
  if(ADC_Left_Detect > BLACK_LINE && ADC_Right_Detect > BLACK_LINE){
      
      
     
      RIGHT_FORWARD_SPEED = SLOWWHEELSPEED;
      LEFT_FORWARD_SPEED = SLOWWHEELSPEED;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      
    }
   
    
    if(blacklinetimer >= TENSEC){
      strcpy(display_line[THIRDLINE], " CIRCLE ");
      display_changed = TRUE;
      
    }
    
    
    break;
    
     case EXITCIRCLE1:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
      
    }
    
    
    strcpy(display_line[THIRDLINE], " BL EXIT  ");
      display_changed = TRUE;
    
    if(blacklinetimer>= ONESEC){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      timereset = TRUE;
     
    }
     
    
    
    break;
    
    case EXITCIRCLE2:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
      
    }
    
    
    if(blacklinetimer>= ONESEC){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      timereset = TRUE;
     
    }else{
       RIGHT_FORWARD_SPEED = FASTWHEELSPEED;
      LEFT_REVERSE_SPEED = FASTWHEELSPEED;
      
    }
     
    
    
   
    break;
    case STOPCARFINAL:  
    
    if(timereset == TRUE){
      blacklinetimer = RESETTIME;
      timereset = FALSE;
      
    }
    
    
    if(blacklinetimer>= THREESEC){
      
      blacklinetemp = blacklinestate;
      blacklinestate = ZERO;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
      timereset = TRUE;
      strcpy(display_line[THIRDLINE], " BL STOP  ");
      display_changed = TRUE;
     
    }else{
       RIGHT_FORWARD_SPEED = FASTWHEELSPEED;
      LEFT_FORWARD_SPEED = FASTWHEELSPEED;
      
    }
     
    
    
    break;
  }
  
  
  
  
  
  
  
  
}