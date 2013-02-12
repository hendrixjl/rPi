RM := rm -rf

TARGET := rPi_devices_test

LIBS := 

CPP := g++ # arm-none-eabi-g++

CPPOPTS := -std=c++0x -O0 -g3 -Wall -fmessage-length=0

AR := ar # arm-none-eabi-ar

CPP_SRCS += $(shell list *.cpp) 

OBJS += $(patsubst %.cpp, %.o, $(CPPSRCS))

# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC'
	$(CPP)  -o "rPi_devices_test" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CPP) $(CPPOPTS)  -o "$@" -c "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Other Targets
clean:
	-$(RM) *.o $(TARGET)
	-@echo ' '

.PHONY: all clean dependents
