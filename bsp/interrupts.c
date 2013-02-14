/*
 * bsp.c
 *
 *  Created on: Jan 12, 2013
 *      Author: jonathanhendrix
 */

#include "interrupts.h"
#include "bar.h"

typedef enum {
	IRQ_BASIC = IRQ_BAR,
	IRQ_PEND1 = IRQ_BAR + 0x04,
	IRQ_PEND2 = IRQ_BAR + 0x08,
	IRQ_FIQ_CONTROL = IRQ_BAR + 0x0C,
	IRQ_ENABLE_IRQS1 = IRQ_BAR + 0x10,
	IRQ_ENABLE_IRQS2 = IRQ_BAR + 0x14,
	IRQ_ENABLE_BASIC = IRQ_BAR + 0x18,
	IRQ_DISABLE_IRQS1 = IRQ_BAR + 0x1C,
	IRQ_DISABLE_IRQS2 = IRQ_BAR + 0x20,
	IRQ_DISABLE_BASIC = IRQ_BAR + 0x24
} irq_bar_t;

void select_fiq_interrupt_source(irq_source_t i) {  // @TODO ??????
	if (i == IRQ_NONE) {
		*(unsigned int*) (IRQ_FIQ_CONTROL) = 0;
	} else if (i <= IRQ_ILLEGAL_ACCESS_TYPE0) {
		enum {
			FIQ_ENABLE = 1 << 7
		};
		*(unsigned int*) (IRQ_FIQ_CONTROL) = i + FIQ_ENABLE;
	}
}

void enable_basic_interrupt(irq_source_t i) {
	if (i <= IRQ_ILLEGAL_ACCESS_TYPE0) {
		*(unsigned int*) (IRQ_ENABLE_BASIC) = i;
	}
}

void disable_basic_interrupt(irq_source_t i) {
	if (i <= IRQ_ILLEGAL_ACCESS_TYPE0) {
		*(unsigned int*) (IRQ_ENABLE_BASIC) = i;
	}
}

int is_interrupt_pending(irq_source_t i)  {
	return ((*(unsigned int*) (IRQ_BASIC) & i) > 0);
}
