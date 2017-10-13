#include <msp430G2553.h>
 unsigned int delay =10000;
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= (BIT0);           // Set P1.0 to output direction

  P1DIR &= ~BIT3;               // button is an input
  P1OUT |= BIT3;                // pull-up resistor
  P1REN |= BIT3;                // resistor enabled

  //P1IE |= BIT3;         // P1.3 interrupt enabled
  //P1IFG &= ~BIT3;       // P1.3 IFG cleared
  __enable_interrupt();
  TA0CTL=TASSEL_2+MC_1+ID_3+DIVS_3;		//Using SMCLK, with 2 1/8 dividers, 15625 Hz clock
  TA0CCTL0 = BIT9;
  CCTL0 = CCIE;
  CCR0=1563;							//LED will initially blink at 10 Hz

  int i;
  for(;;){
      while((P1IN & BIT3) != BIT3){
          delay++;
      }
      CCR0=delay;

     // P1OUT |= BIT0;
  }


}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    
    __delay_cycles(50000);
    delay+=10000;
    if(delay>=30000){
        delay=0;
    }


    P1IFG &= ~BIT3; // P1.3 IFG cleared
    
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT^=BIT0;
   // __delay_cycles(10000);
}



