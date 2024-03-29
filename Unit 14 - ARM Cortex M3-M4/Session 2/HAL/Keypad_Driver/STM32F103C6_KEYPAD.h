/*
 * STM32F103C6_KEYPAD.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Bahaa
 */

#ifndef KEYPAD_DRIVER_STM32F103C6_KEYPAD_H_
#define KEYPAD_DRIVER_STM32F103C6_KEYPAD_H_

#define F_CPU 1000000UL

#include <Stm32_F103C6_gpio_driver.h>

#define KEYPAD_PORT GPIOB

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

//-------------------------------------------------
// KEYPAD FUNCTIONS
//-------------------------------------------------


void KEYPAD_INIT(void);

char KEYPAD_GET_KEY(void);

#endif /* KEYPAD_DRIVER_STM32F103C6_KEYPAD_H_ */
