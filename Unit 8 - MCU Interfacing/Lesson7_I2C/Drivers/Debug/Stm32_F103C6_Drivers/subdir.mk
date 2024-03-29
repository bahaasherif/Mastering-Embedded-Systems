################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_I2C_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_RCC_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_SPI_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_USART_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.c 

OBJS += \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_I2C_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_RCC_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_SPI_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_USART_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_I2C_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_RCC_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_SPI_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_USART_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/I2C_Slave_EEPROM" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/Keypad_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/LCD_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32_F103C6_Drivers/Stm32_F103C6_I2C_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_I2C_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/I2C_Slave_EEPROM" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/Keypad_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/LCD_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_I2C_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32_F103C6_Drivers/Stm32_F103C6_RCC_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_RCC_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/I2C_Slave_EEPROM" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/Keypad_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/LCD_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_RCC_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32_F103C6_Drivers/Stm32_F103C6_SPI_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_SPI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/I2C_Slave_EEPROM" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/Keypad_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/LCD_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_SPI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32_F103C6_Drivers/Stm32_F103C6_USART_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_USART_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/I2C_Slave_EEPROM" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/Keypad_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/LCD_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_USART_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/I2C_Slave_EEPROM" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/Keypad_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/HAL/LCD_Driver" -I"D:/sho8l/embedded diploma/units_lab/unit8_lesson7/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

