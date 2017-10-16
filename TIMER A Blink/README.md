# Timer Blink Delay
Implemented on the following processors:
1. MSP430G2553
2. MSP430F5529
3. MSP430FR2311
4. MSP430FR5994
5. MSP430FR6989


## Overall structure of code
The following list gives an idea of the overall structure of the code used to implement Button Blink using interrupts.

1. Stop WatchDog Timer
2. Initialise Registers (1 button, 1 LED, enable interrupts for Timer)
3. Set CCR register for Timer A
3. Blink LED at some initial default rate
4. When button is pressed, increase the rate of blink
5. Once rate of blink has reached maximum, reset back to a slow speed.

### How this code works (more detailed)
This code is implemented using two interrupts (explained below), a button interrupt and a timer interrupt.
The timer interrupt will control the rate at which the LED blinks. I am going to define a "blink" as an LED turning on, then off.
So, to blink at a rate of 10 Hz (10 times per second), the LED must turn on 10 times, and off 10 times, per second. Since the 
interrupt flips the status of the LED, we want to trigger the interrupt 20 times per second, to achieve my definition of 
10 Hz blinking. In order to achieve this feat, we must specifically set our CCR0 register so that based on the clock speed, 
it will overflow 10 times each second. the calculations can be seen below:

####Calculations
For the MSP430G2553 processor, we use SMClk, which runs at 1MHz. In addition, we use two 1/8 dividers, resulting in a 
frequency of 15625 Hz. The timer will increment 15625 times per second. To overflow CCR0 20 times each second,
we will set CCR0 to 781. This will allow us to trigger the interrupt 20 times per second, resulting in 10 "blinks" per second.


### Required Materials
In order to implement each of these pieces of software, you will require 3 things:

1. Physical MicroController with appropriate USB connector cable, or some equivalent emulator software
2. Code Composer Studio(CCS), or program to flash code to the MCU.
3. Main.c file for corresponding processor
4. Header file for corresponding processor (CCS has them built in, or they can be found online) 
5. 8 LED's, 8 1k resistors, breadboard jumper wires

### Implementing this code on your Processor
Each of the main.c files found in the folders can be implemented directly on the processors denoted by the folder name.
The main differences lie in the specific processor dependent implementations. Each processor has its own pre-defined
registers, which would need to be changed based on the specific processor used. For example, Pin 1.0 is the red LED on the MSP430G2553,
while the same pin on the MSP430F5529 is not even accessible.

### Key differences
We have 5 different implementations of the same code, for 5 different processors. The code for all 5 is nearly identical,
and for some processors, is even 100% identical. However, one important aspect to understand is that the 2311, 5994, and 
6989 processors all require an additional piece of code in order to function, else nothing will happen. For these boards,
we need to disable the pin high-impedance mode, which is enabled by default in these boards. This high-impedance mode
essentially forces all registers regarding pins to be set to their default values, and blocks the ability to change the pins.
As a result, we need to run the line, PM5CTL0 &= ~LOCKLPM5 in order to actually implement our code.

#### Interrupts
A key idea introduced here is interrupts. An interrupt is essentially a (sometimes) random suspension of the code currently
being executed, in order to execute some other code. Generally, the new code that is to be run is known as an 
Interrupt Service Routine(ISR) or Interrupt Handler. The basic chain of events that occurs when an interrupt occurs can
be seen in the following image:

The main program will be executed, and when an interrupt is detected (an interrupt flag is changed),
 we will execute some other code. Once that othercode is finished being executed, we will go right back to the 
 main program (as the state of the program is saved when we begin to handle the interrupt).

##### Timer Based Interrupt
In order to blink the LED in this case, we use the timer modules. In order to do so, we initialise the varius Control
registers for the timers. We set the frequency of the clock, counting mode, predividers, interruptability, and the value
to which we will be counting(essentially determining the blink rate of the LED).

#### Known bugs
There are no known bugs. This is a fairly easily implemented piece of software.




