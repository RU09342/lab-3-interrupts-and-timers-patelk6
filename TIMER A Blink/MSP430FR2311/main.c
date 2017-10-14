#include <msp430FR2311.h>
unsigned int delay = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

       P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
       P1DIR |= BIT0;                          // Set P1.0 to output direction



       ;                   // Disable the GPIO power-on default high-impedance mode
                                               // to activate previously configured port settings
       TB0CTL |= TBSSEL_2 + ID_3 + MC_1;
       TB0CCTL0 |=CCIE;
       TB0CCR0 = 62500;


       __enable_interrupt();
       for(;;){
       }

 }
#pragma vector = TIMER0_B0_VECTOR
__interrupt void buttonPress(void){
    P1OUT^=BIT0;
}




