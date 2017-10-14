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

       TA0CTL |= TASSEL_2 + MC_1 + ID_3;
       TA0CCTL0 |= CCIE;
       TA0CCR0 = 62500;


       __bis_SR_register(LPM0_bits | GIE);
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerOverflow(void){

   P1OUT^=BIT0;

}




