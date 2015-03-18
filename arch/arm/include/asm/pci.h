#ifndef ASMARM_PCI_H
#define ASMARM_PCI_H

#ifdef __KERNEL__
#include <asm-generic/pci-dma-compat.h>
<<<<<<< HEAD

#include <asm/mach/pci.h> /* for pci_sys_data */
#include <mach/hardware.h> /* for PCIBIOS_MIN_* */
=======
#include <asm-generic/pci-bridge.h>

#include <asm/mach/pci.h> /* for pci_sys_data */

extern unsigned long pcibios_min_io;
#define PCIBIOS_MIN_IO pcibios_min_io
extern unsigned long pcibios_min_mem;
#define PCIBIOS_MIN_MEM pcibios_min_mem

static inline int pcibios_assign_all_busses(void)
{
	return pci_has_flag(PCI_REASSIGN_ALL_RSRC);
}
>>>>>>> cm-10.0

#ifdef CONFIG_PCI_DOMAINS
static inline int pci_domain_nr(struct pci_bus *bus)
{
	struct pci_sys_data *root = bus->sysdata;

	return root->domain;
}

static inline int pci_proc_domain(struct pci_bus *bus)
{
	return pci_domain_nr(bus);
}
#endif /* CONFIG_PCI_DOMAINS */

<<<<<<< HEAD
#ifdef CONFIG_PCI_HOST_ITE8152
/* ITE bridge requires setting latency timer to avoid early bus access
   termination by PIC bus mater devices
*/
extern void pcibios_set_master(struct pci_dev *dev);
#else
static inline void pcibios_set_master(struct pci_dev *dev)
{
	/* No special bus mastering setup handling */
}
#endif

=======
>>>>>>> cm-10.0
static inline void pcibios_penalize_isa_irq(int irq, int active)
{
	/* We don't do dynamic PCI IRQ allocation */
}

/*
 * The PCI address space does equal the physical memory address space.
 * The networking and block device layers use this boolean for bounce
 * buffer decisions.
 */
#define PCI_DMA_BUS_IS_PHYS     (1)

#ifdef CONFIG_PCI
static inline void pci_dma_burst_advice(struct pci_dev *pdev,
					enum pci_dma_burst_strategy *strat,
					unsigned long *strategy_parameter)
{
	*strat = PCI_DMA_BURST_INFINITY;
	*strategy_parameter = ~0UL;
}
#endif

#define HAVE_PCI_MMAP
extern int pci_mmap_page_range(struct pci_dev *dev, struct vm_area_struct *vma,
                               enum pci_mmap_state mmap_state, int write_combine);

<<<<<<< HEAD
extern void
pcibios_resource_to_bus(struct pci_dev *dev, struct pci_bus_region *region,
			 struct resource *res);

extern void
pcibios_bus_to_resource(struct pci_dev *dev, struct resource *res,
			struct pci_bus_region *region);

=======
>>>>>>> cm-10.0
/*
 * Dummy implementation; always return 0.
 */
static inline int pci_get_legacy_ide_irq(struct pci_dev *dev, int channel)
{
	return 0;
}

#endif /* __KERNEL__ */
 
#endif
