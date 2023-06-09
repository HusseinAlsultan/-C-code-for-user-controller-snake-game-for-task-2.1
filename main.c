#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       //stop watchdog timer

    //1-- Setup Ports
    P2DIR &= ~BIT0;   //set up Pins P2.0 as an input Pins
    P3DIR &= ~BIT0;   //set up Pins P3.0 as an input Pins
    P4DIR &= ~BIT0;   //set up Pins P4.0 as an input Pins
    P5DIR &= ~BIT0;   //set up Pins P5.0 as an input Pins

    P2REN = BIT0;     //enable built-in resistor of P2.0
    P3REN = BIT0;     //enable built-in resistor of P3.0
    P4REN = BIT0;     //enable built-in resistor of P4.0
    P5REN = BIT0;     //enable built-in resistor of P5.0

    P2OUT = BIT0;     //set resistor to pull up of P2.0
    P3OUT = BIT0;     //set resistor to pull up of P3.0
    P4OUT = BIT0;     //set resistor to pull up of P4.0
    P5OUT = BIT0;     //set resistor to pull up of P5.0


    //2-- Setup UART
    UCA1CTLW0 |= UCSWRST;           //put UART A! in to SW reset

    UCA1CTLW0 |= UCSSEL__ACLK;     //choose ACLK for UART A1
    UCA1BRW = 3;                    //set prescalar to 8
    UCA1MCTLW = 0x9200;            //setup modulation

    //3-- Setup Pins
    P4SEL1 &= ~BIT3;                //setup P4.3 to use UART A1 TX
    P4SEL0 |= BIT3;                 //P4SEL1.3:P3SEL0.3 = 01

    PM5CTL0 &= ~LOCKLPM5;           //turn on GPIO system

    UCA1CTLW0 &= ~UCSWRST;          //take UART A! out of SW reset

    //--- main loop
    int i;
    char r = 'R';
    while(1)
        {
            //Right Direction Button, P2.0
            if ((P2IN & BIT0) != BIT0) //P2IN depends on the input logic state (keep changing depends on whether you are
               {                       //pressing the button). By default, P2IN will be 1 because it is internally connected
                UCA1TXBUF = r;//0x52;      //to the pull-up resistor., if you press the button, then P2IN = 0.
                for( i=0; i<10000; i++){}
               }

            //Left Direction Button, P3.0
            if ((P3IN & BIT0) != BIT0)
               {
                UCA1TXBUF = 0x4C;
                for( i=0; i<10000; i++){}
               }

            //Up Direction Button, P4.0
            if ((P4IN & BIT0) != BIT0)
               {
                UCA1TXBUF = 0x55;
                for( i=0; i<10000; i++){}
               }

            //Down Direction Button, P5.0
            if ((P5IN & BIT0) != BIT0)
               {
                UCA1TXBUF = 0x44;
                for( i=0; i<10000; i++){}
               }
        }
    return 0;
}
