/*
 * main.c
 *
 *  Created on: Oct 28, 2023
 *      Author: AHMED
 */

/* ADC PROJECT*/
/**************************************/
#include "LIB/STD_TYPES.h"
#include <avr/delay.h>

#include "HAL/LCD2/LCD_Interface.h"


#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/Port/Port_Interface.h"
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/ADC/NTI_ADC_Interface.h"
#include "MCAL/EXT_INT/EXT_INT_Interface.h"

#define CH_0	0
#define CH_1	1
#define CH_4	4


f32 volatile Globalu8Readings[5] = {0};
u8 Sensor_index = 0;

void ADC_LM35()
{
	Globalu8Readings[Sensor_index] = (f32)ADC_u16ReadADCInMV() > 1500 ? 1500 : (f32)ADC_u16ReadADCInMV()/10 ;
}
void ADC_LDR()
{
//	u16 Local_u16LDRRead = ADC_u16ReadADCInMV();
	Globalu8Readings[Sensor_index] = (f32)ADC_u16ReadADCInMV()/1000UL;
}
void ADC_POT()
{
//	u16 Local_u16POTRead = ADC_u16ReadADCInMV();
	Globalu8Readings[Sensor_index] = (f32)ADC_u16ReadADCInMV()/1000UL;

}



void ADC_voidChannelRun()
{
	ADC_voidDisable();

	if(Sensor_index == CH_0)
	{
		ADC_LM35();
		Sensor_index = 1;
	}
	else if(Sensor_index == CH_1)
	{
		ADC_POT();
		Sensor_index = 4;
	}
	else if(Sensor_index == CH_4)
	{
		ADC_LDR();
		Sensor_index = 0;
	}
	else
	{
		Sensor_index = 0;
	}
}

void LM32_Interrupt()
{
	LCD_voidGoToPosition(1,0);
	LCD_voidWriteString((u8*)"LM35 value:");
	LCD_voidWriteFloatData(Globalu8Readings[CH_0]);
	LCD_voidWriteString((u8*)" C");
}
void LDR_Interrupt()
{
	LCD_voidGoToPosition(3,0);
	LCD_voidWriteString((u8*)"LDR value:");
	LCD_voidWriteFloatData(Globalu8Readings[CH_4]);
	LCD_voidWriteString((u8*)" volt");
}
void POT_Interrupt()
{
	LCD_voidGoToPosition(2,0);
	LCD_voidWriteString((u8*)"POT value:");
	LCD_voidWriteFloatData(Globalu8Readings[CH_1]);
	LCD_voidWriteString((u8*)" volt");
}



int main(void)
{
	PORT_voidInit();
	LCD_voidInit();
	GIE_voidEnable();
	EXTI0_voidInit();
	EXTI1_voidInit();
	EXTI2_voidInit();
	EXTI2_voidEnable();
	EXTI1_voidEnable();
	EXTI0_voidEnable();
	ADC_voidEnable();
	ADC_voidInterrputEnable();
	ADC_voidStartInterruptConversion(CH_0); // Start First Conversion

	ADC_SetCallback(ADC_voidChannelRun); // Call Back Function

	// ISR Functions
	EXT0_VID_SET_CALL_BACK(LM32_Interrupt);
	EXT1_VID_SET_CALL_BACK(POT_Interrupt);
	EXT2_VID_SET_CALL_BACK(LDR_Interrupt);

	while(1)
	{
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_0, DIO_u8PIN_HIGH);	// LM35
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_1, DIO_u8PIN_HIGH);	// POT
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_2, DIO_u8PIN_HIGH);	// LDR

//		DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN_2, DIO_u8PIN_HIGH);
//		DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN_3, DIO_u8PIN_HIGH);
//		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN_2, DIO_u8PIN_HIGH);

		if(Globalu8Readings[CH_0] > 28)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_0, DIO_u8PIN_LOW); // Interrupt Occur
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_3, DIO_u8PIN_HIGH);
			_delay_ms(150);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_3, DIO_u8PIN_LOW);

		}
		else
		{
			LCD_voidClearLine(1,19);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_0, DIO_u8PIN_HIGH);
		}

		if(Globalu8Readings[CH_1] > 2.5f)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_1, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_4, DIO_u8PIN_HIGH);
			_delay_ms(150);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_4, DIO_u8PIN_LOW);

		}
		else
		{
			LCD_voidClearLine(2,19);
			DIO_u8SetPinValue(DIO_u8PORTD, DIO_u8PIN_1, DIO_u8PIN_HIGH);

		}

		if(Globalu8Readings[CH_4] > 2.5f)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_2, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_5, DIO_u8PIN_HIGH);
			_delay_ms(150);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_5, DIO_u8PIN_LOW);

		}
		else
		{
			LCD_voidClearLine(3,19);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN_2, DIO_u8PIN_HIGH);
		}

		ADC_voidEnable();
		ADC_voidStartInterruptConversion(Sensor_index);
	}

	return 0;
}



