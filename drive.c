#include "macros.h"
#include  "functions.h"
#include  "msp430.h"

extern unsigned int Last_Time_Sequence; // a variable to identify Time_Sequence has changed
extern unsigned int cycle_time; // is a new time base used to control making shapes
extern unsigned int time_change;// is an identifier that a change has occurred
extern char event;

unsigned int right_motor_count;
unsigned int left_motor_count;
unsigned int segment_count;
unsigned int delay_start;
char state = WAIT;
unsigned int count = 0;



/*void Forward_On(void){
  
  Motor_off();
  
  
}*/

void Motor_check(void){
  
  if(RIGHT_FORWARD_SPEED > 0 && RIGHT_REVERSE_SPEED > 0){
    
       RIGHT_FORWARD_SPEED = 0;
       RIGHT_REVERSE_SPEED = 0;
       LEFT_FORWARD_SPEED = 0;
       LEFT_REVERSE_SPEED = 0;
    
  }
  
  if(LEFT_FORWARD_SPEED > 0 && LEFT_REVERSE_SPEED > 0){
    
       RIGHT_FORWARD_SPEED = 0;
       RIGHT_REVERSE_SPEED = 0;
       LEFT_FORWARD_SPEED = 0;
       LEFT_REVERSE_SPEED = 0;
    
  }
  
 }
  


void Motor_off(void){
  P6OUT &= ~L_FORWARD;
  P6OUT &= ~R_FORWARD;
  P6OUT &= ~L_REVERSE;
  P6OUT &= ~R_REVERSE;
  
}

void Forward_Right(void){
  
  
  P6OUT |= R_FORWARD;
  
  
  
}
  
void Forward_Left(void){
  
  P6OUT |=  L_FORWARD;
  
}

void Reverse_Left(void){
 
  P6OUT |=  L_REVERSE;
  

}
void Reverse_Right(void){
  
  P6OUT |=  R_REVERSE;
  
}



void Run_Circle(void){
 switch(state){
 case WAIT: // Begin
 wait_case();
 break; //
 case START: // Begin
 start_case();
 break; //
 case RUN: // Run
 run_CIRCLE_case();
 break; //
 case END: // End
 end_case();
 break; //
 default: break;
 }
}

void run_CIRCLE_case(void){
 if(time_change){
 time_change = 0;
 if(segment_count <= TRAVEL_CIRCLE_DISTANCE){
 if(right_motor_count++ >= RIGHT_CIRCLE_COUNT_TIME){
 P6OUT &= ~R_FORWARD; 
 }
 if(left_motor_count++ >= LEFT_CIRCLE_COUNT_TIME){
 P6OUT &= ~L_FORWARD; 
 }
 if(cycle_time >= WHEEL_CIRCLE_COUNT_TIME){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
 segment_count++;
 Forward_Move();
 }
 }else{
 state = END;
 }
 }
}

void Run_Figure8(void){
 switch(state){
 case WAIT: // Begin
 wait_case();
 break; //
 case START: // Begin
 start_case();
 break; //
 case RUN: // Run
 run_FIGURE8_case();
 break; //
 case RUN2:
 run_FIGURE8_case2();
 break;
 case END: // End
 end_case();
 break; //
 default: break;
 }
}

void run_FIGURE8_case(void){
 if(time_change){
 time_change = 0;
 if(segment_count <= TRAVEL_FIGURE8_DISTANCE){
 if(right_motor_count++ >= RIGHT_FIGURE8_COUNT_TIME){
 P6OUT &= ~R_FORWARD; 
 }
 if(left_motor_count++ >= LEFT_FIGURE8_COUNT_TIME){
 P6OUT &= ~L_FORWARD; 
 }
 if(cycle_time >= WHEEL_FIGURE8_COUNT_TIME){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
 segment_count++;
 Forward_Move();
 }
 }else{
 state = RUN2;
 segment_count = 0;
 }
 }
}

void run_FIGURE8_case2(void){
 if(time_change){
 time_change = 0;
 if(segment_count <= TRAVEL_FIGURE8_DISTANCE2){
 if(right_motor_count++ >= RIGHT_FIGURE8_COUNT_TIME2){
 P6OUT &= ~R_FORWARD; 
 }
 if(left_motor_count++ >= LEFT_FIGURE8_COUNT_TIME2){
 P6OUT &= ~L_FORWARD; 
 }
 if(cycle_time >= WHEEL_FIGURE8_COUNT_TIME){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
 segment_count++;
 Forward_Move();
 }
 }else if(count < ONE){
   count++;
 state = RUN;    // need to test this code
 segment_count = 0;
 
 }
 else{
  
   state = END;
 }
}
}


void Run_Triangle(void){
 switch(state){
 case WAIT: // Begin
 wait_case();
 break; //
 case START: // Begin
 start_case();
 break; //
 case RUN: // Run
 run_TRIANGLE_case();
 break; //
 case RUN2:
 run_TRIANGLE_case2();
 break;
 case END: // End
 end_case();
 break; //
 default: break;
 }
}

void run_TRIANGLE_case(void){
 if(time_change){
 time_change = 0;
 if(segment_count <= TRAVEL_TRIANGLE_DISTANCE){
 if(right_motor_count++ >= RIGHT_TRIANGLE_COUNT_TIME){
 P6OUT &= ~R_FORWARD; 
 }
 if(left_motor_count++ >= LEFT_TRIANGLE_COUNT_TIME){
 P6OUT &= ~L_FORWARD; 
 }
 if(cycle_time >= WHEEL_TRIANGLE_COUNT_TIME){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
 segment_count++;
 Forward_Move();
 }
 }else{
 state = RUN2;
 segment_count = 0;
 }
 }
}

void run_TRIANGLE_case2(void){
 if(time_change){
 time_change = 0;
 if(segment_count <= TRAVEL_TRIANGLE_DISTANCE2){
 if(right_motor_count++ >= RIGHT_TRIANGLE_COUNT_TIME2){
 P6OUT &= ~R_FORWARD; 
 }
 if(left_motor_count++ >= LEFT_TRIANGLE_COUNT_TIME2){
 P6OUT &= ~L_FORWARD; 
 }
 if(cycle_time >= WHEEL_TRIANGLE_COUNT_TIME){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
 segment_count++;
 Forward_Move();
 }
 }else if(count < 5){
   count++;
 state = RUN;    // need to test this code
 segment_count = 0;
 
 }
 else{
   
   state = END;
 }
}
}

void wait_case(void){
 if(time_change){
 time_change = 0;
 if(delay_start++ >= WAITING2START){
 delay_start = 0;
 state = START;
 }
 }
}

void start_case(void){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
// Forward_On();
 segment_count = 0;
 state = RUN;
}



void end_case(void){
 Forward_Off();
 state = WAIT;
 event = NONE;
}
