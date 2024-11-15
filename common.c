#include <xc.h>
#include "common.h"
#include <stdlib.h>


void Delay_ms(uint32 ms)
{
  uint32 temp = timestamp;
  while((timestamp - temp) < ms);
}

void randinit(void)
{
  srand((uint8)timestamp);
}

uint8 getrand(uint8 N)
{
  return (rand() % (N + 1));
}

uint8 dig_to_smb(uint8 dig)
{
  switch (dig)
  {
    case 0: return 48;
    case 1: return 49; 
    case 2: return 50;
    case 3: return 51; 
    case 4: return 52;
    case 5: return 53; 
    case 6: return 54; 
    case 7: return 55; 
    case 8: return 56;
    case 9: return 57;
  }
  return 0;
}

void u8_to_str(uint8* str, uint8 num)
{ 
  str[0] = num%10;
  str[1] = (num%100)/10;
  str[2] = num/100;
  if(num > 99)
  {
    for(uint8 i = 0; i < 3; i++) {
    str[i] = dig_to_smb(str[i]);
    }
    str[3] = '\0';
  }
  if((num > 9) && (num < 100))
  {
    for(uint8 i = 0; i < 2; i++) {
    str[i] = dig_to_smb(str[i]);
    }
    str[2] = '\0';
  }
  if(num < 10)
  {
    str[0] = dig_to_smb(str[0]);
    str[1] = '\0';
  }
}
