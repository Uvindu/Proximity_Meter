#define _XTAL_FREQ 8000000                // set crystal oscillator to 8MHz.
#define TMR1PRESCALE 8                     // timer1 prescaler is 8.
#define OUT RC2                            // use the name OUT for RC2 pin.

#include <xc.h>


// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// variables and constants declarations 
unsigned long CCPR = 0;                    // holds the value needed to be put in CCP's registers.
unsigned long current_period = 0;          // holds the period that timer1 will use.
const unsigned long total_period = 32500;  // 20ms for 50hz frequency.


// interrupt service routine
void interrupt tmr1isr () {
   if (CCP1IF == 1) {                           // if CCP compare interrupt flag is set
      
      
       if ((current_period > 0) && (current_period < total_period)){ // if duty is > 0% AND < 100% then:
       
           if (OUT == 1) {                           // if the output was 1 -> was "on-time".         
           OUT = 0;                                  // set output to 0 in order to achieve "off-time".
           CCPR = total_period - current_period;     // make it time for "off-time", off-time = full time - on time.
           }
                 
      else {                                    // if the output was 0 -> was "off-time".
         OUT = 1;                               // set output to 1 in order to achieve "on-time"
         CCPR = current_period;                 // make it time for "on-time".
      }
       }
       else {
           if (current_period == total_period) { OUT = 1;}             // if duty = 100%, then output 1 all the time.
           if (current_period == 0)            {OUT = 0;}              // if duty = 0%, then output 0 all the time.
       }
       
   
      // now set the value of CCPR into CCP module's registers:
      
      CCPR1H = CCPR >> 8;                       // right-shift CCPR by 8 then load it into CCPR1H register (load higher byte).
      CCPR1L = CCPR;                            // put the lower byte of CCPR in CCPR1L register.
      CCP1IF = 0;                               // reset CCP1 interrupt flag.
   }
}


// main function:
void main() {
   

   TRISC = 0;                 // port c is output.
   PORTC = 0;                 // port c = 0.
   
   T1CON = 0b00110000;        // timer1 uses prescaler value of 8 and it is off.
   TMR1H = 0;                 // timer1 registers have 0 (clear).
   TMR1L = 0;

   CCP1CON = 0x0b;            // set CCP module to compare mode and trigger special event when interrupt happens.
   CCPR = 0;                  // load 0 in CCPR.
   CCP1IF = 0;                // clear CCP1 interrupt flag.
   CCP1IE = 1;                // enable CCP1 interrupt. 
   INTCON = 0xC0;             // enable global and peripheral interrupt. 
   T1CON = 0b00110001;        // start timer1 with the same settings like before.
   

   

   while (1) {                                          // infinite loop.
      
       
       // TEST CODE...
       
       current_period = total_period * 0.5;            // 50% duty cycle.
       __delay_ms(5000);                               // delay 2s.
       current_period = total_period * 0.7;            // 10% duty cycle.
       __delay_ms(5000);                               // delay 2s.
       current_period = total_period * 0.3;              // 100% duty cycle.
       __delay_ms(5000);                               // delay 2s.
                               
      }
   }

