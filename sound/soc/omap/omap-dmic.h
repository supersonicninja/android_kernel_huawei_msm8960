/*
 * omap-dmic.h  --  OMAP Digital Microphone Controller
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _OMAP_DMIC_H
#define _OMAP_DMIC_H

<<<<<<< HEAD
=======
#define OMAP_DMIC_REVISION_REG		0x00
#define OMAP_DMIC_SYSCONFIG_REG		0x10
#define OMAP_DMIC_IRQSTATUS_RAW_REG	0x24
#define OMAP_DMIC_IRQSTATUS_REG		0x28
#define OMAP_DMIC_IRQENABLE_SET_REG	0x2C
#define OMAP_DMIC_IRQENABLE_CLR_REG	0x30
#define OMAP_DMIC_IRQWAKE_EN_REG	0x34
#define OMAP_DMIC_DMAENABLE_SET_REG	0x38
#define OMAP_DMIC_DMAENABLE_CLR_REG	0x3C
#define OMAP_DMIC_DMAWAKEEN_REG		0x40
#define OMAP_DMIC_CTRL_REG		0x44
#define OMAP_DMIC_DATA_REG		0x48
#define OMAP_DMIC_FIFO_CTRL_REG		0x4C
#define OMAP_DMIC_FIFO_DMIC1R_DATA_REG	0x50
#define OMAP_DMIC_FIFO_DMIC1L_DATA_REG	0x54
#define OMAP_DMIC_FIFO_DMIC2R_DATA_REG	0x58
#define OMAP_DMIC_FIFO_DMIC2L_DATA_REG	0x5C
#define OMAP_DMIC_FIFO_DMIC3R_DATA_REG	0x60
#define OMAP_DMIC_FIFO_DMIC3L_DATA_REG	0x64

/* IRQSTATUS_RAW, IRQSTATUS, IRQENABLE_SET, IRQENABLE_CLR bit fields */
#define OMAP_DMIC_IRQ			(1 << 0)
#define OMAP_DMIC_IRQ_FULL		(1 << 1)
#define OMAP_DMIC_IRQ_ALMST_EMPTY	(1 << 2)
#define OMAP_DMIC_IRQ_EMPTY		(1 << 3)
#define OMAP_DMIC_IRQ_MASK		0x07

/* DMIC_DMAENABLE bit fields */
#define OMAP_DMIC_DMA_ENABLE		0x1

/* DMIC_CTRL bit fields */
#define OMAP_DMIC_UP1_ENABLE		(1 << 0)
#define OMAP_DMIC_UP2_ENABLE		(1 << 1)
#define OMAP_DMIC_UP3_ENABLE		(1 << 2)
#define OMAP_DMIC_UP_ENABLE_MASK	0x7
#define OMAP_DMIC_FORMAT		(1 << 3)
#define OMAP_DMIC_POLAR1		(1 << 4)
#define OMAP_DMIC_POLAR2		(1 << 5)
#define OMAP_DMIC_POLAR3		(1 << 6)
#define OMAP_DMIC_POLAR_MASK		(0x7 << 4)
#define OMAP_DMIC_CLK_DIV(x)		(((x) & 0x7) << 7)
#define OMAP_DMIC_CLK_DIV_MASK		(0x7 << 7)
#define	OMAP_DMIC_RESET			(1 << 10)

#define OMAP_DMICOUTFORMAT_LJUST	(0 << 3)
#define OMAP_DMICOUTFORMAT_RJUST	(1 << 3)

/* DMIC_FIFO_CTRL bit fields */
#define OMAP_DMIC_THRES_MAX		0xF

>>>>>>> cm-10.0
enum omap_dmic_clk {
	OMAP_DMIC_SYSCLK_PAD_CLKS,		/* PAD_CLKS */
	OMAP_DMIC_SYSCLK_SLIMBLUS_CLKS,		/* SLIMBUS_CLK */
	OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS,		/* DMIC_SYNC_MUX_CLK */
<<<<<<< HEAD
};

/* DMIC dividers */
enum omap_dmic_div {
	OMAP_DMIC_CLKDIV,
=======
	OMAP_DMIC_ABE_DMIC_CLK,			/* abe_dmic_clk */
>>>>>>> cm-10.0
};

#endif
