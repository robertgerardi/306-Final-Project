North Carolina State University - ECE 306 - Embedded Systems 

This project consisted of 10 sub-projects that ultimately led to the final car implementation.

High Level Overview 

o	Constructed a dual-motor autonomous car with line detection and remote-control capabilities using EPS32 IOT WIFI module and infrared sensors.
o	Soldered a backlit display that was used as a GUI for the user. Information such as power, wheel speed, IP address, location, and movement were calibrated and displayed.
o	Engineered the vehicles software using C and the MSP-430’s IAR IDE. Interrupt service routines, pulse width modulation, data transfer mechanisms, and power control technics were used to perform maximum efficiency.
o	Controlled the vehicles movement and initiated its autonomous line following in an obstacle course that was aimed to tests the cars capabilities

File Descriptions

Main.c - Once all the hardware is set up and working, the next step is to make sure the software is configured and running correctly. When the program starts, it is initially in main. The code in main is where important functions used for initialization are called, including functions used for initializing ports, clocks, timers, conditions, the LCD display, and the ADC. One of the timers, Timer B3, is responsible for controlling the wheels. Once all the essential functions are called, the program goes into a while loop used for code execution. The main code is running functions that include processing commands, black line navigation, and displaying the time to the screen.

Ports.c - In the port initialization function, the program initializes and configures ports 1-6 which is important for vehicle functionality. It makes sure that all of the correct pins are set including the select bits. pull up resistors, and output and input configuration. This code is located in ports.c.

Timers.c - The code within the timers.c file is responsible for the implementation of Timers B0 and B3. Timer B0 runs at 100 msec intervals and enables interrupts used for enabling ADC conversions and incrementing counters used for black line detection. The interrupt also clears flags for Timer B0 0 interrupt and 1-2 overflow interrupt. Timer B3 is used for implementation of PWM. 

ADC_Interrupts.c - The ADC code is responsible for converting values read from the IR detectors and emitter into an integer value that can be used to detect the black line. There are four functions tied to making the ADC work: Init_ADC, the ADC interrupt, the hex to BCD function, and the adc_line function. All of these functions are located in the adc.c file. The ADC interrupt converts hex to BCD values for the left and right detectors as well as the thumb wheel. The interrupt also displays the value onto the LCD display using the adc_line function.

Blackline.c - The line-following code is responsible for gathering values from our IR sensors and using them to decide whether or not we are on the line.  We are also able to use these values to decipher what side of the line we are on, if we are not on the center.  We are constantly receiving values, telling us where we are on the line.  When we first run our line-following code we tell the car to use our all_forward function until it runs into a line.  Once the car has detected the line, it turns until the line is found again. Once the line is found again, it will activate the motors, continuously reading the black line values and transferring that data to the FRAM Board. The FRAM board takes those readings and determines if it needs to turn left, right, or continue going forward to stay on the line. While the car is following the black line,it will display its position on the screen. Time spent is also being displayed on the screen. 

Serial.c - The code present in this file is regarding the ESP32 wifi module and the intake of commands from connected devices. In this case, commands were sent to the IOT module using a phone. Once the command_processing function was called in main, the command sent to the IOT would be moved to a process buffer. The process buffer was then sifted through to find the command sent, and the proper action was performed. Some of the commands included putting the IP address onto the display, turning in different directions, and performing black line navigation. Once the command was processed the process buffer was clear, a wait state occurred, and then the process buffer was open to receiving commands again.
