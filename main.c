#include "config.h"
#include "common.h"

/*------------------------ÏÎÄÊËÞ×ÀÅÌÛÅ ÔÀÉËÛ----------------------------------*/
#include "init_periph.h"
//#include "drv_7seg.h"
#include "drv_buttons.h"
//#include "drv_led096_I2C.h"
//#include "drv_I2C.h"
#include "drv_lcdST7565_SPI.h"
//#include "drv_usart.h"
/*----------------------------------------------------------------------------*/
/*-----------------------ÃËÎÁÀËÜÍÛÅ ÏÅÐÅÌÅÍÍÛÅ--------------------------------*/

uint32 mainTimeCounter = 0;
uint32 dispCounter = 0;
uint32 countTime = 0;
uint16 countPeriod = 1000;
uint8  countDirect = 1;
uint8  countOn = 0;
uint8 Array[] = "Ïðèâåò, Ìèð!!!! Hello, World!!!!";

/*typedef struct {
uint8 USART_buf[100];
uint8 BufMax;
uint8 WritePos;
} UART_DATA;
UART_DATA UBuf = {0};*/

typedef struct{
  uint8 sec;
  uint8 min;
  uint8 hour;
} systime;
systime Time;
/*----------------------------------------------------------------------------*/   
uint16 GetPrd(void)
{
  static int i = 1;
  uint16 prd;
  if(i == 4) i = 0;
  switch (i) {
    case 0: prd = 1000; break;
    case 1: prd = 100; break;
    case 2: prd = 10; break;
    case 3: prd = 1; break;
  }
  i++;
  return prd;  
}
void Counting(uint16 cPrd, uint8 cOn, uint8 cDirect, uint32 counterMax){
  static uint32 cTime = 0;
  if(((timestamp - cTime) >= cPrd) && (cOn)) { 
    cTime = timestamp;
    if(cDirect)  mainTimeCounter++;
    if(!cDirect) mainTimeCounter--;
      }
    if(mainTimeCounter > counterMax && countDirect) mainTimeCounter = 0;
    if(mainTimeCounter > counterMax && !countDirect) mainTimeCounter = counterMax;
    }
/*-----------------------------ÎÁÐÀÁÎÒÊÀ ÏÐÅÐÛÂÀÍÈÉ---------------------------*/
void __interrupt() systemTime_int(void)
{
  if (TMR1IE && TMR1IF)
  {
    TMR1L += 32;
    TMR1H = 209;
    TMR1IF = 0;
    timestamp++;
    return;
  }
  
  /*if(RCIE && RCIF)
  {
    RCIF = 0;
    UBuf.USART_buf[UBuf.WritePos] = RCREG;
    UBuf.WritePos++;
    if(UBuf.BufMax < 100) UBuf.BufMax++;
    if(UBuf.WritePos > 99) UBuf.WritePos = 0;
    return;
  }*/
}
/*----------------------------------------------------------------------------*/
/*-----------------------------------MAIN-------------------------------------*/
void main(void) 
{
/*-------------------------------Èíèöèàëèçàöèÿ--------------------------------*/
  TMR0_init();
  TMR1_init();
  Interrupt_init();
  randinit();
  //I2C_init();
  //USART_init();
  btn_t B1 = CreateBtn(&TRISB, &PORTB, &LATB, 2, 5, &timestamp);
  btn_t B2 = CreateBtn(&TRISB, &PORTB, &LATB, 3, 5, &timestamp);
  btn_t B3 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 5, &timestamp);
  btn_t B4 = CreateBtn(&TRISB, &PORTB, &LATB, 2, 6, &timestamp);
  btn_t B5 = CreateBtn(&TRISB, &PORTB, &LATB, 3, 6, &timestamp);
  btn_t B6 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 6, &timestamp);
  btn_t B7 = CreateBtn(&TRISB, &PORTB, &LATB, 2, 7, &timestamp);
  btn_t B8 = CreateBtn(&TRISB, &PORTB, &LATB, 3, 7, &timestamp);
  btn_t B9 = CreateBtn(&TRISB, &PORTB, &LATB, 4, 7, &timestamp);
/*----------------------------------------------------------------------------*/
/*--------------------------------Ïåðåìåííûå----------------------------------*/
  uint8 prntClk = 1;
  uint8 T = 0;
  uint8 PG = 0;
  uint8 CL = 0;
  uint8 i = 0;

/*----------------------------------------------------------------------------*/
  Delay_ms(100);           // Çàäåðæêà ïîñëå âêëþ÷åíèÿ (äëÿ led096))
  LCD_Init();
  /*//Èíèöèàëèçàöèÿ led096
  Led096Set(8, 0xD5, 0xF0, 0x8D, 0x14, 0xAF, 0xA4, 0x20, 0x01);
  Led096Clear();*/
/*-----------------------------ÎÑÍÎÂÍÎÉ ÖÈÊË----------------------------------*/
  while(1)
  {
    TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4); TestBtn(&B5); 
    TestBtn(&B6); TestBtn(&B7); TestBtn(&B8); TestBtn(&B9);
    
    if(B1.BtnON || B1.HoldON || B1.StuckON){ 
      B1.BtnON = 0;
      uint8 Number = getrand(255);
      uint8 Nsmb = LCD_printStr8x5(u8_to_str(Number), PG, CL);
      CL += 6*Nsmb;
      if(CL > 108) {PG++; CL = 0;}
      if(PG > 7) {PG = 0; LCD_Erase();}
    }
    
    if(B2.BtnON){ 
      B2.BtnON = 0;
      LCD_Erase();
      PG = 0;
      CL = 0;
      randinit();
    }
    
    if(B3.BtnON){ 
      B3.BtnON = 0;
      LCD_printStr8x5(Array, 0, 0);
    }
    
    if(B4.BtnON) {
        B4.BtnON = 0; 
        if(B4.Toggle) prntClk = 0; 
        else prntClk = 1;
    }
    
    if(B5.BtnON) {
        B5.BtnON = 0; 
        countPeriod = GetPrd();
    }
    if(B6.BtnON) {
        B6.BtnON = 0;
        if(B6.Toggle)countDirect = 0;
        else countDirect = 1;
    }
    
    if(B7.BtnON){B7.BtnON = 0;}
    if(B8.BtnON){B8.BtnON = 0;}
    
    Counting(countPeriod, 1, countDirect, 359999);
    Time.hour = mainTimeCounter/3600;
    Time.min = (mainTimeCounter%3600)/60;
    Time.sec = mainTimeCounter%60;
    if(prntClk) LCD_PrintClock(Time.hour, Time.min, Time.sec);
  }
/*----------------------------------------------------------------------------*/
  return;
}
