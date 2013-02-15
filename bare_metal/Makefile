include "Makefile.rules"

RM := rm -rf

LIBS := 

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

# Other Targets
clean:
	-$(RM) *.o 
	-@echo ' '

.PHONY: all clean dependents
