/*
 * Stm32_F1103C6_gpio_driver.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Bahaa
 */

#include "Stm32_F1103C6_EXTI_driver.h"

//-*-*-*-*-*-*-*-*-*-*-*-
//Global Variables
//-*-*-*-*-*-*-*-*-*-*-*
void (*GP_IRQ_CallBack[15])(void);

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*

#define AFIO_GPIO_EXTI_Mapping(x)	x==GPIOA ? 0:\
									x==GPIOB ? 1:\
									x==GPIOC ? 2:\
									x==GPIOD ? 3:0

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Functions
//-*-*-*-*-*-*-*-*-*-*-*

void NVIC_Enable(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI9_5_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI15_10_Enable;
		break;
	}
}

void NVIC_Disable(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI9_5_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI15_10_Disable;
		break;
	}
}



//-*-*-*-*-*-*-*-*-*-*-*-
//APIs Functions
//-*-*-*-*-*-*-*-*-*-*-*


void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR = 	0x00000000;
	EXTI->EMR = 	0x00000000;
	EXTI->RTSR = 	0x00000000;
	EXTI->FTSR = 	0x00000000;
	EXTI->SWIER = 	0x00000000;
	EXTI->PR = 		0xFFFFFFFF;

	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI9_5_Disable;
	NVIC_IRQ40_EXTI15_10_Disable;
}

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_Config)
{
	MCAL_EXTI_GPIO_Update(EXTI_Config);
}

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
	//FIRST set pin to input floating
	GPIO_PinConfig_t PinCfg;
	PinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, &PinCfg);


	//SECOND updating the AFIO
	uint8_t AFIO_Index = EXTI_Config->EXTI_PIN.ETI_InputLineNumber / 4  ;
	uint8_t AFIO_Pos = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber % 4) * 4 ;
	//clear the 4 bits
	AFIO->EXTICR[AFIO_Index] &= ~(0xf << AFIO_Pos);
	//setting the 4 bits
	AFIO->EXTICR[AFIO_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0x0F)<<AFIO_Pos);


	//THIRD setting the triggering edge
	//resetting rising and falling bits
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	if(EXTI_Config->EXTI_Trigger == EXTI_Trigger_Rising)
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	else if (EXTI_Config->EXTI_Trigger == EXTI_Trigger_Falling)
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	else if(EXTI_Config->EXTI_Trigger == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}


	//FORTH updating IRQ callback
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;


	//FIFTH enabling/disabling the interrupt and NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		NVIC_Enable(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
	else if(EXTI_Config->IRQ_EN == EXTI_IRQ_Disable)
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		NVIC_Disable(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	}
}

//-*-*-*-*-*-*-*-*-*-*-*-
//ISR Functions
//-*-*-*-*-*-*-*-*-*-*-*

void EXTI0_IRQHandler(void)
{
	//clear the pending bit
	EXTI->PR |= 1<<0;
	//callback function
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	//clear the pending bit
	EXTI->PR |= 1<<1;
	//callback function
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler(void)
{
	//clear the pending bit
	EXTI->PR |= 1<<2;
	//callback function
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler(void)
{
	//clear the pending bit
	EXTI->PR |= 1<<3;
	//callback function
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler(void)
{
	//clear the pending bit
	EXTI->PR |= 1<<4;
	//callback function
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5)
	{
		EXTI->PR = 1<<5;
		GP_IRQ_CallBack[5]();
	}
	if(EXTI->PR & 1<<6)
	{
		EXTI->PR = 1<<6;
		GP_IRQ_CallBack[6]();
	}
	if(EXTI->PR & 1<<7)
	{
		EXTI->PR = 1<<7;
		GP_IRQ_CallBack[7]();
	}
	if(EXTI->PR & 1<<8)
	{
		EXTI->PR = 1<<8;
		GP_IRQ_CallBack[8]();
	}
	if(EXTI->PR & 1<<9)
	{
		EXTI->PR = 1<<9;
		GP_IRQ_CallBack[9]();
	}

}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10)
	{
		EXTI->PR = 1<<10;
		GP_IRQ_CallBack[10]();
	}
	if(EXTI->PR & 1<<11)
	{
		EXTI->PR = 1<<11;
		GP_IRQ_CallBack[11]();
	}
	if(EXTI->PR & 1<<12)
	{
		EXTI->PR = 1<<12;
		GP_IRQ_CallBack[12]();
	}
	if(EXTI->PR & 1<<13)
	{
		EXTI->PR = 1<<13;
		GP_IRQ_CallBack[13]();
	}
	if(EXTI->PR & 1<<14)
	{
		EXTI->PR = 1<<14;
		GP_IRQ_CallBack[14]();
	}
	if(EXTI->PR & 1<<15)
	{
		EXTI->PR = 1<<15;
		GP_IRQ_CallBack[15]();
	}

}

