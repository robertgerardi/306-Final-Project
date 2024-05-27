//------------------------------------------------------------------------------
//
//  Description: This file contains the inilization for the serial commmunication 
//  ports and the interrupts for UCA0 and USA1
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



extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
volatile char USB_Char_Rx[LARGE_RING_SIZE];
volatile char USB_Char_Tx[LARGE_RING_SIZE];

extern unsigned int sendtransmission;
volatile unsigned int UCA0_index;
extern char display_line[NUMBEROFLINES][NUMBEROFCHARS];
volatile unsigned int TRANSMIT = FALSE;


// Serial
  char IOT_2_PC[LARGE_RING_SIZE];
  char PC_2_IOT[LARGE_RING_SIZE];
volatile unsigned int iot_rx_wr = BEGINNING;
 volatile unsigned int usb_rx_wr = BEGINNING;
 unsigned int iot_rx_rd=BEGINNING;
 unsigned int usb_rx_rd=BEGINNING;

extern unsigned int sendtransmission;


unsigned int direct_iot;
unsigned int direct_usb;

void Init_Serial_UCA1(char speed){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
UCA1CTLW0 = CLEAR;
UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
UCA1CTLW0 &= ~UCPEN; // No Parity
UCA1CTLW0 &= ~UCSYNC;
UCA1CTLW0 &= ~UC7BIT;
UCA1CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
if(speed == 'a'){
UCA1BRW = 4 ; // 115,200 baud
UCA1MCTLW = 0x5551 ; }
if(speed == 'b'){
  UCA1BRW = 17 ; // 460800 baud
  UCA1MCTLW = 0x4A00 ; } 
  
UCA1CTLW0 &= ~UCSWRST ; // release from reset

UCA1IE |= UCRXIE; // Enable RX interrupt
//------------------------------------------------------------------------------
}


void Init_Serial_UCA0(char speed){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
UCA0CTLW0 = CLEAR;
UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
UCA0CTLW0 &= ~UCPEN; // No Parity
UCA0CTLW0 &= ~UCSYNC;
UCA0CTLW0 &= ~UC7BIT;
UCA0CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
if(speed == 'a'){
UCA0BRW = 4 ; // 115,200 baud
UCA0MCTLW = 0x5551 ; }
if(speed == 'b'){
  UCA0BRW = 17 ; // 460800 baud
  UCA0MCTLW = 0x4A00 ; } 
  
UCA0CTLW0 &= ~UCSWRST ; // release from reset

UCA0IE |= UCRXIE; // Enable RX interrupt
//------------------------------------------------------------------------------
}

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
//-----------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
  unsigned int temp;
switch(__even_in_range(UCA0IV,0x08)){
case ZERO: break; // Vector 0 - no interrupt
case RXIE:{ // Vector 2 - RXIFG
temp = iot_rx_wr++;
IOT_2_PC[temp] = UCA0RXBUF; // Rx -> IOT_2_PC character array
if (iot_rx_wr >= (LARGE_RING_SIZE)){
iot_rx_wr = BEGINNING; // Circular buffer back to beginning
}

UCA1IE |= UCTXIE; // Enable Tx interrupt
}break;
case TXIE:{ // Vector 4 - TXIFG
UCA0TXBUF = PC_2_IOT[direct_iot++];
if (direct_iot >= (sizeof(PC_2_IOT))){
direct_iot = BEGINNING;
}
if (direct_iot == usb_rx_wr){
UCA0IE &= ~UCTXIE; // Disable TX interrupt
}
}break;
default: break;
}
//------------------------------------------------------------------------------
}


#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
//------------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
  unsigned int temp;
switch(__even_in_range(UCA1IV,0x08)){
case ZERO: break; // Vector 0 - no interrupt
case RXIE:{ // Vector 2 - RXIFG
temp = usb_rx_wr++;
PC_2_IOT[temp] = UCA1RXBUF; // Rx -> PC_2_IOT character array
if (usb_rx_wr >= (LARGE_RING_SIZE)){
usb_rx_wr = BEGINNING; // Circular buffer back to beginning
}
UCA0IE |= UCTXIE; // Enable Tx interrupt
}break;
case TXIE:{ // Vector 4 - TXIFG
UCA1TXBUF = IOT_2_PC[direct_usb++];
if (direct_usb >= (sizeof(IOT_2_PC))){
direct_usb = BEGINNING; // Circular buffer back to beginning
}
if (direct_usb == iot_rx_wr){
UCA1IE &= ~UCTXIE; // Disable TX interrupt
}
}break;
default: break;
}
//------------------------------------------------------------------------------
}
