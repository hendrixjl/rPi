include Makefile.rules

TARGET := crawler

LIBS := 

INCLUDES = -Ibare_metal -Ibsp -Iexternal_devices

DIRS := bsp #bare_metal 

OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
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
	cd $$d; $(RM) *.o; \
	done
	-$(RM) *.o $(TARGET)
	-@echo ' '

DI:
	for d in $(DIRS); do \
	cd $$d; make; \
	done

.PHONY: all clean dependents
