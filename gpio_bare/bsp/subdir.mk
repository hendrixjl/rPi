################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
./bsp/arm_timer.c \
./bsp/interrupts.c \
./bsp/uart.c

CPP_SRCS += \
./bsp/uarts.cpp 

OBJS += \
./bsp/arm_timer.o \
./bsp/interrupts.o \
./bsp/uart.o \
./bsp/uarts.o



# Each subdirectory must supply rules for building sources it contributes
bsp/%.o: ../bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -I"/Users/jonathanhendrix/git/rPi/gpio_bare/bsp" -O0 -g3 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


