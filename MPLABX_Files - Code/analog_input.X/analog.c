#define _XTAL_FREQ 8000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h";
#include <pic16f887.h>


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


int a;
void interrupt ADC()
{   RB4=1;
    if (PIR1bits.ADIF==1)
    {
          PIE1bits.ADIE=0;
          INTCONbits.PEIE=0;
          INTCONbits.GIE=0;
          if (ADCON0bits.GO_nDONE==0)
          {
            
            a=(ADRESH<<8)|ADRESL;
          }
        PIR1bits.ADIF==0;
        PIE1bits.ADIE=1;
        INTCONbits.PEIE=1;
        INTCONbits.GIE=1;
         
    }
}



int main()
{
  
  ANSEL=0x00;
  ANSELH=0x00;
  TRISD = 0x00;
  PORTD=0;
  TRISA=0xFF;
  TRISB=0;
  PORTB=0;
  

  TRISAbits.TRISA2=1;
  ANSELbits.ANS2=1;
  
  ADCON1bits.ADFM=1;
  ADCON1bits.VCFG0=0;
  ADCON1bits.VCFG1=0;
  ADCON0bits.ADCS=0b101;
  
  ADCON0bits.CHS=2;
  ADCON0bits.ADON=1;
  
  PIR1bits.ADIF=1;
  PIE1bits.ADIE=1;
  INTCONbits.PEIE=1;
  INTCONbits.GIE=1;
  
  
  Lcd_Init();
  
  Lcd_Set_Cursor(1,1);
  Lcd_Write_String("Developed By");
  Lcd_Set_Cursor(2,1);
  Lcd_Write_String("GROUP 16");
  __delay_ms(3000);
  Lcd_Clear();
  
 
    
  while(1)
  {

      
      ADCON0bits.GO_nDONE=1;
      //__delay_ms(10);
      
      
      
//      a=a*5/1023;
//      a=2914/(a+5)-1;
          Lcd_Clear();
          Lcd_Set_Cursor(1,1);
          Lcd_Write_String("Distance = ");
          
          Lcd_Set_Cursor(2,15);
          Lcd_Write_Char(a%10+48);
          
          a=a/10;
          Lcd_Set_Cursor(2,14);
          Lcd_Write_Char(a%10+48);
          
          a=a/10;
          Lcd_Set_Cursor(2,13);
          Lcd_Write_Char(a%10+48);
          
          a=a/10;
          Lcd_Set_Cursor(2,12);
          Lcd_Write_Char(a%10+48);

     

      }
      __delay_ms(400);
      return 0;
  }
  
