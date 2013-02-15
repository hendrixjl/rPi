include "Makefile.rules"

RM := rm -rf

LIBS := 

DIRS := bsp bare_metal 

OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
OBJS += $(patsubst %.c, %.o, $(shell ls *.c))
OBJS += $(patsubst %.S, %.o, $(shell ls *.S))


# Other Targets
clean:
	-$(RM) *.o 
	-@echo ' '

.PHONY: all clean
