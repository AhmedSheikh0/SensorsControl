#include "../../LIB/STD_Types.h"
#include "../../LIB/Bit_Math.h"
#include "../Timer/Timer0_Interface.h"
#include "../Timer/Timer0/Timer0_Interface.h"
#include "../Timer/Timer1/Timer1_Interface.h"
#include "../Timer/Timer2/Timer2_Interface.h"


#include "Timers_Config.h"
#include "Timers_Private.h"
#include "Timers_Register.h"

static void (*TIMER0_pvCallBack)(void) = NULL;
static void (*TIMER2_pvCallBack)(void) = NULL;

void TIMER0_voidSetCompMatch( u8 Copyu8Value )
{
	OCR0 = Copyu8Value;
}

void TIMER0_voidInit(void)
{

#if		TIMER0_MODE	== NORMAL_MODE
	/* Choose Normal Mode */
	Clear_Bit(TCCR0, TCCR0_WGW00);
	Clear_Bit(TCCR0, TCCR0_WGW01);

#elif	TIMER0_MODE	== PWM_MODE
	/* Choose PWM Mode */
	Set_Bit(TCCR0, TCCR0_WGW00);
	Clear_Bit(TCCR0, TCCR0_WGW01);

#elif	TIMER0_MODE	== CTC_MODE
	/* Choose PWM Mode */
	Clear_Bit(TCCR0, TCCR0_WGW00);
	Set_Bit(TCCR0, TCCR0_WGW01);

#elif	TIMER0_MODE	== FAST_PWM_MODE
	/* Choose Fast PWM Mode */
	Set_Bit(TCCR0, TCCR0_WGW00);
	Set_Bit(TCCR0, TCCR0_WGW01);
#else
#error "Wrong Input"
#endif


	// output Overflow Interrupt
    Set_Bit(TIMSK, TIMSK_TOIE);


	/* Clear on Top, Set on Comp */
	Set_Bit(TCCR0, TCCR0_COM01);
	Clear_Bit(TCCR0, TCCR0_COM00);

	/* Set Compare Match */
	//TIMER0_voidSetCompMatch(64);

#if		PRESCALER_SELECT == DIV_BY_8
	/* Prescaler Division by 8 */
	Clear_Bit(TCCR0, TCCR0_CS00);
	Set_Bit(TCCR0, TCCR0_CS01);
	Clear_Bit(TCCR0, TCCR0_CS02);
#elif	PRESCALER_SELECT == DIV_BY_64
	/* Prescaler Division by 64 */
	Set_Bit(TCCR0, TCCR0_CS00);
	Set_Bit(TCCR0, TCCR0_CS01);
	Clear_Bit(TCCR0, TCCR0_CS02);
#elif	PRESCALER_SELECT == DIV_BY_256
	/* Prescaler Division by 256 */
	Clear_Bit(TCCR0, TCCR0_CS00);
	Clear_Bit(TCCR0, TCCR0_CS01);
	Set_Bit(TCCR0, TCCR0_CS02);
#elif	PRESCALER_SELECT == DIV_BY_1024
	/* Prescaler Division by 1024 */
	Set_Bit(TCCR0, TCCR0_CS00);
	Clear_Bit(TCCR0, TCCR0_CS01);
	Set_Bit(TCCR0, TCCR0_CS02);
#elif	PRESCALER_SELECT == EXT_CLOCK
	/* Prescaler External Clock */
	Clear_Bit(TCCR0, TCCR0_CS00);
	Set_Bit(TCCR0, TCCR0_CS01);
	Set_Bit(TCCR0, TCCR0_CS02);
#else
#endif

}

u8 TIMER0_u8GetTCNT0()
{
	return TCNT0;
}

void TIMER0_voidSetTCNT0(u8 Copy_u8Value)
{
	TCNT0 = Copy_u8Value;
}

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackfunc)(void))
{
	u8 Local_u8ERROR = OK;

	if(Copy_pvCallBackfunc != NULL)
	{
		TIMER0_pvCallBack = Copy_pvCallBackfunc;
	}
	else
	{
		Local_u8ERROR = NOK;
	}

	return Local_u8ERROR;
}

void TIMER1_voidInit(void)
{
	/* Set Mode to Non Inverting Fast PWM Mode */
	Set_Bit(TCCR1A,TCCR1A_COM1A1);
	Clear_Bit(TCCR1A,TCCR1A_COM1A0);
	Set_Bit(TCCR1A, TCCR1A_COM1B1);

	/* Set Waveform to fast PWM */
	Clear_Bit(TCCR1A, TCCR1A_WGM10);
	Set_Bit(TCCR1A,TCCR1A_WGM11);
	Set_Bit(TCCR1B,TCCR1B_WGM12);
	Set_Bit(TCCR1B,TCCR1B_WGM13);

	/* Set Prescaler   */
//	TCCR1B &= Prescaler_Mask;
	//TCCR1B |= DIV_BY_8;

	Set_Bit(TCCR1B, TCCR1B_CS10); // Prescaler 64
	Set_Bit(TCCR1B, TCCR1B_CS11); // Prescaler 64


}

void TIMER1_voidSetICR( u16 Copyu16Top )
{
	ICR1 = Copyu16Top;

}

void TIMER1_voidSetDutyCycle( u16 Copyu16Value )
{
	OCR1A = Copyu16Value;
}

void TIMER2_voidInit(void)
{

#if		TIMER2_MODE	== NORMAL_MODE
	/* Choose Normal Mode */
	Clear_Bit(TCCR2, TCCR2_WGW20);
	Clear_Bit(TCCR2, TCCR2_WGW21);

#elif	TIMER2_MODE	== PWM_MODE
	/* Choose PWM Mode */
	Set_Bit(TCCR2, TCCR2_WGW00);
	Clear_Bit(TCCR2, TCCR2_WGW01);

#elif	TIMER2_MODE	== CTC_MODE
	/* Choose PWM Mode */
	Clear_Bit(TCCR2, TCCR2_WGW20);
	Set_Bit(TCCR2, TCCR2_WGW21);

#elif	TIMER2_MODE	== FAST_PWM_MODE
	/* Choose Fast PWM Mode */
	Set_Bit(TCCR2, TCCR2_WGW20);
	Set_Bit(TCCR2, TCCR2_WGW21);
#else
#error "Wrong Input"
#endif


	// output Overflow Interrupt
    Set_Bit(TIMSK, TIMSK_TOIE);


	/* Clear on Top, Set on Comp */
	Set_Bit(TCCR2, TCCR2_COM21);
	Clear_Bit(TCCR2, TCCR2_COM20);

	/* Set Compare Match */
	//TIMER0_voidSetCompMatch(64);

#if		PRESCALER_SELECT == DIV_BY_8
	/* Prescaler Division by 8 */
	Clear_Bit(TCCR2, TCCR2_CS20);
	Set_Bit(TCCR2, TCCR2_CS21);
	Clear_Bit(TCCR2, TCCR0_CS22);
#elif	PRESCALER_SELECT == DIV_BY_64
	/* Prescaler Division by 64 */
	Set_Bit(TCCR2, TCCR2_CS20);
	Set_Bit(TCCR2, TCCR2_CS21);
	Clear_Bit(TCCR2, TCCR2_CS22);
#elif	PRESCALER_SELECT == DIV_BY_256
	/* Prescaler Division by 256 */
	Clear_Bit(TCCR2, TCCR2_CS20);
	Clear_Bit(TCCR2, TCCR2_CS21);
	Set_Bit(TCCR2, TCCR2_CS22);
#elif	PRESCALER_SELECT == DIV_BY_1024
	/* Prescaler Division by 1024 */
	Set_Bit(TCCR2, TCCR2_CS20);
	Clear_Bit(TCCR2, TCCR2_CS21);
	Set_Bit(TCCR2, TCCR2_CS22);
#elif	PRESCALER_SELECT == EXT_CLOCK
	/* Prescaler External Clock */
	Clear_Bit(TCCR2, TCCR2_CS20);
	Set_Bit(TCCR2, TCCR2_CS21);
	Set_Bit(TCCR2, TCCR2_CS22);
#else
#endif

}




void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	if( TIMER0_pvCallBack != NULL)
	{
		TIMER0_pvCallBack();
	}
}

void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	if( TIMER0_pvCallBack != NULL)
	{
		TIMER0_pvCallBack();
	}
}



void __vector_4(void)  __attribute__((signal));
void __vector_4(void)
{
	if( TIMER2_pvCallBack != NULL)
	{
		TIMER2_pvCallBack();
	}
}

void __vector_5(void)  __attribute__((signal));
void __vector_5(void)
{
	if( TIMER2_pvCallBack != NULL)
	{
		TIMER2_pvCallBack();
	}
}

