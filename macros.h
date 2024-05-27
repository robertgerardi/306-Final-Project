//******************************************************************************
//
//  Description: This file contains the macros used for the project
//
//  Robert Gerardi
//  December 2022
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
 //
#define TEST_PROBE           (0x01) // 3.0 TEST PROBE
#define RED_LED                (0x01) // 1.0 RED LED 0
#define GRN_LED                (0x40) // 6.6 GREEN LED


// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L 
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define RESET_LCD (0x01) // 0 RESET LCD
#define Check_Bat (0x02) // 1 Check ADC Voltages
#define IR_LED (0x04) // 2 IR_LED 
#define SW2 (0x08) // 3 SW2
#define IOT_RUN_CPU (0x10) // 4 IOT_RUN_CPU
#define DAC_ENB (0x20) // 5 DAC_ENB
#define LFXOUT (0x40) // 6 XOUTR
#define LFXIN (0x80) // 7 XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define OA2O (0x02) // 1 OA2O
#define OA2N (0x04) // 2 OA2N
#define OA2P (0x08) // 3 OA2P
#define SMCLK (0x10) // 4 SMCLK
#define DAC_CNTL (0x20) // 5 DAC signal from Processor
#define IOT_LINK_CPU (0x40) // 6 IOT_LINK_CPU
#define IOT_EN_CPU (0x80) // 7 IOT_EN_CPU

// Port 4 Pins
#define DAC_CNTL1 (0x01) // 0 DAC_CNTR1
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

//Port 5 pins
#define CHECK_BAT (0x01)
#define V_BAT (0x02)
#define V_DAC (0x04)
#define V_3_3 (0x08)
#define IOT_BOOT_CPU (0x10)


//port 6 pins
#define R_FORWARD (0x01)
#define R_REVERSE (0x02)
#define L_FORWARD (0x04)
#define L_REVERSE (0x08)
#define LCD_BACKLITE (0x10)
#define P6_5 (0x20)
#define GRN_LED (0x40)

// STATES ======================================================================
#define NONE ('N')
#define STRAIGHT ('L')
#define CIRCLE ('C')
#define TRIANGLE ('T')
#define FIGURE8 ('8')
#define IDLE ('I')
#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define RUN2 ('Q')
#define END ('E')
#define WHEEL_COUNT_TIME (10)
#define RIGHT_COUNT_TIME (7)
#define LEFT_COUNT_TIME (8)
#define TRAVEL_DISTANCE (10)
#define WAITING2START (500)
//CIRCLE
#define WHEEL_CIRCLE_COUNT_TIME (10)
#define RIGHT_CIRCLE_COUNT_TIME (1)
#define LEFT_CIRCLE_COUNT_TIME (5)
#define TRAVEL_CIRCLE_DISTANCE (67)
//FIGURE8
#define WHEEL_FIGURE8_COUNT_TIME (10)
#define RIGHT_FIGURE8_COUNT_TIME (1)
#define LEFT_FIGURE8_COUNT_TIME (5)
#define RIGHT_FIGURE8_COUNT_TIME2 (7)
#define LEFT_FIGURE8_COUNT_TIME2 (1)
#define TRAVEL_FIGURE8_DISTANCE (32)
#define TRAVEL_FIGURE8_DISTANCE2 (38)
//TRIANGLE

#define WHEEL_TRIANGLE_COUNT_TIME (10)
#define RIGHT_TRIANGLE_COUNT_TIME (4)
#define LEFT_TRIANGLE_COUNT_TIME (3)
#define RIGHT_TRIANGLE_COUNT_TIME2 (10)
#define LEFT_TRIANGLE_COUNT_TIME2 (1)
#define TRAVEL_TRIANGLE_DISTANCE (10)
#define TRAVEL_TRIANGLE_DISTANCE2 (10)

#define CLEAR (0)
#define PRESSED (0)
#define RELEASED (1)
#define NOT_OKAY (0)
#define OKAY (1)
#define DEBOUNCE_TIME (10)
#define DEBOUNCE_RESTART (0)
#define ZERO (0)
#define ONE (1)
#define TWO (2)
#define THREE (3)
#define FOUR (4)
#define FIVE (5)
#define SIX (6)
#define SEVEN (7)
#define EIGHT (8)
#define NINE (9)
#define TEN (10)

#define IPPOSITION (13)
#define FISRTHALFIP1 (14)
#define FISRTHALFIP2 (21)
#define SECONDHALFIP1 (21)
#define SECONDHALFIP2 (28)

#define FIRSTLINE (0)
#define SECONDLINE (1)
#define THIRDLINE (2)
#define FOURTHLINE (3)

#define FIRSTCHAR (0)
#define SECONDCHAR (1)
#define THIRDCHAR  (2)
#define FOURTHCHAR (3)

#define LINEFEED (0x0A)

#define TB0CCR0_INTERVAL (50000)
#define TB0CCR1_INTERVAL (50000)
#define TB0CCR2_INTERVAL (50000)
#define FIFTY_MS_COUNT
#define TEN_MS_COUNT (1)

#define BLACK_LINE (700)
#define BLACK_LINE2 (850)
#define WHITE_AREA (700)
#define WHITE_AREA2 (700)

#define RIGHT_FORWARD_SPEED (TB3CCR3)
#define RIGHT_REVERSE_SPEED (TB3CCR4)
#define LEFT_FORWARD_SPEED (TB3CCR1)
#define LEFT_REVERSE_SPEED (TB3CCR2)
#define WHEEL_OFF (0)
#define WHEEL_PERIOD (50000)
#define BEGINNING (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (64)
#define BEGINNING (0)
#define FALSE (0)
#define TRUE (1)

#define ONESEC (10)
#define TWOSEC (20)
#define THREESEC (30)
#define FOURSEC (40)
#define FIVESEC (50)
#define SIXSEC (60)
#define SEVENSEC (70)
#define EIGHTSEC (80)
#define NINESEC (90)
#define TENSEC (100)

#define COMMANDCHAR (1)
#define COMMANDCHAR2 (2)
#define COMMANDCHAR3 (3)
#define COMMANDCHAR4 (4)
#define COMMANDCHAR5 (9)

#define LENGTHOFMESSAGE1 (13)
#define LENGTHOFMESSAGE2 (21)
#define LENGTHOFMESSAGE3 (10)


#define HEXCUTOFF999 (999)
#define HEXCUTOFF99 (99)
#define HEXCUTOFF9 (9)

#define RESETTIME (0)
#define TURNTIME (4)

#define LEFTDETECT (0x00)
#define RIGHTDETECT (0x01)
#define TURNWHEEL (0x02)


#define BEGININTERCEPT (1)
#define STOPCAR (2)
#define BCDASCII (0x30)
#define SINGLESECCHAR (8)
#define TENSECCHAR (7)
#define HUNDREDSECCHAR (6)

#define BEGIN (1)

#define ONESPLACE (10)
#define TENSPLACE (100)
#define HUNDREDSPLACE (1000)

#define LASTLINE (4)
#define DISPLAYLENGTH (11)
#define LASTCHARFORDISPLAY (10)

#define NUMBEROFLINES (4)
#define NUMBEROFCHARS (11)

#define RXIE (2)
#define TXIE (4)

#define SLOWWHEELSPEED (8000)
#define FASTWHEELSPEED (10000)
#define FASTERWHEELSPEED (13000)
//states for black line navigation

#define TIMEWAITSTATE (0)
#define STARTMOVEMENT (1)
#define TURNTOBOARD (2)
#define BLACKLINEDETECTION (3)
#define BLACKLINEADJUST (4)
#define TURNONTOBLACKLINE (5)
#define BLACKLINETRAVEL (6)
#define EXITCIRCLE1 (7)
#define EXITCIRCLE2 (8)
#define STOPCARFINAL (9)