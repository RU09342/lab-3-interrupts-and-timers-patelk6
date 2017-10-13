# Button-Based Delay
Implemented on the following processors:
1. MSP430G2553
2. MSP430F5529
3. MSP430FR2311
4. MSP430FR5994
5. MSP430FR6989


## Overall structure of code
The following list gives an idea of the overall structure of the code used to implement Button Blink using interrupts.

1. Stop WatchDog Timer
2. Initialise Registers (1 button, 1 LED, enable interrupts for button)
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

##### This Button based interrupt
Each interrupt has its own interrupt flag associated with it. When an interrupt is detected, the respective interrupt flag
will change. For the button based interrupt, we must re-clear the flag once we are finished handling the interrupt,
else the interrupt will not be able to be triggered again. Overall, writing an interrupt handler is fairly straightforward.
We write out function in the following manner:

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)

The pragma vector tells the processor that the following function should be treated as an interrupt routine. Each type of 
interrupt vector has a pre-defined name, (such as PORT1_VECTOR) which we can locate in the datasheet.

When the button is pressed, a delay variable is incremented. This delay will change the rate at which the LED will blink.
Once a certain delay value is reached, the delay will reset back to 0. 

#### Button
At this point, we are begginning to use the buttons that are available on the MSP's. All of the boards have varying
numbers of buttons, each of which are accessed in essentially the same way. In order to access the buttons,
we need to take these 3 actions (order is irrelevant)
* Initialise the button to high
* Set the Button to output
* Enable the pull up resistor for the button

There are two key differences in accessing buttons that we must look at:
1. Initialising the Button to high
2. Enabling the pull up resistor on the button

In order to understand why we need to do both of these things, we can look at the image below:

![alt text](https://imgur.com/a/gudhj "Circuit Diagram detailing why we need a pull-up resistor")

The button is naturally high, as can be seen in the preceeding image. When the switch is open, the voltage on the pin
is Vcc. But when the button is pressed (switch is closed) the voltage on the pin essentially becomes 0, as all of the current will
flow down to ground. Since the button is high when it is not pressed, we must initialise it to a high value.

The pull-up resistor is placed so that high amounts of current do not flow from Vcc to the MCU. If this were to happen, 
our MCU would not have a very good day.

An 8-bit binary counter is implemented using 8 of the GPIO pins. Upon button press, 
### Advanced Work - Binary Counter
An 8-bit binary counter is implemented using the MSP430G2553. The code is included in the MSP430G2553 folder, as main_Adv.c.
This counter works by using breadboard jumper cables to connect the signal output by the GPIO pins to the LED's.
A picture of this set up is included below:


The counter works fairly well, being able to count up to 255, and resetting once we go past 255.

#### Known bugs
The only known bugs in both the binary counter and the regular button based interrupt, is that lack of debouncing. Sometimes,
when pressing the button, the counter will increment twice, or the LED will flicker (having been turned on, and off in the time
that it took for the button signal to stabilise. An example of  of this can be seen below:




