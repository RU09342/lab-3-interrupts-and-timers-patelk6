#include <msp430FR2311.h>
unsigned int delay = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

       P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
       P1DIR |= BIT0;                          // Set P1.0 to output direction



       PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                               // to activate previously configured port settings
       //Set Pin 1.1 as an input
       P1DIR &= ~BIT1;
       //Initialise the button to high
       P1OUT |= BIT1;
       //Enable pull up resistor for button
       P1REN |= BIT1;

       P1IE |= BIT1;
       P1IFG &=~ BIT1;
       __bis_SR_register(LPM0_bits + GIE);
       for(;;){
           int i;
           for(i=0;i<delay;i++){}
           P1OUT^=BIT0;
       }

 }
#pragma vector = PORT1_VECTOR
__interrupt void buttonPress(void){
    delay+=5000;
    if(delay>=55000){
        delay=0;
    }
    P1IFG&=~BIT1;
    __bic_SR_register_on_exit(LPM0_bits);
}




