#include <msp430FR6989.h>
 int count =0;

 int main(void)
{
  PM5CTL0 &= ~LOCKLPM5;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P2DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);           // Set P1.0 to output direction

  P1DIR &= ~BIT1;               // button is an input
  P1OUT |= BIT1;                // pull-up resistor
  P1REN |= BIT1;                // resistor enabled

  P1IE |= BIT1;         // P1.3 interrupt enabled
  P1IFG &= ~BIT1;       // P1.3 IFG cleared
  __bis_SR_register(LPM0_bits + GIE); //Enable interrupts while we are in our forever loop
  int i;
  for(;;){
  
  }

}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{	
	if(count>254){
		P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
		count = 0;
	}else{
		P1OUT += 1;
		count++;

	}
	
    

    __bic_SR_register_on_exit(LPM0_bits);

    P1IFG &= ~BIT1; // P1.3 IFG cleared

}



