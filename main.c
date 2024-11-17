
/*------------------------ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ----------------------------------*/
#include "config.h"
#include "common.h"
#include <stdlib.h>
#include "init_periph.h"
//#include "drv_7seg.h"
#include "drv_buttons.h"
//#include "drv_led096_I2C.h"
//#include "drv_I2C.h"
#include "drv_lcdST7565_SPI.h"
//#include "drv_usart.h"

/*----------------------------------------------------------------------------*/

/*-----------------------ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ--------------------------------*/
uint32 mainTimeCounter = 0;
uint32 dispCounter = 0;
uint32 countTime = 0;
uint16 countPeriod = 1000;
uint8  countDirect = 1;
uint8  countOn = 0;
uint8 Array[] = "Hello, World!!!!";

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

/*----------------------------ДОП. ФУНКЦИИ ДЛЯ MAIN---------------------------*/
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
/*----------------------------------------------------------------------------*/

/*-----------------------------ОБРАБОТКА ПРЕРЫВАНИЙ---------------------------*/
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
/*-------------------------------Инициализация--------------------------------*/
  TMR0_init();
  TMR1_init();
  Interrupt_init();
  randinit();
  //I2C_init();
  //USART_init();
  Delay_ms(100);           // Задержка после включения (для led096))
  LCD_Init();
  LCD_Erase();
  /*//Инициализация led096
  Led096Set(8, 0xD5, 0xF0, 0x8D, 0x14, 0xAF, 0xA4, 0x20, 0x01);
  Led096Clear();*/
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
  
/*--------------------------------Переменные----------------------------------*/
  uint8 prntClk = 1;
  

/*----------------------------------------------------------------------------*/
//------------------------------Game stucts-----------------------
  typedef struct {
    uint8 en;
    uint8 pg;
    uint8 cl;
  } ufo_t;
  
  typedef struct {
    uint8 en;
    uint8 pg;
    uint8 cl;
  } bullet_t;
  
  typedef struct{
    uint8  stat;  // 0 - enemy disable; 1 - enemy enable; 2 - enemy distroed
    uint8  pg;
    uint8  cl;
    uint32 timer;
    uint8  N;
  }comet_t;

//---------------------------------------------------------  
//------------------------------Game vars-----------------------
  ufo_t Tar = {1, 3, 0};
  #define PIU_MAX   4
  #define COMET_MAX 4
  bullet_t Piu[PIU_MAX] = {0};
  comet_t Comet[COMET_MAX] = {0};
  
  
  
//---------------------------------------------------------
  
/*-----------------------------ОСНОВНОЙ ЦИКЛ----------------------------------*/
  while(1)
  {
    //----------COMET PRINT-------------------------------
    for(uint8 i = 0; i < COMET_MAX; i++) 
    {
      if(Comet[i].stat == 1) print_cometa(Comet[i].pg, Comet[i].cl);
      if(Comet[i].stat == 2) print_distr_cometa(Comet[i].pg, Comet[i].cl);
    }
    
    if(Tar.en) print_ufo(Tar.pg, Tar.cl);
    
    //--------PRINT BULLET---------------
    for(uint8 i = 0; i < PIU_MAX; i++)
    {
      if(Piu[i].en){
        print_piu(Piu[i].pg, Piu[i].cl);
        Piu[i].cl += 8;
        if(Piu[i].cl > 120) {
          Piu[i].en = 0;
          Piu[i].cl = 0;
        }
      }
    }
    //-----------------------------------------
    
    TestBtn(&B1); TestBtn(&B2); TestBtn(&B3); TestBtn(&B4); 
    TestBtn(&B5); TestBtn(&B6); TestBtn(&B7); TestBtn(&B8);
    
    if(B2.BtnON || B2.HoldON || B2.StuckON){B2.BtnON = 0; Tar.pg--; if(Tar.pg == 255) Tar.pg = 0;}
    if(B8.BtnON || B8.HoldON || B8.StuckON){B8.BtnON = 0; Tar.pg++; if(Tar.pg == 7) Tar.pg = 6;}
    if(B4.BtnON || B4.HoldON || B4.StuckON){B4.BtnON = 0; Tar.cl += 8; if(Tar.cl > 100) Tar.cl = 100;}
    if(B6.BtnON || B6.HoldON || B6.StuckON){B6.BtnON = 0; Tar.cl -= 8; if(Tar.cl > 100) Tar.cl = 0;}
    
   
    if(B1.BtnON || B1.HoldON || B1.StuckON){ 
      B1.BtnON = 0; 
      for(uint8 i = 0; i < PIU_MAX; i++) {
        if(!Piu[i].en) 
        {
          Piu[i].en = 1; 
          Piu[i].pg = Tar.pg + 1; 
          Piu[i].cl = Tar.cl + 28;
          break;
        }
      }
    }
    
    //--------COMET GENERATOR-------------------------
    
    for(uint8 i = 0; i < COMET_MAX; i++)
    {
      if(Comet[i].stat == 0 && ((timestamp - mainTimeCounter) > 800))
      {
        mainTimeCounter = timestamp;
        Comet[i].stat = 1;
        Comet[i].cl = 100;
        Comet[i].pg = getrand(6);
      }
    }
    //--------------------------------------------------
    //----------COMET MOV-------------------------------
    for(uint8 i = 0; i < COMET_MAX; i++)
    { 
      if((timestamp - Comet[i].timer) > 100)
      {
        Comet[i].timer = timestamp;
        Comet[i].cl -= 4;
        if(Comet[i].cl > 100 || Comet[i].stat == 2) Comet[i].stat = 0;
      }
    }
    
    //------------COLLISION--------------
    for(uint8 j = 0; j < PIU_MAX; j++)
    {
      for(uint8 i = 0; i < COMET_MAX; i++)
      {
        if((Comet[i].cl <= Piu[j].cl && (Comet[i].pg == Piu[j].pg || (Comet[i].pg + 1) == Piu[j].pg)) && Comet[i].stat == 1 && Comet[i].stat == 1 && Piu[j].en)
        {
          Comet[i].stat = 2;
          Piu[j].en = 0;
        }
      }
    }

    for(uint8 i = 0; i < COMET_MAX; i++)
    {
      if((Comet[i].cl <= (Tar.cl+26) && (Comet[i].pg == Tar.pg || (Comet[i].pg + 1) == Tar.pg)) && Comet[i].stat == 1 && Tar.en)
      {
        Comet[i].stat = 2;
        Tar.en = 0;
      }
    }

    Delay_ms(50);
    LCD_Erase();
    
    /*Counting(countPeriod, 1, countDirect, 359999);
    Time.hour = (uint8)(mainTimeCounter/3600);
    Time.min = (uint8)((mainTimeCounter%3600)/60);
    Time.sec = (uint8)(mainTimeCounter%60);
    if(prntClk) LCD_PrintClock(Time.hour, Time.min, Time.sec);*/
  }
/*----------------------------------------------------------------------------*/
  //return;
}