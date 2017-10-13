#include <msp430FR6989.h>
 int delay =0;
int main(void)
{
  PM5CTL0 &= ~LOCKLPM5;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= (BIT0);           // Set P1.0 to output direction
  P9DIR |= (BIT7);

  TA0CTL=TASSEL_1+MC_1;
  TA0CCTL0 = CCIE;
  TA0CCR0 = 12000;


  __bis_SR_register(LPM0_bits + GIE); //Enable interrupts while we are in our forever loop
  int i;

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT^=BIT0;
    P9OUT ^= BIT7;
   // __delay_cycles(10000);
}



