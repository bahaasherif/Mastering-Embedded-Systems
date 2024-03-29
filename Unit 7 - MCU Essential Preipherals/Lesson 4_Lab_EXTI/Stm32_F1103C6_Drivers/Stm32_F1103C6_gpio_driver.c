/*
 * Stm32_F1103C6_gpio_driver.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Bahaa
 */

#include "Stm32_F1103C6_gpio_driver.h"

uint8_t Get_CRLH_POSITION(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}


void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t* PinConfig)
{
	//Port configuration register Low (GPIO_CRL) Configure Pins from 0 to 7
	//Port configuration register High (GPIO_CRH) Configure Pins from 8 to 15

	volatile uint32_t *configregister = NULL ;
	uint8_t Pin_Conf = 0;

	configregister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNFx and MODEx
	(*configregister) &= ~(0xf << Get_CRLH_POSITION(PinConfig->GPIO_PinNumber));

	//if Pin is output
	if(		PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD 	||
			PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_PP 	||
			PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD 	||
			PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP )
	{
		//set CNFx and MODEx
		Pin_Conf = (((PinConfig->GPIO_Mode - 4) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0f;
	}
	//if Pin in input
	else //Mode == 00
	{
		if(PinConfig->GPIO_Mode == GPIO_MODE_ANALOG || PinConfig->GPIO_Mode == GPIO_MODE_INPUT_FLO)
		{
			//set CNFx and MODEx
			Pin_Conf = ((PinConfig->GPIO_Mode << 2) | 0x0) & 0x0f;
		}
		else if(PinConfig->GPIO_Mode == GPIO_MODE_AF_INPUT) // consider it as input floating
		{
			//set CNFx and MODEx
			Pin_Conf = ((GPIO_MODE_INPUT_FLO << 2) | 0x0) & 0x0f;
		}
		else //PU and PD Input
		{
			Pin_Conf = ((GPIO_MODE_INPUT_PU << 2) | 0x0) & 0x0f;

			if(PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU)
			{
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}

	*configregister |= ((Pin_Conf) << Get_CRLH_POSITION(PinConfig->GPIO_PinNumber));
}


void MCAL_GPIO_DeInit	(GPIO_TypeDef *GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= 1<<2 ;
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= 1<<3 ;
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= 1<<4 ;
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= 1<<5 ;
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE)
		{
			RCC->APB2RSTR |= 1<<6 ;
			RCC->APB2RSTR &= ~(1<<6);
		}
}


uint8_t MCAL_GPIO_ReadPin	(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	uint8_t bit;
	if((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_reset)
		bit = GPIO_PIN_set;
	else
		bit = GPIO_PIN_reset;
	return bit;
}


uint16_t MCAL_GPIO_ReadPort	(GPIO_TypeDef *GPIOx)
{
	uint16_t PortValue = (uint16_t)GPIOx->IDR;
	return PortValue;
}


void MCAL_GPIO_WritePin	(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if(Value != GPIO_PIN_reset)
	{
//		GPIOx->ODR |= PinNumber;
//		or
//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
//		These bits are write-only and can be accessed in Word mode only.
//		0: No action on the corresponding ODRx bit
//		1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
//		BRy: Port x Reset bit y (y= 0 .. 15)
//		These bits are write-only and can be accessed in Word mode only.
//		0: No action on the corresponding ODRx bit
//		1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}


void MCAL_GPIO_WritePort	(GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}


void MCAL_GPIO_TooglePin	(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}


uint8_t MCAL_GPIO_LockPin	(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
//	Bit 16 LCKK[16]: Lock key
//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	LOCK key writing sequence:
//	Write 1
//	Write 0
//	Write 1
//	Read 0
//	Read 1 (this read is optional but confirms that the lock is active)
//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	Any error in the lock sequence will abort the lock.
//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	These bits are read write but can only be written when the LCKK bit is 0.
//	0: Port configuration not locked
//	1: Port configuration locked.


	//Set LCKK[16]
	volatile uint32_t tmp = 1<<16;

	//Set LCKy
	tmp |= PinNumber;

	//	LOCK key writing sequence:
	//	Write 1
	GPIOx->LCKR = tmp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = tmp;
	//	Read 0
	tmp = GPIOx->LCKR;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if( (uint32_t)(GPIOx->LCKR & 1<<16))
		return GPIO_RETURN_LOCK_EN;
	else
		return GPIO_RETURN_LOCK_ERROR;

}
