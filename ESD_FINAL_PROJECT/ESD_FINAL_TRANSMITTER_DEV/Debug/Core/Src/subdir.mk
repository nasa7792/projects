################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/I2C_driver.c \
../Core/Src/NMEA.c \
../Core/Src/NRF_DRIVER.c \
../Core/Src/SPI.c \
../Core/Src/delay.c \
../Core/Src/fatfs_sd_card.c \
../Core/Src/formated_printf.c \
../Core/Src/gps.c \
../Core/Src/main.c \
../Core/Src/max_heart_sensor_driver.c \
../Core/Src/sd_card.c \
../Core/Src/spo2_algorithm.c \
../Core/Src/state_machine.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/uartRingBuffer.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/I2C_driver.o \
./Core/Src/NMEA.o \
./Core/Src/NRF_DRIVER.o \
./Core/Src/SPI.o \
./Core/Src/delay.o \
./Core/Src/fatfs_sd_card.o \
./Core/Src/formated_printf.o \
./Core/Src/gps.o \
./Core/Src/main.o \
./Core/Src/max_heart_sensor_driver.o \
./Core/Src/sd_card.o \
./Core/Src/spo2_algorithm.o \
./Core/Src/state_machine.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/uartRingBuffer.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/I2C_driver.d \
./Core/Src/NMEA.d \
./Core/Src/NRF_DRIVER.d \
./Core/Src/SPI.d \
./Core/Src/delay.d \
./Core/Src/fatfs_sd_card.d \
./Core/Src/formated_printf.d \
./Core/Src/gps.d \
./Core/Src/main.d \
./Core/Src/max_heart_sensor_driver.d \
./Core/Src/sd_card.d \
./Core/Src/spo2_algorithm.d \
./Core/Src/state_machine.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/uartRingBuffer.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/I2C_driver.cyclo ./Core/Src/I2C_driver.d ./Core/Src/I2C_driver.o ./Core/Src/I2C_driver.su ./Core/Src/NMEA.cyclo ./Core/Src/NMEA.d ./Core/Src/NMEA.o ./Core/Src/NMEA.su ./Core/Src/NRF_DRIVER.cyclo ./Core/Src/NRF_DRIVER.d ./Core/Src/NRF_DRIVER.o ./Core/Src/NRF_DRIVER.su ./Core/Src/SPI.cyclo ./Core/Src/SPI.d ./Core/Src/SPI.o ./Core/Src/SPI.su ./Core/Src/delay.cyclo ./Core/Src/delay.d ./Core/Src/delay.o ./Core/Src/delay.su ./Core/Src/fatfs_sd_card.cyclo ./Core/Src/fatfs_sd_card.d ./Core/Src/fatfs_sd_card.o ./Core/Src/fatfs_sd_card.su ./Core/Src/formated_printf.cyclo ./Core/Src/formated_printf.d ./Core/Src/formated_printf.o ./Core/Src/formated_printf.su ./Core/Src/gps.cyclo ./Core/Src/gps.d ./Core/Src/gps.o ./Core/Src/gps.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/max_heart_sensor_driver.cyclo ./Core/Src/max_heart_sensor_driver.d ./Core/Src/max_heart_sensor_driver.o ./Core/Src/max_heart_sensor_driver.su ./Core/Src/sd_card.cyclo ./Core/Src/sd_card.d ./Core/Src/sd_card.o ./Core/Src/sd_card.su ./Core/Src/spo2_algorithm.cyclo ./Core/Src/spo2_algorithm.d ./Core/Src/spo2_algorithm.o ./Core/Src/spo2_algorithm.su ./Core/Src/state_machine.cyclo ./Core/Src/state_machine.d ./Core/Src/state_machine.o ./Core/Src/state_machine.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/uartRingBuffer.cyclo ./Core/Src/uartRingBuffer.d ./Core/Src/uartRingBuffer.o ./Core/Src/uartRingBuffer.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

