/*
 * interrupts.h
 *
 *  Created on: Jan 13, 2013
 *      Author: jonathanhendrix
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "bsp.h"

typedef enum {
	IRQ_NONE = 0,
	IRQ_ARM_TIMER = 0x000001,
	IRQ_ARM_MAILBOX = 0x000002,
	IRQ_ARM_DOORBELL0 = 0x000004,
	IRQ_ARM_DOORBELL1 = 0x000008,
	IRQ_GPU0_HALTED = 0x000010,
	IRQ_GPU1_HALTED = 0x000020,
	IRQ_ILLEGAL_ACCESS_TYPE1 = 0x000040,
	IRQ_ILLEGAL_ACCESS_TYPE0 = 0x000080,
	IRQ_REG1_PENDING = 0x000100,
	IRQ_REG2_PENDING = 0x000200,
	IRQ_GPU_IRQ7 = 0x000400,
	IRQ_GPU_IRQ9 = 0x000800,
	IRQ_GPU_IRQ10 = 0x001000,
	IRQ_GPU_IRQ18 = 0x002000,
	IRQ_GPU_IRQ19 = 0x004000,
	IRQ_GPU_IRQ53 = 0x008000,
	IRQ_GPU_IRQ54 = 0x010000,
	IRQ_GPU_IRQ55 = 0x020000,
	IRQ_GPU_IRQ56 = 0x040000,
	IRQ_GPU_IRQ57 = 0x080000,
	IRQ_GPU_IRQ62 = 0x100000
} irq_source_t;


#ifdef __cplusplus
extern "C" {
#endif

void select_fiq_interrupt_source(irq_source_t i);

void enable_basic_interrupt(irq_source_t i);

void disable_basic_interrupt(irq_source_t i);

int is_interrupt_pending(irq_source_t i);

#ifdef __cplusplus
}
#endif



#endif /* INTERRUPTS_H_ */
