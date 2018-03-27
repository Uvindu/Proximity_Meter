#define _XTAL_FREQ 8000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h";
#include "SharpIR.h"



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
int r;

void interrupt ISR_HANDLER()
{
    if(INTCONbits.RBIF == 1)
    {
        INTCONbits.GIE=0;
        if(PORTBbits.RB4==1)T1CONbits.TMR1ON=1;
        if(PORTBbits.RB4==0)
        {
            T1CONbits.TMR1ON=0;
            a=(TMR1L|(TMR1H<<8))/58.82;
        }
            INTCONbits.RBIF=0;
            INTCONbits.GIE=1;
    }
    

}

int main()
{
  TRISB=0b00010000;

  TRISD = 0x00;
 
  
  INTCONbits.GIE=1;
  INTCONbits.RBIF=0;
  INTCONbits.RBIE=1;
  IOCBbits.IOCB4=1;

  
  
  Sharp_Init();
  Lcd_Init();
  
  Lcd_Set_Cursor(1,1);
  Lcd_Write_String("Developed By");
  Lcd_Set_Cursor(2,1);
  Lcd_Write_String("Hiran Perera");
  __delay_ms(3000);
  Lcd_Clear();
  
  T1CON=0x10;
    
  while(1)
  {
      TMR1H=0x00;
      TMR1L=0x00;
      
      PORTBbits.RB0=0;
      __delay_us(2);
      PORTBbits.RB0=1;
      __delay_us(10);
      PORTBbits.RB0=0;
      
      __delay_ms(100);
     
      r=Process(2);

      
      
      //if(a>=2 && a<=400)
      //{
          Lcd_Clear();
          Lcd_Set_Cursor(1,1);
          Lcd_Write_String("Distance = ");
          
//          itoa(a,10,buf1);
//          Lcd_Set_Cursor(1,12);
//          Lcd_Write_String(buf1);
          
          Lcd_Set_Cursor(1,14);
          Lcd_Write_Char(a%10+48);
          
          a=a/10;
          Lcd_Set_Cursor(1,13);
          Lcd_Write_Char(a%10+48);
          
          a=a/10;
          Lcd_Set_Cursor(1,12);
          Lcd_Write_Char(a%10+48);
          
          Lcd_Set_Cursor(1,15);
          Lcd_Write_String("cm");
 
          Lcd_Set_Cursor(2,1);
          Lcd_Write_String("Distance = ");
          
          Lcd_Set_Cursor(2,15);
          Lcd_Write_Char(r%10+48);
          
          r=r/10;
          Lcd_Set_Cursor(2,14);
          Lcd_Write_Char(r%10+48);
          
          r=r/10;
          Lcd_Set_Cursor(2,13);
          Lcd_Write_Char(r%10+48);
          
          r=r/10;
          Lcd_Set_Cursor(2,12);
          Lcd_Write_Char(r%10+48);

      //}
      //else
      //{
        //  Lcd_Clear();
          //Lcd_Set_Cursor(1,1);
          //Lcd_Write_String("Out of Range");
      //}
      __delay_ms(100);
  }
  return 0;
}