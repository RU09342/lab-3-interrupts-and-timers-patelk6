# Advanced Work Lab 3
## In this lab, the advanced work tackled was the 8-bit binary counter, as well as the reaction game (has its own readme)
To implement the 8-bit binary counter, I initialised the 8 GPIO pins that I would require, and hooked them all up
to their various LED's. The actual logic was fairly simple. I was able to abuse the fact that the P1OUT register on the 
MSP430FR6989 development board was 8 bits, each of which corresponded to the status of a GPIO pin. By simply adding 
"1" to the P1OUT register, I am able to get binary counting very easily. The only caveat is that I need to keep track
of the current count, and reset the values of the pins once I hit 255, because I found I would run into strange issues
when the register overflowed.
### Implementation
Implemenation of this binary counter is simple. Simple take the main.c file, make sure your project is linked to the
MSP430FR6989 board, and set up the circuit for the LED's. Then just hit the button to count up.