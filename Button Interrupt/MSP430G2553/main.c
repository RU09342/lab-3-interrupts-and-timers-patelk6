#include <msp430G2553.h>
 int delay =0;
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= (BIT0);           // Set P1.0 to output direction

  P1DIR &= ~BIT3;               // button is an input
  P1OUT |= BIT3;                // pull-up resistor
  P1REN |= BIT3;                // resistor enabled

  P1IE |= BIT3;         // P1.3 interrupt enabled
  P1IFG &= ~BIT3;       // P1.3 IFG cleared
  __enable_interrupt();
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
    __delay_cycles(10000);
    delay+=10000;
    if(delay>=30000){
        delay=0;
    }
// Add INTERRUPT SERVICE ROUTINE HERE.
  //  P1OUT ^= BIT0;


    P1IFG &= ~BIT3; // P1.3 IFG cleared
    //__enable_interrupt();
}



