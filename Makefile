TOPDIR := $(PWD)

include Makefile.rules

TARGET := crawler

ifdef __BARE_METAL__
DIRS += bare_metal 
LIBS += -Lbare_metal -lbare_metal
LFLAGS += -nostartfiles -nodefaultlibs -nostdlib -T bare_metal/memmap
else
DIRS += linux
LIBS += -Llinux -llinux -lrt
endif

LIBS += -Lbsp -lbsp -Lexternal_devices -lexternal_devices -Lutils -lutils 

# Needed to resolve linking problems
ifdef __BARE_METAL__
LIBS += -lbare_metal -lgcc -lbsp
endif

DIRS += bsp utils external_devices


OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
#OBJS += $(patsubst %.c, %.o, $(shell ls *.c))
#OBJS += $(patsubst %.S, %.o, $(shell ls *.S))

# Force inclusion of bootstrap code
ifdef __BARE_METAL__
OBJS += bare_metal/bootstrap.o
endif


# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): DI $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
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
