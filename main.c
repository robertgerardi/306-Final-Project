//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System and
// IOT command processing 
//
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"


// Function Prototypes
void main(void);



  // Global Variables
volatile char slow_input_down;
extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
extern char *display[NUMBEROFLINES];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;




extern volatile unsigned int blkline_detect;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;


extern volatile unsigned int interrupt_counter;
extern volatile unsigned int timerfordisplay;

extern  char IOT_2_PC[LARGE_RING_SIZE];
extern  char PC_2_IOT[LARGE_RING_SIZE];
extern volatile unsigned int iot_rx_wr;
extern volatile unsigned int usb_rx_wr;
extern unsigned int iot_rx_rd;
extern unsigned int usb_rx_rd;
unsigned int commandEN;

char TempBuffer2[LARGE_RING_SIZE];
unsigned int i;
extern unsigned int sendtransmission;
extern unsigned int direct_iot;
unsigned int processcommand;
unsigned int timeflag;
unsigned int timewait;
unsigned int commandpos = ZERO;
unsigned int secondcommand = FALSE;
unsigned int counttemp = RESETTIME;

unsigned int singleseconds = ZERO;
unsigned int tenseconds = ZERO;
unsigned int hundredseconds = ZERO;

unsigned int blacklineflag = ZERO;
extern unsigned int blacklinestate;
extern volatile unsigned int TimerFlag;

unsigned int arrivedcount = ZERO;

char FirstIP[SEVEN];
char SecondIP[SEVEN];
void IOT_Process(void){
  
  if(timeflag == TRUE){ // if the time flag is enabled, it goes into the wait state
      
      
      if(interrupt_counter >= timewait){
        RIGHT_FORWARD_SPEED = WHEEL_OFF; // when the wait time has been reached, the it turns off all motor functions
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        
      }
      if(interrupt_counter >= timewait + ONESEC){ // waits one second before disableing the wait state s
        timeflag = FALSE;                              // to make sure I am not blowing FETs
        
      }
      
    }
  
  else if(processcommand == FALSE) { // if we are not processing a command, we are receiving the commannd the command it putting it into the 
                                     // the temp buffer for processing
  
  unsigned int iot_rx_wr_temp;
  
  iot_rx_wr_temp = iot_rx_wr;
  
  if(iot_rx_wr_temp != iot_rx_rd){
    
    TempBuffer[i] = IOT_2_PC[iot_rx_rd++];
    
    if(iot_rx_rd >= LARGE_RING_SIZE){
      iot_rx_rd = BEGINNING;
    }
    
    if(TempBuffer[i] == LINEFEED){
      i = ZERO;
      processcommand = TRUE;                    // this code will go through the IOT_2_PC buffer and copy it to process buffer
    }else{                                      // when it hits a linefeed, it starts processing the command
      i++;
    }
    
  }
  }
  else{
    
    if(secondcommand == TRUE){                  //if 2 commands were sent at once, it sets a flag to move the pointer to the next 
                                                // position so that it can process the next  command
      
      commandpos = commandpos + TWO;
    }else{
      
       for(int j = BEGINNING; j < LARGE_RING_SIZE; j++){
      
      if(TempBuffer[j] == '^'){                         // if there is no second command is enabled yet, it finds the position of the first command
        commandpos = j;
        break;
      }
      
    }
    
      
      
    }
    
   
    
    if(TempBuffer[FIVE] == 'G'){
     
        strcpy(PC_2_IOT,"AT+CIPMUX=1\r\n"); //detects G in fifth position, if it is there from WIFI GOT IP, it sends next command
        
      
        usb_rx_wr = LENGTHOFMESSAGE1;
        usb_rx_rd = BEGINNING;        // sets the read and write pointers and enables the UCA0 interrupt to send to IOT
        UCA0IE |= UCTXIE;     
        
        
        
        
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }
      }
      else if(TempBuffer[EIGHT] == 'X'){
        direct_iot = BEGINNING;
        strcpy(PC_2_IOT,"AT+CIPSERVER=1,1612\r\n");
        
      
        usb_rx_wr = LENGTHOFMESSAGE2;,  // sets the read and write pointers and enables the UCA0 interrupt to send to IOT
        usb_rx_rd = BEGINNING; 
        UCA0IE |= UCTXIE;   
        
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }
      } 
    else if(TempBuffer[NINE] == 'V'){
        direct_iot = BEGINNING;
        strcpy(PC_2_IOT,"AT+CIFSR\r\n");
        
      
        usb_rx_wr = LENGTHOFMESSAGE3;
        usb_rx_rd = BEGINNING;   // sets the read and write pointers and enables the UCA0 interrupt to send to IOT
        UCA0IE |= UCTXIE;   
        
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }
      } 
      else if(TempBuffer[IPPOSITION] == '"'){ // this picks up the beginning of the message for the IP Address 
        direct_iot = BEGINNING;
        unsigned int tempcounter = BEGINNING;
        for(int k = FIRSTHALFIP1; k < FIRSTHALFIP2; k++){
          if( (TempBuffer[k] <= '9' && TempBuffer[k] >= '0') || TempBuffer[k] == '.'){ // pulls the first half of the IP Address 
          FirstIP[tempcounter] = TempBuffer[k];
          tempcounter++; 
          }
        }
        tempcounter = BEGINNING;
        for(int k = SECONDHALFIP2; k < SECONDHALFIP2; k++){
          if((TempBuffer[k] <= '9' && TempBuffer[k] >= '0') || TempBuffer[k] == '.') { // pulls second half of the ip address
          SecondIP[tempcounter] = TempBuffer[k];
          tempcounter++; }
        }
        strcpy(display_line[SECONDLINE], FirstIP); // puts the first half on line 2 of display
        strcpy(display_line[THIRDLINE], SecondIP); // puts the second half on line 3 of display
        display_changed = TRUE;
        update_display = TRUE;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }
      }
      else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'F' ){
         
        RIGHT_FORWARD_SPEED = FASTERWHEELSPEED;
        LEFT_FORWARD_SPEED = FASTERWHEELSPEED;
        interrupt_counter = RESETTIME;
    
       
        display_line[FOURTHLINE][COMMANDCHAR] = 'F';
        if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
        
      else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'B' ){
         
        RIGHT_REVERSE_SPEED = SLOWWHEELSPEED;
        LEFT_REVERSE_SPEED = SLOWWHEELSPEED;
        interrupt_counter = RESETTIME;
        timeflag = TRUE;
        timewait = ONESEC;
        display_line[FOURTHLINE][COMMANDCHAR] = 'B';
        if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'R' ){
         
        RIGHT_REVERSE_SPEED = SLOWWHEELSPEED;
        LEFT_FORWARD_SPEED = SLOWWHEELSPEED;
        interrupt_counter = RESETTIME;
        timeflag = TRUE;
        timewait = TURNTIME;
        display_line[FOURTHLINE][COMMANDCHAR] = 'R';
       if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'L' ){
         
        RIGHT_FORWARD_SPEED = SLOWWHEELSPEED;
        LEFT_REVERSE_SPEED = SLOWWHEELSPEED;
        interrupt_counter = RESETTIME;
        timeflag = TRUE;
        timewait = TURNTIME;
        display_line[FOURTHLINE][COMMANDCHAR] = 'L';
        if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'I' ){
         
        blacklineflag = BEGININTERCEPT;
      
        interrupt_counter = RESETTIME;
       
        timewait = ONESEC;
        display_line[FOURTHLINE][COMMANDCHAR] = 'A';
         display_line[FOURTHLINE][COMMANDCHAR2] = 'U';
          display_line[FOURTHLINE][COMMANDCHAR3] = 'T';
           display_line[FOURTHLINE][COMMANDCHAR4] = 'O';
        if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'S' ){
         
        blacklineflag = STOPCAR;
      
        interrupt_counter = RESETTIME;
        timeflag = TRUE;
        timewait = ONESEC;
        
        if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'X' ){
         
        
      
        interrupt_counter = RESETTIME;
        timeflag = TRUE;
        timewait = STOPCAR;
        
        if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    else if(TempBuffer[commandpos] == '^' && TempBuffer[commandpos + ONE] == 'C' ){
         
        arrivedcount++; 
      display_line[FIRSTLINE][COMMANDCHAR5] = BCDASCII + arrivedcount;
      
      
        interrupt_counter = RESETTIME;
        timeflag = TRUE;
        timewait = ONESEC;
        display_line[FOURTHLINE][COMMANDCHAR] = 'C';
        display_changed = TRUE;
       if(secondcommand == FALSE && TempBuffer[commandpos + TWO] == '^'){
          secondcommand = TRUE;
      
        }
         else{
          secondcommand = FALSE;
        commandpos = BEGINNING;
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }}
      }
    
      else {
        for(int j = BEGINNING; j < sizeof(TempBuffer); j++){ // clears process buffer and sets process command flag to false
          
          
          TempBuffer[j] = CLEAR;
          processcommand = FALSE;
        }
        
        
      
      
    }
    
  
}

}
void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
PM5CTL0 &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timer_B0();  
  Init_Timer_B3();                     // Initialize Timers
  Init_LCD();                          // Initialize LCD
  

 

// This line identifies the text on the Display is to change.
  display_changed = TRUE;

  
  Init_Serial_UCA1('a');// Initialize Serial Port for USB
  Init_Serial_UCA0('a');// Initialize Serial Port for USB
   


//----------------------------------------------------------------------------


  
  
  strcpy(display_line[FIRSTLINE], "ARRIVED   ");
        display_changed = TRUE;
  
  
  
 
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run

    Display_Process();                 // Update Display
    P3OUT ^= TEST_PROBE;        // Change State of TEST_PROBE OFF
    

    if(TimerFlag == TRUE) { // once timer flag
      TimerFlag = FALSE;
      
      if(timerfordisplay < ONESPLACE){
        
        display_line[FOURTHLINE][COMMANDCHAR5] = 's';
      }
    if(timerfordisplay % TEN == ZERO){
      
      singleseconds++;
      if(singleseconds > NINE)
      {
        singleseconds = ZERO;
      }
      display_line[FOURTHLINE][SINGLESECCHAR] = BCDASCII + singleseconds;
      
      display_changed = TRUE;
    }
    if(timerfordisplay % TENSPLACE == ZERO){
      
      tenseconds++;
      if(tenseconds > NINE)
      {
        tenseconds = ZERO;
      }
      display_line[FOURTHLINE][TENSECCHAR] = BCDASCII + tenseconds;
      display_changed = TRUE;
    }
    if(timerfordisplay % HUNDREDSPLACE == ZERO){
      
      hundredseconds++;
      if(hundredseconds > NINE)
      {
        hundredseconds = ZERO;
      }
      display_line[FOURTHLINE][HUNDREDSECCHAR] = BCDASCII + hundredseconds;
      display_changed = TRUE;
    }
    } 
    
    switch(interrupt_counter){
       
    case FIVESEC:
      P3OUT |= IOT_EN_CPU; // enable IOT and LED to process commands
      P2OUT |= IOT_RUN_CPU;
      
      break;
     
    }
    
    
    IOT_Process(); // check for command
    
    
    if(blacklineflag == BEGIN){ // begin black line navigation
      
      blacklinenavigation();
      
      
    } if(blacklineflag == STOPCAR){ // black line navigation stops
      
      blacklinestate = SEVEN;
      blacklineflag = TRUE;
      
    } 
  
  
   
   
   
    
//------------------------------------------------------------------------------

}




}



      
    
    
    
    
    
  
  
  
  
  
  
  



