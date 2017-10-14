#include <msp430F5529.h>
unsigned int delay=0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer


       P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
       P1DIR |= BIT0;                          // Set P1.0 to output direction

       P1DIR &= ~BIT1;
       P1OUT |= BIT1;
       P1REN |= BIT1;

       P1IE |= BIT1;
       P1IFG &=~BIT1;

       P4OUT &= ~BIT7;
       P4DIR |= BIT7;

       __bis_SR_register(LPM0_bits + GIE);
       for(;;){
           int i;
           for(i=0;i<delay;i++){
           }
           P1OUT^=BIT0;
       }
   }
#pragma vector = PORT1_VECTOR
__interrupt void buttonPress(void){
    delay+=5000;
    if(delay>=50000){
        delay=0;
    }
    P1IFG&=~BIT1;
    __bic_SR_register_on_exit(LPM0_bits);
}




