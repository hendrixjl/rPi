/*
 * interrupt.h
 *
 *  Created on: Nov 24, 2012
 *      Author: jonathanhendrix
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


class bsp_irq_t
{
private:
	enum {
		BAR = 0x2000B200,
		IRQ_BASIC = BAR,
		IRQ_PEND1 = BAR + 0x04,
		IRQ_PEND2 = BAR + 0x08,
		IRQ_FIQ_CONTROL = BAR + 0x0C,
		IRQ_ENABLE_IRQS1 = BAR + 0x10,
		IRQ_ENABLE_IRQS2 = BAR + 0x14,
		IRQ_ENABLE_BASIC = BAR + 0x18,
		IRQ_DISABLE_IRQS1 = BAR + 0x1C,
		IRQ_DISABLE_IRQS2 = BAR + 0x20,
		IRQ_DISABLE_BASIC = BAR + 0x24
	};
public:
	enum irq_type {
		IRQ_NONE = 0,
		ARM_TIMER =            0x000001,
		ARM_MAILBOX =          0x000002,
		ARM_DOORBELL0 =        0x000004,
		ARM_DOORBELL1 =        0x000008,
		GPU0_HALTED =          0x000010,
		GPU1_HALTED =          0x000020,
		ILLEGAL_ACCESS_TYPE1 = 0x000040,
		ILLEGAL_ACCESS_TYPE0 = 0x000080,
		REG1_PENDING =         0x000100,
		REG2_PENDING =         0x000200,
		GPU_IRQ7 =             0x000400,
		GPU_IRQ9 =             0x000800,
		GPU_IRQ10 =            0x001000,
		GPU_IRQ18 =            0x002000,
		GPU_IRQ19 =            0x004000,
		GPU_IRQ53 =            0x008000,
		GPU_IRQ54 =            0x010000,
		GPU_IRQ55 =            0x020000,
		GPU_IRQ56 =            0x040000,
		GPU_IRQ57 =            0x080000,
		GPU_IRQ62 =            0x100000
	};

    static void select_fiq_interrupt_source(irq_type i) {  // @TODO ??????
    	if (i == IRQ_NONE) {
        	*reinterpret_cast<unsigned int*>(IRQ_FIQ_CONTROL) = 0;
    	}
    	else if (i <= ILLEGAL_ACCESS_TYPE0)
    	{
    		enum { FIQ_ENABLE = 1<<7 };
    	    *reinterpret_cast<unsigned int*>(IRQ_FIQ_CONTROL) = i + FIQ_ENABLE;
    	}
    }

    static void enable_basic_interrupt(irq_type i) {
    	if (i <= ILLEGAL_ACCESS_TYPE0) {
    		*reinterpret_cast<unsigned int*>(IRQ_ENABLE_BASIC) = i;
    	}
    }

    static void disable_basic_interrupt(irq_type i) {
    	if (i <= ILLEGAL_ACCESS_TYPE0) {
    		*reinterpret_cast<unsigned int*>(IRQ_ENABLE_BASIC) = i;
    	}
    }

    static bool is_interrupt_pending(irq_type i) {
    	return (*reinterpret_cast<unsigned int*>(IRQ_BASIC) & i);
    }
};

#endif /* INTERRUPT_H_ */
