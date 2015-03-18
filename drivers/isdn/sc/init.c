/*
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include "includes.h"
#include "hardware.h"
#include "card.h"

MODULE_DESCRIPTION("ISDN4Linux: Driver for Spellcaster card");
MODULE_AUTHOR("Spellcaster Telecommunications Inc.");
MODULE_LICENSE("GPL");

board *sc_adapter[MAX_CARDS];
int cinst;

static char devname[] = "scX";
static const char version[] = "2.0b1";

static const char *boardname[] = { "DataCommute/BRI", "DataCommute/PRI", "TeleCommute/BRI" };

/* insmod set parameters */
<<<<<<< HEAD
static unsigned int io[] = {0,0,0,0};
static unsigned char irq[] = {0,0,0,0};
static unsigned long ram[] = {0,0,0,0};
static int do_reset = 0;
=======
static unsigned int io[] = {0, 0, 0, 0};
static unsigned char irq[] = {0, 0, 0, 0};
static unsigned long ram[] = {0, 0, 0, 0};
static bool do_reset = 0;
>>>>>>> cm-10.0

module_param_array(io, int, NULL, 0);
module_param_array(irq, int, NULL, 0);
module_param_array(ram, int, NULL, 0);
module_param(do_reset, bool, 0);

static int identify_board(unsigned long, unsigned int);

static int __init sc_init(void)
{
	int b = -1;
	int i, j;
	int status = -ENODEV;

	unsigned long memsize = 0;
	unsigned long features = 0;
	isdn_if *interface;
	unsigned char channels;
	unsigned char pgport;
	unsigned long magic;
	int model;
	int last_base = IOBASE_MIN;
	int probe_exhasted = 0;

#ifdef MODULE
	pr_info("SpellCaster ISA ISDN Adapter Driver rev. %s Loaded\n", version);
#else
	pr_info("SpellCaster ISA ISDN Adapter Driver rev. %s\n", version);
#endif
	pr_info("Copyright (C) 1996 SpellCaster Telecommunications Inc.\n");

<<<<<<< HEAD
	while(b++ < MAX_CARDS - 1) {
=======
	while (b++ < MAX_CARDS - 1) {
>>>>>>> cm-10.0
		pr_debug("Probing for adapter #%d\n", b);
		/*
		 * Initialize reusable variables
		 */
		model = -1;
		magic = 0;
		channels = 0;
		pgport = 0;

<<<<<<< HEAD
		/* 
		 * See if we should probe for IO base 
		 */
		pr_debug("I/O Base for board %d is 0x%x, %s probe\n", b, io[b],
			io[b] == 0 ? "will" : "won't");
		if(io[b]) {
			/*
			 * No, I/O Base has been provided
			 */
			for (i = 0 ; i < MAX_IO_REGS - 1 ; i++) {
				if(!request_region(io[b] + i * 0x400, 1, "sc test")) {
=======
		/*
		 * See if we should probe for IO base
		 */
		pr_debug("I/O Base for board %d is 0x%x, %s probe\n", b, io[b],
			 io[b] == 0 ? "will" : "won't");
		if (io[b]) {
			/*
			 * No, I/O Base has been provided
			 */
			for (i = 0; i < MAX_IO_REGS - 1; i++) {
				if (!request_region(io[b] + i * 0x400, 1, "sc test")) {
>>>>>>> cm-10.0
					pr_debug("request_region for 0x%x failed\n", io[b] + i * 0x400);
					io[b] = 0;
					break;
				} else
					release_region(io[b] + i * 0x400, 1);
			}

			/*
			 * Confirm the I/O Address with a test
			 */
<<<<<<< HEAD
			if(io[b] == 0) {
=======
			if (io[b] == 0) {
>>>>>>> cm-10.0
				pr_debug("I/O Address invalid.\n");
				continue;
			}

			outb(0x18, io[b] + 0x400 * EXP_PAGE0);
<<<<<<< HEAD
			if(inb(io[b] + 0x400 * EXP_PAGE0) != 0x18) {
=======
			if (inb(io[b] + 0x400 * EXP_PAGE0) != 0x18) {
>>>>>>> cm-10.0
				pr_debug("I/O Base 0x%x fails test\n",
					 io[b] + 0x400 * EXP_PAGE0);
				continue;
			}
		}
		else {
			/*
			 * Yes, probe for I/O Base
			 */
<<<<<<< HEAD
			if(probe_exhasted) {
=======
			if (probe_exhasted) {
>>>>>>> cm-10.0
				pr_debug("All probe addresses exhasted, skipping\n");
				continue;
			}
			pr_debug("Probing for I/O...\n");
<<<<<<< HEAD
			for (i = last_base ; i <= IOBASE_MAX ; i += IOBASE_OFFSET) {
=======
			for (i = last_base; i <= IOBASE_MAX; i += IOBASE_OFFSET) {
>>>>>>> cm-10.0
				int found_io = 1;
				if (i == IOBASE_MAX) {
					probe_exhasted = 1; /* No more addresses to probe */
					pr_debug("End of Probes\n");
				}
				last_base = i + IOBASE_OFFSET;
				pr_debug("  checking 0x%x...", i);
<<<<<<< HEAD
				for ( j = 0 ; j < MAX_IO_REGS - 1 ; j++) {
					if(!request_region(i + j * 0x400, 1, "sc test")) {
=======
				for (j = 0; j < MAX_IO_REGS - 1; j++) {
					if (!request_region(i + j * 0x400, 1, "sc test")) {
>>>>>>> cm-10.0
						pr_debug("Failed\n");
						found_io = 0;
						break;
					} else
						release_region(i + j * 0x400, 1);
<<<<<<< HEAD
				}	

				if(found_io) {
					io[b] = i;
					outb(0x18, io[b] + 0x400 * EXP_PAGE0);
					if(inb(io[b] + 0x400 * EXP_PAGE0) != 0x18) { 
=======
				}

				if (found_io) {
					io[b] = i;
					outb(0x18, io[b] + 0x400 * EXP_PAGE0);
					if (inb(io[b] + 0x400 * EXP_PAGE0) != 0x18) {
>>>>>>> cm-10.0
						pr_debug("Failed by test\n");
						continue;
					}
					pr_debug("Passed\n");
					break;
				}
			}
<<<<<<< HEAD
			if(probe_exhasted) {
=======
			if (probe_exhasted) {
>>>>>>> cm-10.0
				continue;
			}
		}

		/*
		 * See if we should probe for shared RAM
		 */
<<<<<<< HEAD
		if(do_reset) {
=======
		if (do_reset) {
>>>>>>> cm-10.0
			pr_debug("Doing a SAFE probe reset\n");
			outb(0xFF, io[b] + RESET_OFFSET);
			msleep_interruptible(10000);
		}
		pr_debug("RAM Base for board %d is 0x%lx, %s probe\n", b,
<<<<<<< HEAD
			ram[b], ram[b] == 0 ? "will" : "won't");

		if(ram[b]) {
=======
			 ram[b], ram[b] == 0 ? "will" : "won't");

		if (ram[b]) {
>>>>>>> cm-10.0
			/*
			 * No, the RAM base has been provided
			 * Just look for a signature and ID the
			 * board model
			 */
<<<<<<< HEAD
			if(request_region(ram[b], SRAM_PAGESIZE, "sc test")) {
				pr_debug("request_region for RAM base 0x%lx succeeded\n", ram[b]);
			 	model = identify_board(ram[b], io[b]);
=======
			if (request_region(ram[b], SRAM_PAGESIZE, "sc test")) {
				pr_debug("request_region for RAM base 0x%lx succeeded\n", ram[b]);
				model = identify_board(ram[b], io[b]);
>>>>>>> cm-10.0
				release_region(ram[b], SRAM_PAGESIZE);
			}
		}
		else {
			/*
			 * Yes, probe for free RAM and look for
			 * a signature and id the board model
			 */
<<<<<<< HEAD
			for (i = SRAM_MIN ; i < SRAM_MAX ; i += SRAM_PAGESIZE) {
				pr_debug("Checking RAM address 0x%x...\n", i);
				if(request_region(i, SRAM_PAGESIZE, "sc test")) {
=======
			for (i = SRAM_MIN; i < SRAM_MAX; i += SRAM_PAGESIZE) {
				pr_debug("Checking RAM address 0x%x...\n", i);
				if (request_region(i, SRAM_PAGESIZE, "sc test")) {
>>>>>>> cm-10.0
					pr_debug("  request_region succeeded\n");
					model = identify_board(i, io[b]);
					release_region(i, SRAM_PAGESIZE);
					if (model >= 0) {
						pr_debug("  Identified a %s\n",
<<<<<<< HEAD
							boardname[model]);
=======
							 boardname[model]);
>>>>>>> cm-10.0
						ram[b] = i;
						break;
					}
					pr_debug("  Unidentifed or inaccessible\n");
					continue;
				}
				pr_debug("  request failed\n");
			}
		}
		/*
		 * See if we found free RAM and the board model
		 */
<<<<<<< HEAD
		if(!ram[b] || model < 0) {
=======
		if (!ram[b] || model < 0) {
>>>>>>> cm-10.0
			/*
			 * Nope, there was no place in RAM for the
			 * board, or it couldn't be identified
			 */
<<<<<<< HEAD
			 pr_debug("Failed to find an adapter at 0x%lx\n", ram[b]);
			 continue;
=======
			pr_debug("Failed to find an adapter at 0x%lx\n", ram[b]);
			continue;
>>>>>>> cm-10.0
		}

		/*
		 * Set the board's magic number, memory size and page register
		 */
<<<<<<< HEAD
		switch(model) {
=======
		switch (model) {
>>>>>>> cm-10.0
		case PRI_BOARD:
			channels = 23;
			magic = 0x20000;
			memsize = 0x100000;
			features = PRI_FEATURES;
			break;

		case BRI_BOARD:
		case POTS_BOARD:
			channels = 2;
			magic = 0x60000;
			memsize = 0x10000;
			features = BRI_FEATURES;
			break;
		}
<<<<<<< HEAD
		switch(ram[b] >> 12 & 0x0F) {
=======
		switch (ram[b] >> 12 & 0x0F) {
>>>>>>> cm-10.0
		case 0x0:
			pr_debug("RAM Page register set to EXP_PAGE0\n");
			pgport = EXP_PAGE0;
			break;

		case 0x4:
			pr_debug("RAM Page register set to EXP_PAGE1\n");
			pgport = EXP_PAGE1;
			break;

		case 0x8:
			pr_debug("RAM Page register set to EXP_PAGE2\n");
			pgport = EXP_PAGE2;
			break;

		case 0xC:
			pr_debug("RAM Page register set to EXP_PAGE3\n");
			pgport = EXP_PAGE3;
			break;

		default:
			pr_debug("RAM base address doesn't fall on 16K boundary\n");
			continue;
		}

<<<<<<< HEAD
		pr_debug("current IRQ: %d  b: %d\n",irq[b],b);
=======
		pr_debug("current IRQ: %d  b: %d\n", irq[b], b);
>>>>>>> cm-10.0

		/*
		 * Make sure we got an IRQ
		 */
<<<<<<< HEAD
		if(!irq[b]) {
=======
		if (!irq[b]) {
>>>>>>> cm-10.0
			/*
			 * No interrupt could be used
			 */
			pr_debug("Failed to acquire an IRQ line\n");
			continue;
		}

		/*
		 * Horray! We found a board, Make sure we can register
		 * it with ISDN4Linux
		 */
		interface = kzalloc(sizeof(isdn_if), GFP_KERNEL);
		if (interface == NULL) {
			/*
			 * Oops, can't malloc isdn_if
			 */
			continue;
		}

		interface->owner = THIS_MODULE;
		interface->hl_hdrlen = 0;
		interface->channels = channels;
		interface->maxbufsize = BUFFER_SIZE;
		interface->features = features;
		interface->writebuf_skb = sndpkt;
		interface->writecmd = NULL;
		interface->command = command;
		strcpy(interface->id, devname);
		interface->id[2] = '0' + cinst;

		/*
		 * Allocate the board structure
		 */
		sc_adapter[cinst] = kzalloc(sizeof(board), GFP_KERNEL);
		if (sc_adapter[cinst] == NULL) {
			/*
			 * Oops, can't alloc memory for the board
			 */
			kfree(interface);
			continue;
		}
		spin_lock_init(&sc_adapter[cinst]->lock);

<<<<<<< HEAD
		if(!register_isdn(interface)) {
=======
		if (!register_isdn(interface)) {
>>>>>>> cm-10.0
			/*
			 * Oops, couldn't register for some reason
			 */
			kfree(interface);
			kfree(sc_adapter[cinst]);
			continue;
		}

		sc_adapter[cinst]->card = interface;
		sc_adapter[cinst]->driverId = interface->channels;
		strcpy(sc_adapter[cinst]->devicename, interface->id);
		sc_adapter[cinst]->nChannels = channels;
		sc_adapter[cinst]->ramsize = memsize;
		sc_adapter[cinst]->shmem_magic = magic;
		sc_adapter[cinst]->shmem_pgport = pgport;
		sc_adapter[cinst]->StartOnReset = 1;

		/*
		 * Allocate channels status structures
		 */
		sc_adapter[cinst]->channel = kzalloc(sizeof(bchan) * channels, GFP_KERNEL);
		if (sc_adapter[cinst]->channel == NULL) {
			/*
			 * Oops, can't alloc memory for the channels
			 */
			indicate_status(cinst, ISDN_STAT_UNLOAD, 0, NULL);	/* Fix me */
			kfree(interface);
			kfree(sc_adapter[cinst]);
			continue;
		}

		/*
		 * Lock down the hardware resources
		 */
		sc_adapter[cinst]->interrupt = irq[b];
		if (request_irq(sc_adapter[cinst]->interrupt, interrupt_handler,
				IRQF_DISABLED, interface->id,
				(void *)(unsigned long) cinst))
		{
			kfree(sc_adapter[cinst]->channel);
			indicate_status(cinst, ISDN_STAT_UNLOAD, 0, NULL);	/* Fix me */
			kfree(interface);
			kfree(sc_adapter[cinst]);
			continue;
<<<<<<< HEAD
			
		}
		sc_adapter[cinst]->iobase = io[b];
		for(i = 0 ; i < MAX_IO_REGS - 1 ; i++) {
			sc_adapter[cinst]->ioport[i] = io[b] + i * 0x400;
			request_region(sc_adapter[cinst]->ioport[i], 1,
					interface->id);
			pr_debug("Requesting I/O Port %#x\n",
				sc_adapter[cinst]->ioport[i]);
		}
		sc_adapter[cinst]->ioport[IRQ_SELECT] = io[b] + 0x2;
		request_region(sc_adapter[cinst]->ioport[IRQ_SELECT], 1,
				interface->id);
		pr_debug("Requesting I/O Port %#x\n",
				sc_adapter[cinst]->ioport[IRQ_SELECT]);
		sc_adapter[cinst]->rambase = ram[b];
		request_region(sc_adapter[cinst]->rambase, SRAM_PAGESIZE,
				interface->id);

		pr_info("  %s (%d) - %s %d channels IRQ %d, I/O Base 0x%x, RAM Base 0x%lx\n", 
			sc_adapter[cinst]->devicename,
			sc_adapter[cinst]->driverId,
			boardname[model], channels, irq[b], io[b], ram[b]);
		
=======

		}
		sc_adapter[cinst]->iobase = io[b];
		for (i = 0; i < MAX_IO_REGS - 1; i++) {
			sc_adapter[cinst]->ioport[i] = io[b] + i * 0x400;
			request_region(sc_adapter[cinst]->ioport[i], 1,
				       interface->id);
			pr_debug("Requesting I/O Port %#x\n",
				 sc_adapter[cinst]->ioport[i]);
		}
		sc_adapter[cinst]->ioport[IRQ_SELECT] = io[b] + 0x2;
		request_region(sc_adapter[cinst]->ioport[IRQ_SELECT], 1,
			       interface->id);
		pr_debug("Requesting I/O Port %#x\n",
			 sc_adapter[cinst]->ioport[IRQ_SELECT]);
		sc_adapter[cinst]->rambase = ram[b];
		request_region(sc_adapter[cinst]->rambase, SRAM_PAGESIZE,
			       interface->id);

		pr_info("  %s (%d) - %s %d channels IRQ %d, I/O Base 0x%x, RAM Base 0x%lx\n",
			sc_adapter[cinst]->devicename,
			sc_adapter[cinst]->driverId,
			boardname[model], channels, irq[b], io[b], ram[b]);

>>>>>>> cm-10.0
		/*
		 * reset the adapter to put things in motion
		 */
		reset(cinst);

		cinst++;
		status = 0;
	}
<<<<<<< HEAD
	if (status) 
=======
	if (status)
>>>>>>> cm-10.0
		pr_info("Failed to find any adapters, driver unloaded\n");
	return status;
}

static void __exit sc_exit(void)
{
	int i, j;

<<<<<<< HEAD
	for(i = 0 ; i < cinst ; i++) {
=======
	for (i = 0; i < cinst; i++) {
>>>>>>> cm-10.0
		pr_debug("Cleaning up after adapter %d\n", i);
		/*
		 * kill the timers
		 */
		del_timer(&(sc_adapter[i]->reset_timer));
		del_timer(&(sc_adapter[i]->stat_timer));

		/*
		 * Tell I4L we're toast
		 */
		indicate_status(i, ISDN_STAT_STOP, 0, NULL);
		indicate_status(i, ISDN_STAT_UNLOAD, 0, NULL);

		/*
		 * Release shared RAM
		 */
		release_region(sc_adapter[i]->rambase, SRAM_PAGESIZE);

		/*
		 * Release the IRQ
		 */
		free_irq(sc_adapter[i]->interrupt, NULL);

		/*
		 * Reset for a clean start
		 */
		outb(0xFF, sc_adapter[i]->ioport[SFT_RESET]);

		/*
		 * Release the I/O Port regions
		 */
<<<<<<< HEAD
		for(j = 0 ; j < MAX_IO_REGS - 1; j++) {
			release_region(sc_adapter[i]->ioport[j], 1);
			pr_debug("Releasing I/O Port %#x\n",
				sc_adapter[i]->ioport[j]);
		}
		release_region(sc_adapter[i]->ioport[IRQ_SELECT], 1);
		pr_debug("Releasing I/O Port %#x\n",
			sc_adapter[i]->ioport[IRQ_SELECT]);
=======
		for (j = 0; j < MAX_IO_REGS - 1; j++) {
			release_region(sc_adapter[i]->ioport[j], 1);
			pr_debug("Releasing I/O Port %#x\n",
				 sc_adapter[i]->ioport[j]);
		}
		release_region(sc_adapter[i]->ioport[IRQ_SELECT], 1);
		pr_debug("Releasing I/O Port %#x\n",
			 sc_adapter[i]->ioport[IRQ_SELECT]);
>>>>>>> cm-10.0

		/*
		 * Release any memory we alloced
		 */
		kfree(sc_adapter[i]->channel);
		kfree(sc_adapter[i]->card);
		kfree(sc_adapter[i]);
	}
	pr_info("SpellCaster ISA ISDN Adapter Driver Unloaded.\n");
}

static int identify_board(unsigned long rambase, unsigned int iobase)
{
	unsigned int pgport;
	unsigned long sig;
	DualPortMemory *dpm;
	RspMessage rcvmsg;
	ReqMessage sndmsg;
	HWConfig_pl hwci;
	int x;

	pr_debug("Attempting to identify adapter @ 0x%lx io 0x%x\n",
<<<<<<< HEAD
		rambase, iobase);
=======
		 rambase, iobase);
>>>>>>> cm-10.0

	/*
	 * Enable the base pointer
	 */
	outb(rambase >> 12, iobase + 0x2c00);

<<<<<<< HEAD
	switch(rambase >> 12 & 0x0F) {
=======
	switch (rambase >> 12 & 0x0F) {
>>>>>>> cm-10.0
	case 0x0:
		pgport = iobase + PG0_OFFSET;
		pr_debug("Page Register offset is 0x%x\n", PG0_OFFSET);
		break;
<<<<<<< HEAD
		
=======

>>>>>>> cm-10.0
	case 0x4:
		pgport = iobase + PG1_OFFSET;
		pr_debug("Page Register offset is 0x%x\n", PG1_OFFSET);
		break;

	case 0x8:
		pgport = iobase + PG2_OFFSET;
		pr_debug("Page Register offset is 0x%x\n", PG2_OFFSET);
		break;

	case 0xC:
		pgport = iobase + PG3_OFFSET;
		pr_debug("Page Register offset is 0x%x\n", PG3_OFFSET);
		break;
	default:
		pr_debug("Invalid rambase 0x%lx\n", rambase);
		return -1;
	}

	/*
	 * Try to identify a PRI card
	 */
	outb(PRI_BASEPG_VAL, pgport);
	msleep_interruptible(1000);
	sig = readl(rambase + SIG_OFFSET);
	pr_debug("Looking for a signature, got 0x%lx\n", sig);
<<<<<<< HEAD
	if(sig == SIGNATURE)
=======
	if (sig == SIGNATURE)
>>>>>>> cm-10.0
		return PRI_BOARD;

	/*
	 * Try to identify a PRI card
	 */
	outb(BRI_BASEPG_VAL, pgport);
	msleep_interruptible(1000);
	sig = readl(rambase + SIG_OFFSET);
	pr_debug("Looking for a signature, got 0x%lx\n", sig);
<<<<<<< HEAD
	if(sig == SIGNATURE)
=======
	if (sig == SIGNATURE)
>>>>>>> cm-10.0
		return BRI_BOARD;

	return -1;

	/*
	 * Try to spot a card
	 */
	sig = readl(rambase + SIG_OFFSET);
	pr_debug("Looking for a signature, got 0x%lx\n", sig);
<<<<<<< HEAD
	if(sig != SIGNATURE)
=======
	if (sig != SIGNATURE)
>>>>>>> cm-10.0
		return -1;

	dpm = (DualPortMemory *) rambase;

	memset(&sndmsg, 0, MSG_LEN);
	sndmsg.msg_byte_cnt = 3;
	sndmsg.type = cmReqType1;
	sndmsg.class = cmReqClass0;
	sndmsg.code = cmReqHWConfig;
	memcpy_toio(&(dpm->req_queue[dpm->req_head++]), &sndmsg, MSG_LEN);
	outb(0, iobase + 0x400);
	pr_debug("Sent HWConfig message\n");
	/*
	 * Wait for the response
	 */
	x = 0;
<<<<<<< HEAD
	while((inb(iobase + FIFOSTAT_OFFSET) & RF_HAS_DATA) && x < 100) {
		schedule_timeout_interruptible(1);
		x++;
	}
	if(x == 100) {
=======
	while ((inb(iobase + FIFOSTAT_OFFSET) & RF_HAS_DATA) && x < 100) {
		schedule_timeout_interruptible(1);
		x++;
	}
	if (x == 100) {
>>>>>>> cm-10.0
		pr_debug("Timeout waiting for response\n");
		return -1;
	}

	memcpy_fromio(&rcvmsg, &(dpm->rsp_queue[dpm->rsp_tail]), MSG_LEN);
	pr_debug("Got HWConfig response, status = 0x%x\n", rcvmsg.rsp_status);
	memcpy(&hwci, &(rcvmsg.msg_data.HWCresponse), sizeof(HWConfig_pl));
	pr_debug("Hardware Config: Interface: %s, RAM Size: %ld, Serial: %s\n"
		 "                 Part: %s, Rev: %s\n",
		 hwci.st_u_sense ? "S/T" : "U", hwci.ram_size,
		 hwci.serial_no, hwci.part_no, hwci.rev_no);

<<<<<<< HEAD
	if(!strncmp(PRI_PARTNO, hwci.part_no, 6))
		return PRI_BOARD;
	if(!strncmp(BRI_PARTNO, hwci.part_no, 6))
		return BRI_BOARD;
		
=======
	if (!strncmp(PRI_PARTNO, hwci.part_no, 6))
		return PRI_BOARD;
	if (!strncmp(BRI_PARTNO, hwci.part_no, 6))
		return BRI_BOARD;

>>>>>>> cm-10.0
	return -1;
}

module_init(sc_init);
module_exit(sc_exit);
