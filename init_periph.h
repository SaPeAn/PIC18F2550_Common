/* 
 * File:   init_periph.h
 * Author: SaPA
 *
 * Created on 14 �������� 2024 �., 10:50
 */

#ifndef INIT_PERIPH_H
#define	INIT_PERIPH_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void Interrupt_init(void);
void TMR0_init(void);
void TMR1_init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* INIT_PERIPH_H */

