include ../Makefile.rules

RM := rm -rf

LIBS := 


OBJS += $(patsubst %.cpp, %.o, $(shell ls *.cpp))
OBJS += $(patsubst %.c, %.o, $(shell ls *.c))
OBJS += $(patsubst %.S, %.o, $(shell ls *.S))

TARGET = libbare_metal.a

all : $(TARGET)


$(TARGET) : $(OBJS)
	$(AR) rcs $(TARGET) $(OBJS)

clean:
	-$(RM) *.o $(TARGET)
	
.PHONY: clean all

