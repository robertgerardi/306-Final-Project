//------------------------------------------------------------------------------
//
//  Description: This file contains the initilization for the ADC sensors and emitter
//              and the HEXtoBCD function to show ADC values
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

char adc_char[4];
extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
extern volatile unsigned char display_changed;
void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
ADCCTL0 = CLEAR; // Reset
ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
ADCCTL0 |= ADCMSC; // MSC
ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
ADCCTL2 = CLEAR; // Reset
ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
ADCCTL2 = CLEAR; // Reset
ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
ADCCTL0 |= ADCENC; // ADC enable conversion.
ADCCTL0 |= ADCSC; // ADC start conversion.
}

//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(int hex_value){
int value;
for(int i=BEGINNING; i < LASTLINE; i++) {
adc_char[i] = '0';
}
while (hex_value > HEXCUTOFF999){   
hex_value = hex_value - HUNDREDSPLACE;
value = value + ONE;
adc_char[FIRSTCHAR] = BCDASCII + value;
} 
value = CLEAR;
while (hex_value > HEXCUTOFF99){                        //this code takes the values gathered by the ADC and converts it to BCD
hex_value = hex_value - TENSPLACE;
value = value + ONE;
adc_char[SECONDCHAR] = BCDASCII + value;
}
value = CLEAR;
while (hex_value > HEXCUTOFF9){
hex_value = hex_value - ONESPLACE;
value = value + ONE;
adc_char[THIRDCHAR] = BCDASCII + value;
}
adc_char[FOURTHCHAR] = BCDASCII + hex_value;
}
//-----------------------------------------------------------------
//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it 
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){  
//-------------------------------------------------------------
int i;
unsigned int real_line;
real_line = line - ONE;
for(i=BEGINNING; i < LASTLINE; i++) {
display_line[real_line][i+location] = adc_char[i];
}
display_changed = TRUE;
}
//----