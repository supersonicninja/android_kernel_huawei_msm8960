/*
<<<<<<< HEAD
 * linux/arch/m68k/amiga/amiints.c -- Amiga Linux interrupt handling code
=======
 * Amiga Linux interrupt handling code
>>>>>>> cm-10.0
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
<<<<<<< HEAD
 *
 * 11/07/96: rewritten interrupt handling, irq lists are exists now only for
 *           this sources where it makes sense (VERTB/PORTS/EXTER) and you must
 *           be careful that dev_id for this sources is unique since this the
 *           only possibility to distinguish between different handlers for
 *           free_irq. irq lists also have different irq flags:
 *           - IRQ_FLG_FAST: handler is inserted at top of list (after other
 *                           fast handlers)
 *           - IRQ_FLG_SLOW: handler is inserted at bottom of list and before
 *                           they're executed irq level is set to the previous
 *                           one, but handlers don't need to be reentrant, if
 *                           reentrance occurred, slow handlers will be just
 *                           called again.
 *           The whole interrupt handling for CIAs is moved to cia.c
 *           /Roman Zippel
 *
 * 07/08/99: rewamp of the interrupt handling - we now have two types of
 *           interrupts, normal and fast handlers, fast handlers being
 *           marked with IRQF_DISABLED and runs with all other interrupts
 *           disabled. Normal interrupts disable their own source but
 *           run with all other interrupt sources enabled.
 *           PORTS and EXTER interrupts are always shared even if the
 *           drivers do not explicitly mark this when calling
 *           request_irq which they really should do.
 *           This is similar to the way interrupts are handled on all
 *           other architectures and makes a ton of sense besides
 *           having the advantage of making it easier to share
 *           drivers.
 *           /Jes
=======
>>>>>>> cm-10.0
 */

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/errno.h>
<<<<<<< HEAD
=======
#include <linux/irq.h>
>>>>>>> cm-10.0

#include <asm/irq.h>
#include <asm/traps.h>
#include <asm/amigahw.h>
#include <asm/amigaints.h>
#include <asm/amipcmcia.h>

<<<<<<< HEAD
static void amiga_enable_irq(unsigned int irq);
static void amiga_disable_irq(unsigned int irq);
static irqreturn_t ami_int1(int irq, void *dev_id);
static irqreturn_t ami_int3(int irq, void *dev_id);
static irqreturn_t ami_int4(int irq, void *dev_id);
static irqreturn_t ami_int5(int irq, void *dev_id);

static struct irq_controller amiga_irq_controller = {
	.name		= "amiga",
	.lock		= __SPIN_LOCK_UNLOCKED(amiga_irq_controller.lock),
	.enable		= amiga_enable_irq,
	.disable	= amiga_disable_irq,
};

/*
 * void amiga_init_IRQ(void)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function should be called during kernel startup to initialize
 * the amiga IRQ handling routines.
 */

void __init amiga_init_IRQ(void)
{
	if (request_irq(IRQ_AUTO_1, ami_int1, 0, "int1", NULL))
		pr_err("Couldn't register int%d\n", 1);
	if (request_irq(IRQ_AUTO_3, ami_int3, 0, "int3", NULL))
		pr_err("Couldn't register int%d\n", 3);
	if (request_irq(IRQ_AUTO_4, ami_int4, 0, "int4", NULL))
		pr_err("Couldn't register int%d\n", 4);
	if (request_irq(IRQ_AUTO_5, ami_int5, 0, "int5", NULL))
		pr_err("Couldn't register int%d\n", 5);

	m68k_setup_irq_controller(&amiga_irq_controller, IRQ_USER, AMI_STD_IRQS);

	/* turn off PCMCIA interrupts */
	if (AMIGAHW_PRESENT(PCMCIA))
		gayle.inten = GAYLE_IRQ_IDE;

	/* turn off all interrupts and enable the master interrupt bit */
	amiga_custom.intena = 0x7fff;
	amiga_custom.intreq = 0x7fff;
	amiga_custom.intena = IF_SETCLR | IF_INTEN;

	cia_init_IRQ(&ciaa_base);
	cia_init_IRQ(&ciab_base);
}
=======
>>>>>>> cm-10.0

/*
 * Enable/disable a particular machine specific interrupt source.
 * Note that this may affect other interrupts in case of a shared interrupt.
 * This function should only be called for a _very_ short time to change some
 * internal data, that may not be changed by the interrupt at the same time.
 */

<<<<<<< HEAD
static void amiga_enable_irq(unsigned int irq)
{
	amiga_custom.intena = IF_SETCLR | (1 << (irq - IRQ_USER));
}

static void amiga_disable_irq(unsigned int irq)
{
	amiga_custom.intena = 1 << (irq - IRQ_USER);
}

=======
static void amiga_irq_enable(struct irq_data *data)
{
	amiga_custom.intena = IF_SETCLR | (1 << (data->irq - IRQ_USER));
}

static void amiga_irq_disable(struct irq_data *data)
{
	amiga_custom.intena = 1 << (data->irq - IRQ_USER);
}

static struct irq_chip amiga_irq_chip = {
	.name		= "amiga",
	.irq_enable	= amiga_irq_enable,
	.irq_disable	= amiga_irq_disable,
};


>>>>>>> cm-10.0
/*
 * The builtin Amiga hardware interrupt handlers.
 */

<<<<<<< HEAD
static irqreturn_t ami_int1(int irq, void *dev_id)
=======
static void ami_int1(unsigned int irq, struct irq_desc *desc)
>>>>>>> cm-10.0
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if serial transmit buffer empty, interrupt */
	if (ints & IF_TBE) {
		amiga_custom.intreq = IF_TBE;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_TBE);
=======
		generic_handle_irq(IRQ_AMIGA_TBE);
>>>>>>> cm-10.0
	}

	/* if floppy disk transfer complete, interrupt */
	if (ints & IF_DSKBLK) {
		amiga_custom.intreq = IF_DSKBLK;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_DSKBLK);
=======
		generic_handle_irq(IRQ_AMIGA_DSKBLK);
>>>>>>> cm-10.0
	}

	/* if software interrupt set, interrupt */
	if (ints & IF_SOFT) {
		amiga_custom.intreq = IF_SOFT;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_SOFT);
	}
	return IRQ_HANDLED;
}

static irqreturn_t ami_int3(int irq, void *dev_id)
=======
		generic_handle_irq(IRQ_AMIGA_SOFT);
	}
}

static void ami_int3(unsigned int irq, struct irq_desc *desc)
>>>>>>> cm-10.0
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if a blitter interrupt */
	if (ints & IF_BLIT) {
		amiga_custom.intreq = IF_BLIT;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_BLIT);
=======
		generic_handle_irq(IRQ_AMIGA_BLIT);
>>>>>>> cm-10.0
	}

	/* if a copper interrupt */
	if (ints & IF_COPER) {
		amiga_custom.intreq = IF_COPER;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_COPPER);
=======
		generic_handle_irq(IRQ_AMIGA_COPPER);
>>>>>>> cm-10.0
	}

	/* if a vertical blank interrupt */
	if (ints & IF_VERTB) {
		amiga_custom.intreq = IF_VERTB;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_VERTB);
	}
	return IRQ_HANDLED;
}

static irqreturn_t ami_int4(int irq, void *dev_id)
=======
		generic_handle_irq(IRQ_AMIGA_VERTB);
	}
}

static void ami_int4(unsigned int irq, struct irq_desc *desc)
>>>>>>> cm-10.0
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if audio 0 interrupt */
	if (ints & IF_AUD0) {
		amiga_custom.intreq = IF_AUD0;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_AUD0);
=======
		generic_handle_irq(IRQ_AMIGA_AUD0);
>>>>>>> cm-10.0
	}

	/* if audio 1 interrupt */
	if (ints & IF_AUD1) {
		amiga_custom.intreq = IF_AUD1;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_AUD1);
=======
		generic_handle_irq(IRQ_AMIGA_AUD1);
>>>>>>> cm-10.0
	}

	/* if audio 2 interrupt */
	if (ints & IF_AUD2) {
		amiga_custom.intreq = IF_AUD2;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_AUD2);
=======
		generic_handle_irq(IRQ_AMIGA_AUD2);
>>>>>>> cm-10.0
	}

	/* if audio 3 interrupt */
	if (ints & IF_AUD3) {
		amiga_custom.intreq = IF_AUD3;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_AUD3);
	}
	return IRQ_HANDLED;
}

static irqreturn_t ami_int5(int irq, void *dev_id)
=======
		generic_handle_irq(IRQ_AMIGA_AUD3);
	}
}

static void ami_int5(unsigned int irq, struct irq_desc *desc)
>>>>>>> cm-10.0
{
	unsigned short ints = amiga_custom.intreqr & amiga_custom.intenar;

	/* if serial receive buffer full interrupt */
	if (ints & IF_RBF) {
		/* acknowledge of IF_RBF must be done by the serial interrupt */
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_RBF);
=======
		generic_handle_irq(IRQ_AMIGA_RBF);
>>>>>>> cm-10.0
	}

	/* if a disk sync interrupt */
	if (ints & IF_DSKSYN) {
		amiga_custom.intreq = IF_DSKSYN;
<<<<<<< HEAD
		m68k_handle_int(IRQ_AMIGA_DSKSYN);
	}
	return IRQ_HANDLED;
=======
		generic_handle_irq(IRQ_AMIGA_DSKSYN);
	}
}


/*
 * void amiga_init_IRQ(void)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function should be called during kernel startup to initialize
 * the amiga IRQ handling routines.
 */

void __init amiga_init_IRQ(void)
{
	m68k_setup_irq_controller(&amiga_irq_chip, handle_simple_irq, IRQ_USER,
				  AMI_STD_IRQS);

	irq_set_chained_handler(IRQ_AUTO_1, ami_int1);
	irq_set_chained_handler(IRQ_AUTO_3, ami_int3);
	irq_set_chained_handler(IRQ_AUTO_4, ami_int4);
	irq_set_chained_handler(IRQ_AUTO_5, ami_int5);

	/* turn off PCMCIA interrupts */
	if (AMIGAHW_PRESENT(PCMCIA))
		gayle.inten = GAYLE_IRQ_IDE;

	/* turn off all interrupts and enable the master interrupt bit */
	amiga_custom.intena = 0x7fff;
	amiga_custom.intreq = 0x7fff;
	amiga_custom.intena = IF_SETCLR | IF_INTEN;

	cia_init_IRQ(&ciaa_base);
	cia_init_IRQ(&ciab_base);
>>>>>>> cm-10.0
}
