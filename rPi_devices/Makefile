
RM := rm -rf

LIBS := 

CPP := g++ # arm-none-eabi-g++

AR := ar # arm-none-eabi-ar

CPP_SRCS += \
../main.cpp 

OBJS += \
./main.o 

# All Target
all: librPi_devices_test

# Tool invocations
librPi_devices.a: $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC'
	$(CPP)  "librPi_devices_test" $(OBJS) $(LIBS)
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
	-$(RM) *.o librPi_devices_test
	-@echo ' '

.PHONY: all clean dependents
