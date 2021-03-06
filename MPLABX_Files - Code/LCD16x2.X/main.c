#define _XTAL_FREQ 20000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h";

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

int main()
{
  unsigned int a;
  TRISD = 0x00;
  Lcd_Init();
  while(1)
  {
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("ABCDEFGHIJKLMNOP");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("abcdefghijklmnop");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("123456789");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("!@#$%^&*()_+");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Hiran Perera");

    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Right();
    }

    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Left();
    }

    Lcd_Clear();
    Lcd_Set_Cursor(2,1);
    Lcd_Write_Char('H');
    Lcd_Write_Char('P');
    __delay_ms(2000);
  }
  return 0;
}