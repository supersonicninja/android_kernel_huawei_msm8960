/*
 * interface to Blackfin CEC
 *
 * Copyright 2009 Analog Devices Inc.
 * Licensed under the GPL-2 or later.
 */

#ifndef __ASM_BFIN_IRQFLAGS_H__
#define __ASM_BFIN_IRQFLAGS_H__

#include <mach/blackfin.h>

#ifdef CONFIG_SMP
# include <asm/pda.h>
# include <asm/processor.h>
# define bfin_irq_flags cpu_pda[blackfin_core_id()].imask
#else
extern unsigned long bfin_irq_flags;
#endif

<<<<<<< HEAD
static inline void bfin_sti(unsigned long flags)
=======
static inline notrace void bfin_sti(unsigned long flags)
>>>>>>> cm-10.0
{
	asm volatile("sti %0;" : : "d" (flags));
}

<<<<<<< HEAD
static inline unsigned long bfin_cli(void)
=======
static inline notrace unsigned long bfin_cli(void)
>>>>>>> cm-10.0
{
	unsigned long flags;
	asm volatile("cli %0;" : "=d" (flags));
	return flags;
}

#ifdef CONFIG_DEBUG_HWERR
# define bfin_no_irqs 0x3f
#else
# define bfin_no_irqs 0x1f
#endif

/*****************************************************************************/
/*
 * Hard, untraced CPU interrupt flag manipulation and access.
 */
<<<<<<< HEAD
static inline void __hard_local_irq_disable(void)
=======
static inline notrace void __hard_local_irq_disable(void)
>>>>>>> cm-10.0
{
	bfin_cli();
}

<<<<<<< HEAD
static inline void __hard_local_irq_enable(void)
=======
static inline notrace void __hard_local_irq_enable(void)
>>>>>>> cm-10.0
{
	bfin_sti(bfin_irq_flags);
}

<<<<<<< HEAD
static inline unsigned long hard_local_save_flags(void)
=======
static inline notrace unsigned long hard_local_save_flags(void)
>>>>>>> cm-10.0
{
	return bfin_read_IMASK();
}

<<<<<<< HEAD
static inline unsigned long __hard_local_irq_save(void)
=======
static inline notrace unsigned long __hard_local_irq_save(void)
>>>>>>> cm-10.0
{
	unsigned long flags;
	flags = bfin_cli();
#ifdef CONFIG_DEBUG_HWERR
	bfin_sti(0x3f);
#endif
	return flags;
}

<<<<<<< HEAD
static inline int hard_irqs_disabled_flags(unsigned long flags)
=======
static inline notrace int hard_irqs_disabled_flags(unsigned long flags)
>>>>>>> cm-10.0
{
	return (flags & ~0x3f) == 0;
}

<<<<<<< HEAD
static inline int hard_irqs_disabled(void)
=======
static inline notrace int hard_irqs_disabled(void)
>>>>>>> cm-10.0
{
	unsigned long flags = hard_local_save_flags();
	return hard_irqs_disabled_flags(flags);
}

<<<<<<< HEAD
static inline void __hard_local_irq_restore(unsigned long flags)
=======
static inline notrace void __hard_local_irq_restore(unsigned long flags)
>>>>>>> cm-10.0
{
	if (!hard_irqs_disabled_flags(flags))
		__hard_local_irq_enable();
}

/*****************************************************************************/
/*
 * Interrupt pipe handling.
 */
#ifdef CONFIG_IPIPE

#include <linux/compiler.h>
#include <linux/ipipe_trace.h>
/*
 * Way too many inter-deps between low-level headers in this port, so
 * we redeclare the required bits we cannot pick from
 * <asm/ipipe_base.h> to prevent circular dependencies.
 */
void __ipipe_stall_root(void);
void __ipipe_unstall_root(void);
unsigned long __ipipe_test_root(void);
unsigned long __ipipe_test_and_stall_root(void);
void __ipipe_restore_root(unsigned long flags);

#ifdef CONFIG_IPIPE_DEBUG_CONTEXT
struct ipipe_domain;
extern struct ipipe_domain ipipe_root;
void ipipe_check_context(struct ipipe_domain *ipd);
#define __check_irqop_context(ipd)  ipipe_check_context(&ipipe_root)
#else /* !CONFIG_IPIPE_DEBUG_CONTEXT */
#define __check_irqop_context(ipd)  do { } while (0)
#endif /* !CONFIG_IPIPE_DEBUG_CONTEXT */

/*
 * Interrupt pipe interface to linux/irqflags.h.
 */
<<<<<<< HEAD
static inline void arch_local_irq_disable(void)
=======
static inline notrace void arch_local_irq_disable(void)
>>>>>>> cm-10.0
{
	__check_irqop_context();
	__ipipe_stall_root();
	barrier();
}

<<<<<<< HEAD
static inline void arch_local_irq_enable(void)
=======
static inline notrace void arch_local_irq_enable(void)
>>>>>>> cm-10.0
{
	barrier();
	__check_irqop_context();
	__ipipe_unstall_root();
}

<<<<<<< HEAD
static inline unsigned long arch_local_save_flags(void)
=======
static inline notrace unsigned long arch_local_save_flags(void)
>>>>>>> cm-10.0
{
	return __ipipe_test_root() ? bfin_no_irqs : bfin_irq_flags;
}

<<<<<<< HEAD
static inline int arch_irqs_disabled_flags(unsigned long flags)
=======
static inline notrace int arch_irqs_disabled_flags(unsigned long flags)
>>>>>>> cm-10.0
{
	return flags == bfin_no_irqs;
}

<<<<<<< HEAD
static inline unsigned long arch_local_irq_save(void)
=======
static inline notrace unsigned long arch_local_irq_save(void)
>>>>>>> cm-10.0
{
	unsigned long flags;

	__check_irqop_context();
	flags = __ipipe_test_and_stall_root() ? bfin_no_irqs : bfin_irq_flags;
	barrier();

	return flags;
}

<<<<<<< HEAD
static inline void arch_local_irq_restore(unsigned long flags)
=======
static inline notrace void arch_local_irq_restore(unsigned long flags)
>>>>>>> cm-10.0
{
	__check_irqop_context();
	__ipipe_restore_root(flags == bfin_no_irqs);
}

<<<<<<< HEAD
static inline unsigned long arch_mangle_irq_bits(int virt, unsigned long real)
=======
static inline notrace unsigned long arch_mangle_irq_bits(int virt, unsigned long real)
>>>>>>> cm-10.0
{
	/*
	 * Merge virtual and real interrupt mask bits into a single
	 * 32bit word.
	 */
	return (real & ~(1 << 31)) | ((virt != 0) << 31);
}

<<<<<<< HEAD
static inline int arch_demangle_irq_bits(unsigned long *x)
=======
static inline notrace int arch_demangle_irq_bits(unsigned long *x)
>>>>>>> cm-10.0
{
	int virt = (*x & (1 << 31)) != 0;
	*x &= ~(1L << 31);
	return virt;
}

/*
 * Interface to various arch routines that may be traced.
 */
#ifdef CONFIG_IPIPE_TRACE_IRQSOFF
<<<<<<< HEAD
static inline void hard_local_irq_disable(void)
=======
static inline notrace void hard_local_irq_disable(void)
>>>>>>> cm-10.0
{
	if (!hard_irqs_disabled()) {
		__hard_local_irq_disable();
		ipipe_trace_begin(0x80000000);
	}
}

<<<<<<< HEAD
static inline void hard_local_irq_enable(void)
=======
static inline notrace void hard_local_irq_enable(void)
>>>>>>> cm-10.0
{
	if (hard_irqs_disabled()) {
		ipipe_trace_end(0x80000000);
		__hard_local_irq_enable();
	}
}

<<<<<<< HEAD
static inline unsigned long hard_local_irq_save(void)
=======
static inline notrace unsigned long hard_local_irq_save(void)
>>>>>>> cm-10.0
{
	unsigned long flags = hard_local_save_flags();
	if (!hard_irqs_disabled_flags(flags)) {
		__hard_local_irq_disable();
		ipipe_trace_begin(0x80000001);
	}
	return flags;
}

<<<<<<< HEAD
static inline void hard_local_irq_restore(unsigned long flags)
=======
static inline notrace void hard_local_irq_restore(unsigned long flags)
>>>>>>> cm-10.0
{
	if (!hard_irqs_disabled_flags(flags)) {
		ipipe_trace_end(0x80000001);
		__hard_local_irq_enable();
	}
}

#else /* !CONFIG_IPIPE_TRACE_IRQSOFF */
# define hard_local_irq_disable()	__hard_local_irq_disable()
# define hard_local_irq_enable()	__hard_local_irq_enable()
# define hard_local_irq_save()		__hard_local_irq_save()
# define hard_local_irq_restore(flags)	__hard_local_irq_restore(flags)
#endif /* !CONFIG_IPIPE_TRACE_IRQSOFF */

#define hard_local_irq_save_cond()		hard_local_irq_save()
#define hard_local_irq_restore_cond(flags)	hard_local_irq_restore(flags)

#else /* !CONFIG_IPIPE */

/*
 * Direct interface to linux/irqflags.h.
 */
#define arch_local_save_flags()		hard_local_save_flags()
#define arch_local_irq_save(flags)	__hard_local_irq_save()
#define arch_local_irq_restore(flags)	__hard_local_irq_restore(flags)
#define arch_local_irq_enable()		__hard_local_irq_enable()
#define arch_local_irq_disable()	__hard_local_irq_disable()
#define arch_irqs_disabled_flags(flags)	hard_irqs_disabled_flags(flags)
#define arch_irqs_disabled()		hard_irqs_disabled()

/*
 * Interface to various arch routines that may be traced.
 */
#define hard_local_irq_save()		__hard_local_irq_save()
#define hard_local_irq_restore(flags)	__hard_local_irq_restore(flags)
#define hard_local_irq_enable()		__hard_local_irq_enable()
#define hard_local_irq_disable()	__hard_local_irq_disable()
#define hard_local_irq_save_cond()		hard_local_save_flags()
#define hard_local_irq_restore_cond(flags)	do { (void)(flags); } while (0)

#endif /* !CONFIG_IPIPE */

#ifdef CONFIG_SMP
#define hard_local_irq_save_smp()		hard_local_irq_save()
#define hard_local_irq_restore_smp(flags)	hard_local_irq_restore(flags)
#else
#define hard_local_irq_save_smp()		hard_local_save_flags()
#define hard_local_irq_restore_smp(flags)	do { (void)(flags); } while (0)
#endif

/*
 * Remap the arch-neutral IRQ state manipulation macros to the
 * blackfin-specific hard_local_irq_* API.
 */
#define local_irq_save_hw(flags)			\
	do {						\
		(flags) = hard_local_irq_save();	\
	} while (0)
#define local_irq_restore_hw(flags)		\
	do {					\
		hard_local_irq_restore(flags);	\
	} while (0)
#define local_irq_disable_hw()			\
	do {					\
		hard_local_irq_disable();	\
	} while (0)
#define local_irq_enable_hw()			\
	do {					\
		hard_local_irq_enable();	\
	} while (0)
#define local_irq_save_hw_notrace(flags)		\
	do {						\
		(flags) = __hard_local_irq_save();	\
	} while (0)
#define local_irq_restore_hw_notrace(flags)		\
	do {						\
		__hard_local_irq_restore(flags);	\
	} while (0)

#define irqs_disabled_hw()	hard_irqs_disabled()

#endif
