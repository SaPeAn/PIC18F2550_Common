
#include "init_periph.h"
#include <xc.h>

void Interrupt_init(void)
{
  // INTCON
  GIE_GIEH = 1;  PEIE_GIEL = 1;  TMR0IE = 0;  INT0IE = 0;  RBIE = 0; // глоб.прер/глоб.прер высок.ур;  прер.периф./низк.ур.периф.прер; тмр0.переп.разр.прер; внеш.прер.разр; прер.портБ.прер.
  // INTCON2
  RBPU = 0;  INTEDG0 = 0;  INTEDG1 = 0;  INTEDG2 = 0;  TMR0IP = 0;  RBIP = 0; // портБ.пулап(0-pullUp En; 1-pullUp Dis); фронт.внеш.прер.0; фронт.внеш.прер.1; фронт.внеш.прер.2; тмр0прер.приоритет; портБпрер.приоритет.
  // INTCON3
  INT2IP = 0;  INT1IP = 0;  INT2IE = 0;  INT1IE = 0; // приор.внеш.прер2; приор.внеш.прер1; разр.внеш.прер2; разр.внеш.прер1;
  // PIE1 Peripherial Interrapt Enable 1
  ADIE = 0;  RCIE = 0;  TXIE = 0;  SSPIE = 0;  CCP1IE = 0;  TMR2IE = 0;  TMR1IE = 1;  
  // PIE2 Peripherial Interrapt Enable 2
  OSCFIE = 0;  CMIE = 0;  USBIE = 0;  EEIE = 0;  BCLIE = 0;  HLVDIE = 0;  TMR3IE = 0;  CCP2IE = 0;
  //  IPR1 PERIPHERAL INTERRUPT PRIORITY REGISTER 1
  ADIP = 0;  RCIP = 0;  TXIP = 0;  SSPIP = 0;  CCP1IP = 0;  TMR2IP = 0;  TMR1IP = 1;
  //  IPR2 PERIPHERAL INTERRUPT PRIORITY REGISTER 2
  OSCFIP = 0;  CMIP = 0;  USBIP = 0;  EEIP = 0;  BCLIP = 0;  HLVDIP = 0;  TMR3IP = 0;  CCP2IP = 0;
  // RCON RESET CONTROL REGISTER
  IPEN = 0;  SBOREN = 0; 
}

void TMR0_init(void)
{
  T0CON = 0b11000111;
  TMR0L = 32;
  TMR0H = 209;
}

void TMR1_init(void)
{
  T1CON = 0b00000101;
  TMR1L = 32;
  TMR1H = 209;    
}
