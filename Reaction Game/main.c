#include <msp430FR6989.h>
 int gameReady =0;
 unsigned volatile int count =0;
 unsigned volatile int randomNumber = 0;
 int needDelay=1;
 int gameStart=0;


 int generateDelay(void);
int main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;
  //Set LED Registers
  P1DIR |= (BIT0);
  P9DIR |= BIT7;
  //Initialise LED status's to off
  P1OUT &=~BIT0;
  P9OUT &=~BIT7;

  P1DIR &= ~BIT1;               // button is an input
  P1OUT |= BIT1;                // initialise button to high
  P1REN |= BIT1;                // resistor enabled

  P1DIR &= ~BIT2;               // button is an input
  P1OUT |= BIT2;                // initialise button to high
  P1REN |= BIT2;                // resistor enabled


  //Initialise Button Interrupts
  P1IE |= P1IV_P1IFG1;
  P1IE |= P1IV_P1IFG2;
  //Clear Button Interrupt Flags Initially
  P1IFG &= (~BIT1);
  P1IFG &= ~BIT2;
  //Set up AClk, in up mode, with a clock divider of 8, to the 32 KHz clock
  TA0CTL = TASSEL_1 + MC_1 + ID_3 + SELA__LFXTCLK ;
  //Enable CCR1 interrupts
  TA0CCTL1 = CCIE;

  TA0CCR0 = 2048;
  TA0CCR1 = 2048;



  //enter low power mode with interrupts
  __bis_SR_register(LPM0_bits + GIE);
  //Forever loop
  for(;;){
      //If the game is ready to be played, and we need a time at which to start the game
      if(gameReady&& needDelay){
          //Set CCR0 to the output of generateDelay plus 12000
          TA0CCR0 = (generateDelay() + 12000);

      }
  }


}
//Function to generate a "random" delay, and also to enable CCR0
int generateDelay(void){
    TA0CCTL1 &=~CCIE;
    TA0CCTL0=CCIE;
    needDelay=0;
    return (randomNumber % 24576);
}
//Button interrupt handling
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(!gameReady){
        if(( ((P1IN && BIT2) != BIT2)) && (  ((P1IN && BIT1) != BIT1))){
            gameReady=1;
            P1OUT|= BIT0;
            P9OUT|=BIT7;
        }
    }else if(!gameStart && gameReady){
        //False-Start Protection
        if(P1IFG & BIT1){

            displayWinner(2);

        }else if(P1IFG & BIT2){

            displayWinner(1);
        }



    }else{
        //Win conditions
        if(P1IFG & BIT1){

            displayWinner(1);

        }else if(P1IFG & BIT2){
            displayWinner(2);
        }

    }
    //Make sure everyone is on an even playing field to begin
     P1IFG &= (~BIT1);       // P1.3 IFG cleared
     P1IFG &= ~BIT2;
     P1OUT&= ~BIT0;
     P9OUT&=~BIT7;
     __bic_SR_register_on_exit(LPM0_bits);

}
//Flash an LED to show the winner
void displayWinner(int winner){
   switch(winner){
       case 1:
           for(;;){
               __delay_cycles(50000);
               P1OUT ^= BIT0;
           }
       case 2:
           for(;;){
               __delay_cycles(50000);
               P9OUT ^= BIT7;
           }
    }
}
//CCR1 interrupt handling
#pragma vector = TIMER0_A1_VECTOR
__interrupt void randomCounter(void)
{
            randomNumber++;
            TA0CCTL1 &= ~CCIFG;

}
//CCR0 interrupt handling
#pragma vector = TIMER0_A0_VECTOR
__interrupt void mainGameClock(void)
{
    gameStart=1;
    TA0CCTL0 &=~CCIE;
    P1OUT|= BIT0;
    P9OUT|= BIT7;

}



