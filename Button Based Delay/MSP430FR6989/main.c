#include <msp430FR6989.h>
unsigned int delay=1;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;


       P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
       P1DIR |= BIT0;                          // Set P1.0 to output direction

       P1DIR &= ~BIT1;
       P1OUT |= BIT1;
       P1REN |= BIT1;

       TA0CCTL1 = CCIE;                          // CCR0 interrupt enabled

       TA0CCR0 = 2048;
       TA0CCR1 = 2048;

       TA0CTL = TASSEL_1 + MC_1 + ID_3 + TACLR;         // SMCLK, upmode, clear TAR



       __enable_interrupt();
       while(1){
           while((P1IN & BIT1) != BIT1){
               TA0CCTL1 |=CCIE;
               TA0CCTL0 &=~CCIE;


           }
           TA0CCR0 = 2048*delay;

           TA0CCTL0 |=CCIE;
           TA0CCTL1 &=~CCIE;

       }
   }
#pragma vector = TIMER0_A1_VECTOR
__interrupt void delayBuilder(void){
    delay++;
    P1IFG &=~BIT1;
    TA0CCTL1 &= ~CCIFG;

}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void ledBlinker(void){

    P1OUT^=BIT0;

}




