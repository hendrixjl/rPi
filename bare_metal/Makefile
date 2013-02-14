RM := rm -rf


LIBS := 

ifdef __BARE_METAL__
PREFIX := arm-none-eabi-
endif

CPP := $(PREFIX)g++
CC := $(PREFIX)gcc
AS := $(PREFIX)g++
AR := $(PREFIX)ar

CPPOPTS := -std=c++0x -O0 -g3 -Wall -fmessage-length=0

DIRS := bsp bare_metal 

OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
OBJS += $(patsubst %.c, %.o, $(shell ls *.c))
OBJS += $(patsubst %.S, %.o, $(shell ls *.S))

# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): $(DIRS) $(OBJS) 
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

%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(CC) $(COPTS)  -o "$@" -c "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: %.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	$(AS) $(AOPTS)  -o "$@" -c "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Other Targets
clean:
	-$(RM) *.o 
	-@echo ' '

.PHONY: all clean dependents
