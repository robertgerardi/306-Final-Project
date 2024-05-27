//------------------------------------------------------------------------------
//
//  Description: This file contains the interrupts for ADC black line detection
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

unsigned int ADC_Channel = ZERO;
extern unsigned int ADC_Left_Detect = ZERO;
extern unsigned int ADC_Right_Detect = ZERO;
unsigned int ADC_Thumb = ZERO;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
case ADCIV_NONE:
break;
case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
// before its previous conversion result was read.
break;
case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
break;
case ADCIV_ADCHIIFG: // Window comparator interrupt flags
break;
case ADCIV_ADCLOIFG: // Window comparator interrupt flag
break;
case ADCIV_ADCINIFG: // Window comparator interrupt flag
break;
case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
ADCCTL0 &= ~ADCENC; // Disable ENC bit.
switch (ADC_Channel++){
case LEFTDETECT: // Channel A2 Interrupt
ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
ADC_Left_Detect = ADCMEM0; // Move result into Global
ADC_Left_Detect = ADC_Left_Detect >> TWO; // Divide the result by 4

break;
case RIGHTDETECT
ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
ADC_Right_Detect = ADCMEM0; // Move result into Global
ADC_Right_Detect = ADC_Right_Detect >> TWO; // Divide the result by 4

break;
case TURNWHEEL:
  
ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
ADCMCTL0 |= ADCINCH_2; // Enable Next channel A2
ADC_Thumb = ADCMEM0; // Move result into Global
ADC_Thumb = ADC_Thumb >> TWO; // Divide the result by 4

ADC_Channel=CLEAR;
break;
default:
break;
}
ADCCTL0 |= ADCENC; // Enable Conversions
ADCCTL0 |= ADCSC;
break;
default:
break;
}
}
