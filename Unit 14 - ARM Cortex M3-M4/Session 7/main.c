/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <core_cm3.h>

#include <stm32f103x6.h>
#include <Stm32_F103C6_gpio_driver.h>
#include <Stm32_F103C6_EXTI_driver.h>
#include <STM32F103C6_LCD.h>
#include <STM32F103C6_KEYPAD.h>



unsigned int IRQ_Flag = 0;


void OS_SVC_services(int* StackFramePointer)
{
	//OS_SVC_Set Stack -> r0 -> argument 0 = StackFramePointer
	// OS_SVC_Set Stack : r0,r1,r2,r3,r12,LR,PC,XPSR

	unsigned char SVC_number ;
	unsigned int val1,val2 ;

	SVC_number = *((unsigned char*)(((unsigned char*)StackFramePointer[6])-2)) ;
	val1 = StackFramePointer[0];
	val2 = StackFramePointer[1];
	switch (SVC_number)
	{
	case 1: //ADD
		StackFramePointer[0] = val1 + val2 ;
		break;
	case 2: //SUB
		StackFramePointer[0] = val1 - val2 ;
		break;
	case 3: //MULTIPLY
		StackFramePointer[0] = val1 * val2 ;
		break;
	case 4: //PendSV
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
		break;
	}
}

__attribute ((naked)) void SVC_Handler()
{
	__asm("tst lr,#4 \n\t "
			"ITE EQ \n\t"
			"mrseq r0,MSP \n\t"
			"mrsne r0,PSP \n\t"
			"B OS_SVC_services");
}

int OS_SVC_Set(int a,int b, int SVC_ID)
{
	int result ;
	switch (SVC_ID)
	{
	case 1: //ADD
		__asm("svc #0x01");
		break;

	case 2: //SUB
		__asm("svc #0x02");
		break;

	case 3: //MULTIPLY
		__asm("svc #0x03");
		break;
	case 4: //PendSV
		__asm("svc #0x04");
		break;
	}
	__asm("mov %[output],r0"
			: [output] "=r" (result));

	return result;
}
int main(void)
{
	IRQ_Flag = OS_SVC_Set(3,2,1);//add
	IRQ_Flag = OS_SVC_Set(3,2,2);//sub
	IRQ_Flag = OS_SVC_Set(3,2,3);//multiply
	IRQ_Flag = OS_SVC_Set(0, 0, 4);//PendSV
	while(1);
}
