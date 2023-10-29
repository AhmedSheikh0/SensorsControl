#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


void TIMER0_voidInit(void);

void TIMER0_voidSetCompMatch( u8 Copyu8Value );

u8 TIMER0_u8SetCallBack( void (*Copy_pvCallBackfunc)(void) );

void TIMER0_voidSetTCNT0(u8 Copy_u8Value);

u8 TIMER0_u8GetTCNT0();

void TIMER1_voidInit(void);

void TIMER1_voidSetICR( u16 Copyu16Top );

void TIMER1_voidSetDutyCycle( u16 Copyu16Value );




#endif
