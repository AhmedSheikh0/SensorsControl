#ifndef TIMERS_REGISTER_H_
#define TIMERS_REGISTER_H_


#define TCCR0               *((volatile u8 *) 0x53)
#define TCCR0_WGW00         6
#define TCCR0_WGW01         3
#define TCCR0_COM00         4
#define TCCR0_COM01         5
#define TCCR0_CS02          2
#define TCCR0_CS01          1
#define TCCR0_CS00          0

#define TCCR2 				*( (volatile u8 *) 0x45)
#define TCCR2_WGW20         6
#define TCCR2_WGW21         3
#define TCCR2_COM20         4
#define TCCR2_COM21         5
#define TCCR2_CS22          2
#define TCCR2_CS21          1
#define TCCR2_CS20          0


#define TCNT0				*((volatile u8 *) 0x52)

#define OCR0                *((volatile u8 *) 0x5C)

#define TIMSK               *((volatile u8 *) 0x59)
#define TIMSK_OCIE0         1
#define TIMSK_TOIE			0


#define TCCR1B               *((volatile u8 *) 0x4E)
#define TCCR1B_CS12		2
#define TCCR1B_CS11		1
#define TCCR1B_CS10		0

#define ICR1               	 *((volatile u16 *) 0x46)
#define OCR1A                *((volatile u16 *) 0x4A)

#define TCCR1A               *((volatile u8 *) 0x4F)

#define TCCR1A_WGM10 		 0
#define TCCR1A_WGM11 		 1

#define TCCR1A_COM1A0 		 6
#define TCCR1A_COM1A1		 7

#define TCCR1A_COM1B1		 5
#define TCCR1A_COM1B0		 4

#define TCCR1B_WGM12 		 3
#define TCCR1B_WGM13 		 4

#define Prescaler_Mask		 0b11111000

#endif
