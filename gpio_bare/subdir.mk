################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./main.cpp 

C_SRCS += 

S_UPPER_SRCS += \
./0_link_first.S 

OBJS += \
./0_link_first.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ./%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	arm-none-eabi-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-none-eabi-g++ -I"/Users/jonathanhendrix/git/rPi/gpio_bare/bsp" -O0 -Wall -c -fmessage-length=0 -nostdlib -nostartfiles -ffreestanding -fno-exceptions -fno-rtti -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -I"/Users/jonathanhendrix/git/rPi/gpio_bare/bsp" -O0 -g3 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


