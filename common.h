
#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef unsigned char    uint8;
typedef char             int8; 
typedef unsigned int     uint16;
typedef int              int16;
typedef unsigned long    uint32;
typedef long             int32;  

uint32 timestamp = 0; //счетчик милисекунд после включения
void Delay_ms(uint32);
uint8 getrand(uint8);
void randinit(void);
uint8 dig_to_smb(uint8);
uint8* u8_to_str(uint8);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

