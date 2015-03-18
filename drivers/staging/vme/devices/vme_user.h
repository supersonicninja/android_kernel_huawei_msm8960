#ifndef _VME_USER_H_
#define _VME_USER_H_

<<<<<<< HEAD
#define USER_BUS_MAX                  1
=======
#define VME_USER_BUS_MAX	1
>>>>>>> cm-10.0

/*
 * VMEbus Master Window Configuration Structure
 */
struct vme_master {
	int enable;			/* State of Window */
	unsigned long long vme_addr;	/* Starting Address on the VMEbus */
	unsigned long long size;	/* Window Size */
<<<<<<< HEAD
	vme_address_t aspace;		/* Address Space */
	vme_cycle_t cycle;		/* Cycle properties */
	vme_width_t dwidth;		/* Maximum Data Width */
=======
	u32 aspace;			/* Address Space */
	u32 cycle;		/* Cycle properties */
	u32 dwidth;		/* Maximum Data Width */
>>>>>>> cm-10.0
#if 0
	char prefetchEnable;		/* Prefetch Read Enable State */
	int prefetchSize;		/* Prefetch Read Size (Cache Lines) */
	char wrPostEnable;		/* Write Post State */
#endif
};


/*
 * IOCTL Commands and structures
 */

/* Magic number for use in ioctls */
#define VME_IOC_MAGIC 0xAE


/* VMEbus Slave Window Configuration Structure */
struct vme_slave {
	int enable;			/* State of Window */
	unsigned long long vme_addr;	/* Starting Address on the VMEbus */
	unsigned long long size;	/* Window Size */
<<<<<<< HEAD
	vme_address_t aspace;		/* Address Space */
	vme_cycle_t cycle;		/* Cycle properties */
=======
	u32 aspace;			/* Address Space */
	u32 cycle;		/* Cycle properties */
>>>>>>> cm-10.0
#if 0
	char wrPostEnable;		/* Write Post State */
	char rmwLock;			/* Lock PCI during RMW Cycles */
	char data64BitCapable;		/* non-VMEbus capable of 64-bit Data */
#endif
};

<<<<<<< HEAD
=======
struct vme_irq_id {
	__u8 level;
	__u8 statid;
};

>>>>>>> cm-10.0
#define VME_GET_SLAVE _IOR(VME_IOC_MAGIC, 1, struct vme_slave)
#define VME_SET_SLAVE _IOW(VME_IOC_MAGIC, 2, struct vme_slave)
#define VME_GET_MASTER _IOR(VME_IOC_MAGIC, 3, struct vme_master)
#define VME_SET_MASTER _IOW(VME_IOC_MAGIC, 4, struct vme_master)
<<<<<<< HEAD
=======
#define VME_IRQ_GEN _IOW(VME_IOC_MAGIC, 5, struct vme_irq_id)
>>>>>>> cm-10.0

#endif /* _VME_USER_H_ */

