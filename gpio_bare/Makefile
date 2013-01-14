
SUBDIRS := \
. \
bsp \

RM := rm -rf

# All of the sources participating in the build are defined here
-include subdir.mk
-include bsp/subdir.mk

LIBS := -lgcc


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: gpio_bare

# Tool invocations
gpio_bare: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	arm-none-eabi-g++ -nostartfiles -nodefaultlibs -nostdlib -ffreestanding -T memmap -o "gpio_bare" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(EXECUTABLES) gpio_bare
	-@echo ' '

post-build:
	-arm-none-eabi-objdump -D gpio_bare > gpio_bare.list; arm-none-eabi-objcopy gpio_bare -O binary /tmp/gpio_bare.bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

