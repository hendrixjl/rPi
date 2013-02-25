
TOPDIR := $(PWD)

include Makefile.rules

TARGET := crawler

LIBS := -Lbsp -lbsp -Lutils -lutils

INCLUDES = -Ibare_metal -Ibsp -Iexternal_devices -Iutils

DIRS := bsp utils

ifdef __BARE_METAL__
DIRS += bare_metal 
LIBS += -Lbare_metal
else
DIRS += linux
endif


#OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
#OBJS += $(patsubst %.c, %.o, $(shell ls *.c))
#OBJS += $(patsubst %.S, %.o, $(shell ls *.S))


# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): DI $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC'
	$(LD)  -o $(TARGET) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	for d in $(DIRS); do \
	cd $$d; make clean; \
	done
	-$(RM) *.o $(TARGET)
	-@echo ' '

DI:
	for d in $(DIRS); do \
	cd $$d; make TOPDIR="$(TOPDIR)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)"; \
	done

.PHONY: all clean dependents
