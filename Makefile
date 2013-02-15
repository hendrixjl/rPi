include "Makefile.rules"

TARGET := crawler

LIBS := 

INCLUDES = bare_metal bsp external_devices

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
	-$(RM) *.o $(TARGET)
	-@echo ' '

bare_metal:
	cd "$@"; make

bsp:
	cd "$@"; make

.PHONY: all clean dependents
