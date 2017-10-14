#include <msp430FR5994.h>
unsigned int delay = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

       P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
       P1DIR |= BIT0;                          // Set P1.0 to output direction

       //Enable Pin 5.6 as an input
       P5DIR &= ~BIT6;
       //Initialise the button to high
       P5OUT |= BIT6;
       //Enable Pull up resistor for Pin 5.6
       P5REN |= BIT6;

       P5IE |=BIT6;
       P5IFG &=~BIT6;

       __bis_SR_register(LPM0_bits + GIE);
       int i;
       for(;;){
           for(i = 0;i<(delay);i++){;}
           for(i=0;i<(delay);i++){;}
           for(i=0;i<(delay);i++){;}
           for(i=0;i<(delay);i++){;}
           for(i = 0;i<(delay);i++){;}

           P1OUT^=BIT0;
       }
}
#pragma vector = PORT5_VECTOR
__interrupt void buttonPress(void){
    delay+=10000;
    if(delay>=50000){
        delay=0;
    }
    P5IFG &=~BIT6;
    __bic_SR_register_on_exit(LPM0_bits);
}




