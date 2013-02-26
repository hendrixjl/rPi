TOPDIR := $(PWD)

include Makefile.rules

TARGET := crawler

ifdef __BARE_METAL__
DIRS += bare_metal 
LIBS += -Lbare_metal -lbare_metal
LFLAGS += -nostartfiles -nodefaultlibs -nostdlib
else
DIRS += linux
LIBS += -Llinux -llinux
endif

LIBS += -Lbsp -lbsp -Lutils -lutils

INCLUDES += -Ibare_metal -Ibsp -Iexternal_devices -Iutils

DIRS := bsp utils


#OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
#OBJS += $(patsubst %.c, %.o, $(shell ls *.c))
#OBJS += $(patsubst %.S, %.o, $(shell ls *.S))


# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): DI $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC'
	$(LD)  -o $(TARGET) $(LFLAGS) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	for d in $(DIRS); do \
	cd $$d; make clean; cd $(TOPDIR); \
	done
	-$(RM) *.o $(TARGET)
	-@echo ' '

DI:
	for d in $(DIRS); do \
	cd $$d; make TOPDIR="$(TOPDIR)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)"; cd $(TOPDIR); \
	done

.PHONY: all clean dependents
