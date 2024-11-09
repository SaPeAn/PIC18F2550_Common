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
  srand(timestamp + TMR1H);
}

uint8 getrand(uint8 N)
{
  return (rand() % (N + 1));
}

uint8 dig_to_smb(uint8 dig)
{
  switch (dig)
  {
    case 0: return 48; break;
    case 1: return 49; break;
    case 2: return 50; break;
    case 3: return 51; break;
    case 4: return 52; break;
    case 5: return 53; break;
    case 6: return 54; break;
    case 7: return 55; break;
    case 8: return 56; break;
    case 9: return 57; break;
  }
}

uint8* u8_to_str(uint8 num)
{
  uint8 L = num%10;
  L = dig_to_smb(L);
  uint8 M = (num%100)/10;
  uint8 H = num/100;
  if(H == 0) {
    if(M == 0) {
      uint8 str1[] = {L, '\0'};
      return str1;
    }
    else {
      M = dig_to_smb(M);
      uint8 str2[] = {M, L, '\0'};
      return str2;
    }
  }
  else {
    M = dig_to_smb(M);
    H = dig_to_smb(H);
    uint8 str3[] = {H, M, L, '\0'};
    return str3;
  }            
}           
