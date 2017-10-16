# Reaction Game
## Implemenation
This game is implemented on the MSP430FR6989 development board. I make use of both buttons, and both LED's,
as well as implement false-start protection. To implement this on your own device, you simply take my main.c file, and
put it into your project, and then make sure that the appropraite processor is chosen.
### How it works
The game implements various timers and button interrupts in order to function effectively. When first launching the game,
the processor will be in a low power state. To start the game, we press both buttons. Once this is done,
the LED's will both shine for a moment, before turning off. At this point, the game can be considered started. After a
"random" amount of time, both LED's will turn back on. The first person to hit their button is the winner. The winner 
is indicated by having the LED on his/her side blink rapidly. If you are to hit the button before the LED's turn back on,
the LED of the opponent will blink rapidly, indicating that they are the winners.
#### "Random time"
Initially, I attempted to find some kind of random number generator library on the internet. However, I eventually
decided against this, as I was not sure how many unwanted functions I would have to load onto my processor,
just for the ability to get a random number. Instead, I decided to implement something sneaky. I have a separate timer
module running in the background, incrementing a "randomNumber" variable. This incrementation is disabled, once the game 
is ready. Once both players have pressed their button, I will then use the randomNumber variable to generate a random delay.
I do this by performing the modulo operation on it with the value 24576, ensuring that I have a bound of 24576.
I then add 12000 to the value from the modulo, and that will become my CCR register to count up to, after which the LED's
will turn on, and the players will have to hit their buttons.
### Why this board
I chose this board because it offered me everything I wanted, 2 buttons, plenty of playing space, and good real estate
for a real 1 on 1 feel. The buttons are next to each other, as are the LED's, so I felt this board was the best for the
type of game that I was implementing.