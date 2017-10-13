#include <msp430FR6989.h>
 int delay =0;
int main(void)
{
  PM5CTL0 &= ~LOCKLPM5;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= (BIT0);           // Set P1.0 to output direction

  P1DIR &= ~BIT1;               // button is an input
  P1OUT |= BIT1;                // pull-up resistor
  P1REN |= BIT1;                // resistor enabled

  P1IE |= BIT1;         // P1.3 interrupt enabled
  P1IFG &= ~BIT1;       // P1.3 IFG cleared
  __bis_SR_register(LPM0_bits + GIE); //Enable interrupts while we are in our forever loop
  int i;
  for(;;){
    for(i=0;i<delay;i++);
    P1OUT ^= BIT0;
  }

}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    //__disable_interrupt();
   // __delay_cycles(10000);  //Attempt to debounce the button slightly
    delay+=10000;

    if(delay>=50000){
        delay=0;
    }

    __bic_SR_register_on_exit(LPM0_bits);

    P1IFG &= ~BIT1; // P1.3 IFG cleared

}



