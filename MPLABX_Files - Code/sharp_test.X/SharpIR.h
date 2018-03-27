#include <math.h>

float tol=0.01;
int avg=25;
void Sharp_Init()
{
  ANSEL=0x00;
  ANSELH=0x00;
  TRISA=0xFF;
  

  TRISAbits.TRISA2=1;
  ANSELbits.ANS2=1;
  
  ADCON1bits.ADFM=1;
  ADCON1bits.VCFG0=0;
  ADCON0bits.ADCS=0b101;
  
  ADCON0bits.CHS=2;
  ADCON0bits.ADON=1;
}

int analogRead(int channel)
{   int raw;
    float volt;
   
    ADCON0bits.CHS=channel;
    ADCON0bits.GO=1;
    while(ADCON0bits.GO==1)
      {
         raw=(ADRESH<<8)|ADRESL; 
      }
    ADCON0bits.GO=0;
    volt=(raw*5.0)/1023.0;
    return (int)(61.573*pow(volt, -1.1068));
}

int Process(int channel)
{
  
    int p=0;
    int sum=0;
    int previousDistance;
    
    for (int i=0; i<avg; i++){
        
        int foo=analogRead(channel);
        
        if (foo>=(tol*previousDistance)){
        
            previousDistance=foo;
            sum=sum+foo;
            p++;
            
        }
        
        
    }

    
    int accurateDistance=sum/p;
    
    return accurateDistance;  
}