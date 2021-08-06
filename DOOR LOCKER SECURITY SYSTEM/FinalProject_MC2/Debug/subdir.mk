################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_Motor.c \
../MC2.c \
../Timer0.c \
../external_eeprom.c \
../i2c.c \
../lcd.c \
../password.c \
../uart.c 

OBJS += \
./DC_Motor.o \
./MC2.o \
./Timer0.o \
./external_eeprom.o \
./i2c.o \
./lcd.o \
./password.o \
./uart.o 

C_DEPS += \
./DC_Motor.d \
./MC2.d \
./Timer0.d \
./external_eeprom.d \
./i2c.d \
./lcd.d \
./password.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


