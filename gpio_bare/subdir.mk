################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./main.cpp 

C_SRCS += 

S_UPPER_SRCS += \
./vectors.S 

OBJS += \
./vectors.o \
./main.o 

INCLUDES += -I bsp -I external_devices

CPP_OPTS += -O0 -Wall -c -fmessage-length=0 -nostdlib -nostartfiles -ffreestanding -fno-exceptions -fno-rtti

C_OPTS += -O0 -g3 -Wall -c -fmessage-length=0

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
	arm-none-eabi-g++ ${INCLUDES} ${CPP_OPTS} -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc ${INCLUDES} ${C_OPTS}  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


