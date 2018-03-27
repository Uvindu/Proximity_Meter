void Keypad_Init()
{
  TRISB=0b11110000;
  PORTB=0x00;
  ANSEL=0;
  ANSELH=0; 
}

char findKey(unsigned short a, unsigned short b)
{
 if(b == 0)
 {
   if(a == 3)
    return 'A';
   else if(a == 2)
    return '3';
   else if(a == 1)
    return '2';
   else if(a == 0)
    return '1';
 }
 else if(b == 1)
 {
   if(a == 3)
    return 'B';
   else if(a == 2)
    return '6';
   else if(a == 1)
    return '5';
   else if(a == 0)
    return '4';
 }
 else if(b == 2)
 {
   if(a == 3)
    return 'C';
   else if(a == 2)
    return '9';
   else if(a == 1)
    return '8';
   else if(a == 0)
    return '7';
 }
 else if(b == 3)
 {
   if(a == 3)
    return 'D';
   else if(a == 2)
    return '.';
   else if(a == 1)
    return '0';
   else if(a == 0)
    return '#';
 }
 return ' ';
}

char readKeyboard()
{
 unsigned int i = 0;
 for(i=0;i<4;i++)
 {
  if(i == 0)
  PORTB = 1;
  else if(i == 1)
  PORTB = 2;
  else if(i == 2)
  PORTB = 4;
  else if(i == 3)
  PORTB = 8;

  if(RB4)
    return findKey(0,i);
  if(RB5)
   return findKey(1,i);
  if(RB6)
   return findKey(2,i);
  if(RB7)
   return findKey(3,i);
 }
 return ' ';
}