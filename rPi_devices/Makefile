
RM := rm -rf

LIBS := 

CPP := arm-none-eabi-g++

AR := arm-none-eabi-ar

CPP_SRCS += \
../i2c.cpp 

OBJS += \
./i2c.o 

# All Target
all: librPi_devices.a

# Tool invocations
librPi_devices.a: $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Archiver'
	$(AR) -r  "librPi_devices.a" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CPP) -O0 -g3 -Wall -c -fmessage-length=0 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Other Targets
clean:
	-$(RM) *.o librPi_devices.a
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
