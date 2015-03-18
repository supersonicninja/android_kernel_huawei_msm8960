<<<<<<< HEAD
/* Copyright (c) 2009-2011, Code Aurora Forum. All rights reserved.
=======
/* Copyright (c) 2009-2012, The Linux Foundation. All rights reserved.
>>>>>>> cm-10.0
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#define pr_fmt(fmt) "%s: " fmt, __func__

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/ctype.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/clk.h>

#include <mach/msm_iomap.h>
#include <mach/clk.h>
#include <mach/scm-io.h>

#include "clock.h"
#include "clock-local.h"

#ifdef CONFIG_MSM_SECURE_IO
#undef readl_relaxed
#undef writel_relaxed
#define readl_relaxed secure_readl
#define writel_relaxed secure_writel
#endif

/*
 * When enabling/disabling a clock, check the halt bit up to this number
 * number of times (with a 1 us delay in between) before continuing.
 */
#define HALT_CHECK_MAX_LOOPS	200
/* For clock without halt checking, wait this long after enables/disables. */
#define HALT_CHECK_DELAY_US	10

DEFINE_SPINLOCK(local_clock_reg_lock);
struct clk_freq_tbl rcg_dummy_freq = F_END;

/*
 * Common Set-Rate Functions
 */

/* For clocks with MND dividers. */
<<<<<<< HEAD
void set_rate_mnd(struct rcg_clk *clk, struct clk_freq_tbl *nf)
=======
void set_rate_mnd(struct rcg_clk *rcg, struct clk_freq_tbl *nf)
>>>>>>> cm-10.0
{
	uint32_t ns_reg_val, ctl_reg_val;

	/* Assert MND reset. */
<<<<<<< HEAD
	ns_reg_val = readl_relaxed(clk->ns_reg);
	ns_reg_val |= BIT(7);
	writel_relaxed(ns_reg_val, clk->ns_reg);

	/* Program M and D values. */
	writel_relaxed(nf->md_val, clk->md_reg);

	/* If the clock has a separate CC register, program it. */
	if (clk->ns_reg != clk->b.ctl_reg) {
		ctl_reg_val = readl_relaxed(clk->b.ctl_reg);
		ctl_reg_val &= ~(clk->ctl_mask);
		ctl_reg_val |= nf->ctl_val;
		writel_relaxed(ctl_reg_val, clk->b.ctl_reg);
=======
	ns_reg_val = readl_relaxed(rcg->ns_reg);
	ns_reg_val |= BIT(7);
	writel_relaxed(ns_reg_val, rcg->ns_reg);

	/* Program M and D values. */
	writel_relaxed(nf->md_val, rcg->md_reg);

	/* If the clock has a separate CC register, program it. */
	if (rcg->ns_reg != rcg->b.ctl_reg) {
		ctl_reg_val = readl_relaxed(rcg->b.ctl_reg);
		ctl_reg_val &= ~(rcg->ctl_mask);
		ctl_reg_val |= nf->ctl_val;
		writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);
>>>>>>> cm-10.0
	}

	/* Deassert MND reset. */
	ns_reg_val &= ~BIT(7);
<<<<<<< HEAD
	writel_relaxed(ns_reg_val, clk->ns_reg);
}

void set_rate_nop(struct rcg_clk *clk, struct clk_freq_tbl *nf)
=======
	writel_relaxed(ns_reg_val, rcg->ns_reg);
}

void set_rate_nop(struct rcg_clk *rcg, struct clk_freq_tbl *nf)
>>>>>>> cm-10.0
{
	/*
	 * Nothing to do for fixed-rate or integer-divider clocks. Any settings
	 * in NS registers are applied in the enable path, since power can be
	 * saved by leaving an un-clocked or slowly-clocked source selected
	 * until the clock is enabled.
	 */
}

<<<<<<< HEAD
void set_rate_mnd_8(struct rcg_clk *clk, struct clk_freq_tbl *nf)
=======
void set_rate_mnd_8(struct rcg_clk *rcg, struct clk_freq_tbl *nf)
>>>>>>> cm-10.0
{
	uint32_t ctl_reg_val;

	/* Assert MND reset. */
<<<<<<< HEAD
	ctl_reg_val = readl_relaxed(clk->b.ctl_reg);
	ctl_reg_val |= BIT(8);
	writel_relaxed(ctl_reg_val, clk->b.ctl_reg);

	/* Program M and D values. */
	writel_relaxed(nf->md_val, clk->md_reg);

	/* Program MN counter Enable and Mode. */
	ctl_reg_val &= ~(clk->ctl_mask);
	ctl_reg_val |= nf->ctl_val;
	writel_relaxed(ctl_reg_val, clk->b.ctl_reg);

	/* Deassert MND reset. */
	ctl_reg_val &= ~BIT(8);
	writel_relaxed(ctl_reg_val, clk->b.ctl_reg);
}

void set_rate_mnd_banked(struct rcg_clk *clk, struct clk_freq_tbl *nf)
{
	struct bank_masks *banks = clk->bank_info;
=======
	ctl_reg_val = readl_relaxed(rcg->b.ctl_reg);
	ctl_reg_val |= BIT(8);
	writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);

	/* Program M and D values. */
	writel_relaxed(nf->md_val, rcg->md_reg);

	/* Program MN counter Enable and Mode. */
	ctl_reg_val &= ~(rcg->ctl_mask);
	ctl_reg_val |= nf->ctl_val;
	writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);

	/* Deassert MND reset. */
	ctl_reg_val &= ~BIT(8);
	writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);
}

void set_rate_mnd_banked(struct rcg_clk *rcg, struct clk_freq_tbl *nf)
{
	struct bank_masks *banks = rcg->bank_info;
>>>>>>> cm-10.0
	const struct bank_mask_info *new_bank_masks;
	const struct bank_mask_info *old_bank_masks;
	uint32_t ns_reg_val, ctl_reg_val;
	uint32_t bank_sel;

	/*
	 * Determine active bank and program the other one. If the clock is
	 * off, program the active bank since bank switching won't work if
	 * both banks aren't running.
	 */
<<<<<<< HEAD
	ctl_reg_val = readl_relaxed(clk->b.ctl_reg);
	bank_sel = !!(ctl_reg_val & banks->bank_sel_mask);
	 /* If clock isn't running, don't switch banks. */
	bank_sel ^= (!clk->enabled || clk->current_freq->freq_hz == 0);
=======
	ctl_reg_val = readl_relaxed(rcg->b.ctl_reg);
	bank_sel = !!(ctl_reg_val & banks->bank_sel_mask);
	 /* If clock isn't running, don't switch banks. */
	bank_sel ^= (!rcg->enabled || rcg->current_freq->freq_hz == 0);
>>>>>>> cm-10.0
	if (bank_sel == 0) {
		new_bank_masks = &banks->bank1_mask;
		old_bank_masks = &banks->bank0_mask;
	} else {
		new_bank_masks = &banks->bank0_mask;
		old_bank_masks = &banks->bank1_mask;
	}

<<<<<<< HEAD
	ns_reg_val = readl_relaxed(clk->ns_reg);

	/* Assert bank MND reset. */
	ns_reg_val |= new_bank_masks->rst_mask;
	writel_relaxed(ns_reg_val, clk->ns_reg);
=======
	ns_reg_val = readl_relaxed(rcg->ns_reg);

	/* Assert bank MND reset. */
	ns_reg_val |= new_bank_masks->rst_mask;
	writel_relaxed(ns_reg_val, rcg->ns_reg);
>>>>>>> cm-10.0

	/*
	 * Program NS only if the clock is enabled, since the NS will be set
	 * as part of the enable procedure and should remain with a low-power
	 * MUX input selected until then.
	 */
<<<<<<< HEAD
	if (clk->enabled) {
		ns_reg_val &= ~(new_bank_masks->ns_mask);
		ns_reg_val |= (nf->ns_val & new_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, clk->ns_reg);
=======
	if (rcg->enabled) {
		ns_reg_val &= ~(new_bank_masks->ns_mask);
		ns_reg_val |= (nf->ns_val & new_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, rcg->ns_reg);
>>>>>>> cm-10.0
	}

	writel_relaxed(nf->md_val, new_bank_masks->md_reg);

	/* Enable counter only if clock is enabled. */
<<<<<<< HEAD
	if (clk->enabled)
=======
	if (rcg->enabled)
>>>>>>> cm-10.0
		ctl_reg_val |= new_bank_masks->mnd_en_mask;
	else
		ctl_reg_val &= ~(new_bank_masks->mnd_en_mask);

	ctl_reg_val &= ~(new_bank_masks->mode_mask);
	ctl_reg_val |= (nf->ctl_val & new_bank_masks->mode_mask);
<<<<<<< HEAD
	writel_relaxed(ctl_reg_val, clk->b.ctl_reg);

	/* Deassert bank MND reset. */
	ns_reg_val &= ~(new_bank_masks->rst_mask);
	writel_relaxed(ns_reg_val, clk->ns_reg);
=======
	writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);

	/* Deassert bank MND reset. */
	ns_reg_val &= ~(new_bank_masks->rst_mask);
	writel_relaxed(ns_reg_val, rcg->ns_reg);
>>>>>>> cm-10.0

	/*
	 * Switch to the new bank if clock is running.  If it isn't, then
	 * no switch is necessary since we programmed the active bank.
	 */
<<<<<<< HEAD
	if (clk->enabled && clk->current_freq->freq_hz) {
		ctl_reg_val ^= banks->bank_sel_mask;
		writel_relaxed(ctl_reg_val, clk->b.ctl_reg);
=======
	if (rcg->enabled && rcg->current_freq->freq_hz) {
		ctl_reg_val ^= banks->bank_sel_mask;
		writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);
>>>>>>> cm-10.0
		/*
		 * Wait at least 6 cycles of slowest bank's clock
		 * for the glitch-free MUX to fully switch sources.
		 */
		mb();
		udelay(1);

		/* Disable old bank's MN counter. */
		ctl_reg_val &= ~(old_bank_masks->mnd_en_mask);
<<<<<<< HEAD
		writel_relaxed(ctl_reg_val, clk->b.ctl_reg);

		/* Program old bank to a low-power source and divider. */
		ns_reg_val &= ~(old_bank_masks->ns_mask);
		ns_reg_val |= (clk->freq_tbl->ns_val & old_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, clk->ns_reg);
	}

	/*
	 * If this freq requires the MN counter to be enabled,
	 * update the enable mask to match the current bank.
	 */
	if (nf->mnd_en_mask)
		nf->mnd_en_mask = new_bank_masks->mnd_en_mask;
	/* Update the NS mask to match the current bank. */
	clk->ns_mask = new_bank_masks->ns_mask;
}

void set_rate_div_banked(struct rcg_clk *clk, struct clk_freq_tbl *nf)
{
	struct bank_masks *banks = clk->bank_info;
=======
		writel_relaxed(ctl_reg_val, rcg->b.ctl_reg);

		/* Program old bank to a low-power source and divider. */
		ns_reg_val &= ~(old_bank_masks->ns_mask);
		ns_reg_val |= (rcg->freq_tbl->ns_val & old_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, rcg->ns_reg);
	}

	/* Update the MND_EN and NS masks to match the current bank. */
	rcg->mnd_en_mask = new_bank_masks->mnd_en_mask;
	rcg->ns_mask = new_bank_masks->ns_mask;
}

void set_rate_div_banked(struct rcg_clk *rcg, struct clk_freq_tbl *nf)
{
	struct bank_masks *banks = rcg->bank_info;
>>>>>>> cm-10.0
	const struct bank_mask_info *new_bank_masks;
	const struct bank_mask_info *old_bank_masks;
	uint32_t ns_reg_val, bank_sel;

	/*
	 * Determine active bank and program the other one. If the clock is
	 * off, program the active bank since bank switching won't work if
	 * both banks aren't running.
	 */
<<<<<<< HEAD
	ns_reg_val = readl_relaxed(clk->ns_reg);
	bank_sel = !!(ns_reg_val & banks->bank_sel_mask);
	 /* If clock isn't running, don't switch banks. */
	bank_sel ^= (!clk->enabled || clk->current_freq->freq_hz == 0);
=======
	ns_reg_val = readl_relaxed(rcg->ns_reg);
	bank_sel = !!(ns_reg_val & banks->bank_sel_mask);
	 /* If clock isn't running, don't switch banks. */
	bank_sel ^= (!rcg->enabled || rcg->current_freq->freq_hz == 0);
>>>>>>> cm-10.0
	if (bank_sel == 0) {
		new_bank_masks = &banks->bank1_mask;
		old_bank_masks = &banks->bank0_mask;
	} else {
		new_bank_masks = &banks->bank0_mask;
		old_bank_masks = &banks->bank1_mask;
	}

	/*
	 * Program NS only if the clock is enabled, since the NS will be set
	 * as part of the enable procedure and should remain with a low-power
	 * MUX input selected until then.
	 */
<<<<<<< HEAD
	if (clk->enabled) {
		ns_reg_val &= ~(new_bank_masks->ns_mask);
		ns_reg_val |= (nf->ns_val & new_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, clk->ns_reg);
=======
	if (rcg->enabled) {
		ns_reg_val &= ~(new_bank_masks->ns_mask);
		ns_reg_val |= (nf->ns_val & new_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, rcg->ns_reg);
>>>>>>> cm-10.0
	}

	/*
	 * Switch to the new bank if clock is running.  If it isn't, then
	 * no switch is necessary since we programmed the active bank.
	 */
<<<<<<< HEAD
	if (clk->enabled && clk->current_freq->freq_hz) {
		ns_reg_val ^= banks->bank_sel_mask;
		writel_relaxed(ns_reg_val, clk->ns_reg);
=======
	if (rcg->enabled && rcg->current_freq->freq_hz) {
		ns_reg_val ^= banks->bank_sel_mask;
		writel_relaxed(ns_reg_val, rcg->ns_reg);
>>>>>>> cm-10.0
		/*
		 * Wait at least 6 cycles of slowest bank's clock
		 * for the glitch-free MUX to fully switch sources.
		 */
		mb();
		udelay(1);

		/* Program old bank to a low-power source and divider. */
		ns_reg_val &= ~(old_bank_masks->ns_mask);
<<<<<<< HEAD
		ns_reg_val |= (clk->freq_tbl->ns_val & old_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, clk->ns_reg);
	}

	/* Update the NS mask to match the current bank. */
	clk->ns_mask = new_bank_masks->ns_mask;
=======
		ns_reg_val |= (rcg->freq_tbl->ns_val & old_bank_masks->ns_mask);
		writel_relaxed(ns_reg_val, rcg->ns_reg);
	}

	/* Update the NS mask to match the current bank. */
	rcg->ns_mask = new_bank_masks->ns_mask;
>>>>>>> cm-10.0
}

/*
 * Clock enable/disable functions
 */

/* Return non-zero if a clock status registers shows the clock is halted. */
<<<<<<< HEAD
static int branch_clk_is_halted(const struct branch *clk)
{
	int invert = (clk->halt_check == ENABLE);
	int status_bit = readl_relaxed(clk->halt_reg) & BIT(clk->halt_bit);
	return invert ? !status_bit : status_bit;
}

int branch_in_hwcg_mode(const struct branch *b)
=======
static int branch_clk_is_halted(const struct branch *b)
{
	int invert = (b->halt_check == ENABLE);
	int status_bit = readl_relaxed(b->halt_reg) & BIT(b->halt_bit);
	return invert ? !status_bit : status_bit;
}

static int branch_in_hwcg_mode(const struct branch *b)
>>>>>>> cm-10.0
{
	if (!b->hwcg_mask)
		return 0;

	return !!(readl_relaxed(b->hwcg_reg) & b->hwcg_mask);
}

<<<<<<< HEAD
void __branch_clk_enable_reg(const struct branch *clk, const char *name)
{
	u32 reg_val;

	if (clk->en_mask) {
		reg_val = readl_relaxed(clk->ctl_reg);
		reg_val |= clk->en_mask;
		writel_relaxed(reg_val, clk->ctl_reg);
=======
void __branch_enable_reg(const struct branch *b, const char *name)
{
	u32 reg_val;

	if (b->en_mask) {
		reg_val = readl_relaxed(b->ctl_reg);
		reg_val |= b->en_mask;
		writel_relaxed(reg_val, b->ctl_reg);
>>>>>>> cm-10.0
	}

	/*
	 * Use a memory barrier since some halt status registers are
	 * not within the same 1K segment as the branch/root enable
	 * registers.  It's also needed in the udelay() case to ensure
	 * the delay starts after the branch enable.
	 */
	mb();

	/* Skip checking halt bit if the clock is in hardware gated mode */
<<<<<<< HEAD
	if (branch_in_hwcg_mode(clk))
		return;

	/* Wait for clock to enable before returning. */
	if (clk->halt_check == DELAY)
		udelay(HALT_CHECK_DELAY_US);
	else if (clk->halt_check == ENABLE || clk->halt_check == HALT
			|| clk->halt_check == ENABLE_VOTED
			|| clk->halt_check == HALT_VOTED) {
		int count;

		/* Wait up to HALT_CHECK_MAX_LOOPS for clock to enable. */
		for (count = HALT_CHECK_MAX_LOOPS; branch_clk_is_halted(clk)
=======
	if (branch_in_hwcg_mode(b))
		return;

	/* Wait for clock to enable before returning. */
	if (b->halt_check == DELAY) {
		udelay(HALT_CHECK_DELAY_US);
	} else if (b->halt_check == ENABLE || b->halt_check == HALT
			|| b->halt_check == ENABLE_VOTED
			|| b->halt_check == HALT_VOTED) {
		int count;

		/* Wait up to HALT_CHECK_MAX_LOOPS for clock to enable. */
		for (count = HALT_CHECK_MAX_LOOPS; branch_clk_is_halted(b)
>>>>>>> cm-10.0
					&& count > 0; count--)
			udelay(1);
		WARN(count == 0, "%s status stuck at 'off'", name);
	}
}

/* Perform any register operations required to enable the clock. */
<<<<<<< HEAD
static void __rcg_clk_enable_reg(struct rcg_clk *clk)
{
	u32 reg_val;
	void __iomem *const reg = clk->b.ctl_reg;

	WARN(clk->current_freq == &rcg_dummy_freq,
		"Attempting to enable %s before setting its rate. "
		"Set the rate first!\n", clk->c.dbg_name);
=======
static void __rcg_clk_enable_reg(struct rcg_clk *rcg)
{
	u32 reg_val;
	void __iomem *const reg = rcg->b.ctl_reg;

	WARN(rcg->current_freq == &rcg_dummy_freq,
		"Attempting to enable %s before setting its rate. "
		"Set the rate first!\n", rcg->c.dbg_name);
>>>>>>> cm-10.0

	/*
	 * Program the NS register, if applicable. NS registers are not
	 * set in the set_rate path because power can be saved by deferring
	 * the selection of a clocked source until the clock is enabled.
	 */
<<<<<<< HEAD
	if (clk->ns_mask) {
		reg_val = readl_relaxed(clk->ns_reg);
		reg_val &= ~(clk->ns_mask);
		reg_val |= (clk->current_freq->ns_val & clk->ns_mask);
		writel_relaxed(reg_val, clk->ns_reg);
=======
	if (rcg->ns_mask) {
		reg_val = readl_relaxed(rcg->ns_reg);
		reg_val &= ~(rcg->ns_mask);
		reg_val |= (rcg->current_freq->ns_val & rcg->ns_mask);
		writel_relaxed(reg_val, rcg->ns_reg);
>>>>>>> cm-10.0
	}

	/* Enable MN counter, if applicable. */
	reg_val = readl_relaxed(reg);
<<<<<<< HEAD
	if (clk->current_freq->mnd_en_mask) {
		reg_val |= clk->current_freq->mnd_en_mask;
		writel_relaxed(reg_val, reg);
	}
	/* Enable root. */
	if (clk->root_en_mask) {
		reg_val |= clk->root_en_mask;
		writel_relaxed(reg_val, reg);
	}
	__branch_clk_enable_reg(&clk->b, clk->c.dbg_name);
}

/* Perform any register operations required to disable the branch. */
u32 __branch_clk_disable_reg(const struct branch *clk, const char *name)
{
	u32 reg_val;

	reg_val = readl_relaxed(clk->ctl_reg);
	if (clk->en_mask) {
		reg_val &= ~(clk->en_mask);
		writel_relaxed(reg_val, clk->ctl_reg);
=======
	if (rcg->current_freq->md_val) {
		reg_val |= rcg->mnd_en_mask;
		writel_relaxed(reg_val, reg);
	}
	/* Enable root. */
	if (rcg->root_en_mask) {
		reg_val |= rcg->root_en_mask;
		writel_relaxed(reg_val, reg);
	}
	__branch_enable_reg(&rcg->b, rcg->c.dbg_name);
}

/* Perform any register operations required to disable the branch. */
u32 __branch_disable_reg(const struct branch *b, const char *name)
{
	u32 reg_val;

	reg_val = b->ctl_reg ? readl_relaxed(b->ctl_reg) : 0;
	if (b->en_mask) {
		reg_val &= ~(b->en_mask);
		writel_relaxed(reg_val, b->ctl_reg);
>>>>>>> cm-10.0
	}

	/*
	 * Use a memory barrier since some halt status registers are
	 * not within the same K segment as the branch/root enable
	 * registers.  It's also needed in the udelay() case to ensure
	 * the delay starts after the branch disable.
	 */
	mb();

	/* Skip checking halt bit if the clock is in hardware gated mode */
<<<<<<< HEAD
	if (branch_in_hwcg_mode(clk))
		return reg_val;

	/* Wait for clock to disable before continuing. */
	if (clk->halt_check == DELAY || clk->halt_check == ENABLE_VOTED
				     || clk->halt_check == HALT_VOTED)
		udelay(HALT_CHECK_DELAY_US);
	else if (clk->halt_check == ENABLE || clk->halt_check == HALT) {
		int count;

		/* Wait up to HALT_CHECK_MAX_LOOPS for clock to disable. */
		for (count = HALT_CHECK_MAX_LOOPS; !branch_clk_is_halted(clk)
=======
	if (branch_in_hwcg_mode(b))
		return reg_val;

	/* Wait for clock to disable before continuing. */
	if (b->halt_check == DELAY || b->halt_check == ENABLE_VOTED
				   || b->halt_check == HALT_VOTED) {
		udelay(HALT_CHECK_DELAY_US);
	} else if (b->halt_check == ENABLE || b->halt_check == HALT) {
		int count;

		/* Wait up to HALT_CHECK_MAX_LOOPS for clock to disable. */
		for (count = HALT_CHECK_MAX_LOOPS; !branch_clk_is_halted(b)
>>>>>>> cm-10.0
					&& count > 0; count--)
			udelay(1);
		WARN(count == 0, "%s status stuck at 'on'", name);
	}

	return reg_val;
}

/* Perform any register operations required to disable the generator. */
<<<<<<< HEAD
static void __rcg_clk_disable_reg(struct rcg_clk *clk)
{
	void __iomem *const reg = clk->b.ctl_reg;
	uint32_t reg_val;

	reg_val = __branch_clk_disable_reg(&clk->b, clk->c.dbg_name);
	/* Disable root. */
	if (clk->root_en_mask) {
		reg_val &= ~(clk->root_en_mask);
		writel_relaxed(reg_val, reg);
	}
	/* Disable MN counter, if applicable. */
	if (clk->current_freq->mnd_en_mask) {
		reg_val &= ~(clk->current_freq->mnd_en_mask);
=======
static void __rcg_clk_disable_reg(struct rcg_clk *rcg)
{
	void __iomem *const reg = rcg->b.ctl_reg;
	uint32_t reg_val;

	reg_val = __branch_disable_reg(&rcg->b, rcg->c.dbg_name);
	/* Disable root. */
	if (rcg->root_en_mask) {
		reg_val &= ~(rcg->root_en_mask);
		writel_relaxed(reg_val, reg);
	}
	/* Disable MN counter, if applicable. */
	if (rcg->current_freq->md_val) {
		reg_val &= ~(rcg->mnd_en_mask);
>>>>>>> cm-10.0
		writel_relaxed(reg_val, reg);
	}
	/*
	 * Program NS register to low-power value with an un-clocked or
	 * slowly-clocked source selected.
	 */
<<<<<<< HEAD
	if (clk->ns_mask) {
		reg_val = readl_relaxed(clk->ns_reg);
		reg_val &= ~(clk->ns_mask);
		reg_val |= (clk->freq_tbl->ns_val & clk->ns_mask);
		writel_relaxed(reg_val, clk->ns_reg);
=======
	if (rcg->ns_mask) {
		reg_val = readl_relaxed(rcg->ns_reg);
		reg_val &= ~(rcg->ns_mask);
		reg_val |= (rcg->freq_tbl->ns_val & rcg->ns_mask);
		writel_relaxed(reg_val, rcg->ns_reg);
>>>>>>> cm-10.0
	}
}

/* Enable a rate-settable clock. */
<<<<<<< HEAD
int rcg_clk_enable(struct clk *c)
{
	unsigned long flags;
	struct rcg_clk *clk = to_rcg_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__rcg_clk_enable_reg(clk);
	clk->enabled = true;
=======
static int rcg_clk_enable(struct clk *c)
{
	unsigned long flags;
	struct rcg_clk *rcg = to_rcg_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__rcg_clk_enable_reg(rcg);
	rcg->enabled = true;
>>>>>>> cm-10.0
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);

	return 0;
}

/* Disable a rate-settable clock. */
<<<<<<< HEAD
void rcg_clk_disable(struct clk *c)
{
	unsigned long flags;
	struct rcg_clk *clk = to_rcg_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__rcg_clk_disable_reg(clk);
	clk->enabled = false;
=======
static void rcg_clk_disable(struct clk *c)
{
	unsigned long flags;
	struct rcg_clk *rcg = to_rcg_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__rcg_clk_disable_reg(rcg);
	rcg->enabled = false;
>>>>>>> cm-10.0
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

/*
 * Frequency-related functions
 */

<<<<<<< HEAD
/* Set a clock's frequency. */
static int _rcg_clk_set_rate(struct rcg_clk *clk, struct clk_freq_tbl *nf)
{
	struct clk_freq_tbl *cf;
	int rc = 0;
	struct clk *chld;

	/* Check if frequency is actually changed. */
	cf = clk->current_freq;
	if (nf == cf)
		return 0;

	if (clk->enabled) {
=======
/* Set a clock to an exact rate. */
static int rcg_clk_set_rate(struct clk *c, unsigned long rate)
{
	struct rcg_clk *rcg = to_rcg_clk(c);
	struct clk_freq_tbl *nf, *cf;
	struct clk *chld;
	int rc = 0;

	for (nf = rcg->freq_tbl; nf->freq_hz != FREQ_END
			&& nf->freq_hz != rate; nf++)
		;

	if (nf->freq_hz == FREQ_END)
		return -EINVAL;

	cf = rcg->current_freq;

	if (rcg->enabled) {
>>>>>>> cm-10.0
		/* Enable source clock dependency for the new freq. */
		rc = clk_enable(nf->src_clk);
		if (rc)
			return rc;
	}

	spin_lock(&local_clock_reg_lock);

	/* Disable branch if clock isn't dual-banked with a glitch-free MUX. */
<<<<<<< HEAD
	if (!clk->bank_info) {
		/* Disable all branches to prevent glitches. */
		list_for_each_entry(chld, &clk->c.children, siblings) {
=======
	if (!rcg->bank_info) {
		/* Disable all branches to prevent glitches. */
		list_for_each_entry(chld, &rcg->c.children, siblings) {
>>>>>>> cm-10.0
			struct branch_clk *x = to_branch_clk(chld);
			/*
			 * We don't need to grab the child's lock because
			 * we hold the local_clock_reg_lock and 'enabled' is
			 * only modified within lock.
			 */
			if (x->enabled)
<<<<<<< HEAD
				__branch_clk_disable_reg(&x->b, x->c.dbg_name);
		}
		if (clk->enabled)
			__rcg_clk_disable_reg(clk);
	}

	/* Perform clock-specific frequency switch operations. */
	BUG_ON(!clk->set_rate);
	clk->set_rate(clk, nf);
=======
				__branch_disable_reg(&x->b, x->c.dbg_name);
		}
		if (rcg->enabled)
			__rcg_clk_disable_reg(rcg);
	}

	/* Perform clock-specific frequency switch operations. */
	BUG_ON(!rcg->set_rate);
	rcg->set_rate(rcg, nf);
>>>>>>> cm-10.0

	/*
	 * Current freq must be updated before __rcg_clk_enable_reg()
	 * is called to make sure the MNCNTR_EN bit is set correctly.
	 */
<<<<<<< HEAD
	clk->current_freq = nf;

	/* Enable any clocks that were disabled. */
	if (!clk->bank_info) {
		if (clk->enabled)
			__rcg_clk_enable_reg(clk);
		/* Enable only branches that were ON before. */
		list_for_each_entry(chld, &clk->c.children, siblings) {
			struct branch_clk *x = to_branch_clk(chld);
			if (x->enabled)
				__branch_clk_enable_reg(&x->b, x->c.dbg_name);
=======
	rcg->current_freq = nf;

	/* Enable any clocks that were disabled. */
	if (!rcg->bank_info) {
		if (rcg->enabled)
			__rcg_clk_enable_reg(rcg);
		/* Enable only branches that were ON before. */
		list_for_each_entry(chld, &rcg->c.children, siblings) {
			struct branch_clk *x = to_branch_clk(chld);
			if (x->enabled)
				__branch_enable_reg(&x->b, x->c.dbg_name);
>>>>>>> cm-10.0
		}
	}

	spin_unlock(&local_clock_reg_lock);

	/* Release source requirements of the old freq. */
<<<<<<< HEAD
	if (clk->enabled)
=======
	if (rcg->enabled)
>>>>>>> cm-10.0
		clk_disable(cf->src_clk);

	return rc;
}

<<<<<<< HEAD
/* Set a clock to an exact rate. */
int rcg_clk_set_rate(struct clk *c, unsigned long rate)
{
	struct rcg_clk *clk = to_rcg_clk(c);
	struct clk_freq_tbl *nf;

	for (nf = clk->freq_tbl; nf->freq_hz != FREQ_END
			&& nf->freq_hz != rate; nf++)
		;

	if (nf->freq_hz == FREQ_END)
		return -EINVAL;

	return _rcg_clk_set_rate(clk, nf);
}

/* Get the currently-set rate of a clock in Hz. */
unsigned long rcg_clk_get_rate(struct clk *c)
{
	struct rcg_clk *clk = to_rcg_clk(c);
	unsigned long flags;
	unsigned ret = 0;

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	ret = clk->current_freq->freq_hz;
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);

	/*
	 * Return 0 if the rate has never been set. Might not be correct,
	 * but it's good enough.
	 */
	if (ret == FREQ_END)
		ret = 0;

	return ret;
}

/* Check if a clock is currently enabled. */
int rcg_clk_is_enabled(struct clk *clk)
{
	return to_rcg_clk(clk)->enabled;
}

/* Return a supported rate that's at least the specified rate. */
long rcg_clk_round_rate(struct clk *c, unsigned long rate)
{
	struct rcg_clk *clk = to_rcg_clk(c);
	struct clk_freq_tbl *f;

	for (f = clk->freq_tbl; f->freq_hz != FREQ_END; f++)
=======
/* Check if a clock is currently enabled. */
static int rcg_clk_is_enabled(struct clk *c)
{
	return to_rcg_clk(c)->enabled;
}

/* Return a supported rate that's at least the specified rate. */
static long rcg_clk_round_rate(struct clk *c, unsigned long rate)
{
	struct rcg_clk *rcg = to_rcg_clk(c);
	struct clk_freq_tbl *f;

	for (f = rcg->freq_tbl; f->freq_hz != FREQ_END; f++)
>>>>>>> cm-10.0
		if (f->freq_hz >= rate)
			return f->freq_hz;

	return -EPERM;
}

<<<<<<< HEAD
bool local_clk_is_local(struct clk *clk)
{
	return true;
}

/* Return the nth supported frequency for a given clock. */
int rcg_clk_list_rate(struct clk *c, unsigned n)
{
	struct rcg_clk *clk = to_rcg_clk(c);

	if (!clk->freq_tbl || clk->freq_tbl->freq_hz == FREQ_END)
		return -ENXIO;

	return (clk->freq_tbl + n)->freq_hz;
}

struct clk *rcg_clk_get_parent(struct clk *clk)
{
	return to_rcg_clk(clk)->current_freq->src_clk;
}

/* Disable hw clock gating if not set at boot */
static void branch_handoff(struct branch *clk, struct clk *c)
{
	if (!branch_in_hwcg_mode(clk)) {
		clk->hwcg_mask = 0;
		c->flags &= ~CLKFLAG_HWCG;
	} else {
		c->flags |= CLKFLAG_HWCG;
	}
}

int branch_clk_handoff(struct clk *c)
{
	struct branch_clk *clk = to_branch_clk(c);
	branch_handoff(&clk->b, &clk->c);
	return 0;
}

int rcg_clk_handoff(struct clk *c)
{
	struct rcg_clk *clk = to_rcg_clk(c);
	uint32_t ctl_val, ns_val, md_val, ns_mask;
	struct clk_freq_tbl *freq;

	branch_handoff(&clk->b, &clk->c);

	ctl_val = readl_relaxed(clk->b.ctl_reg);
	if (!(ctl_val & clk->root_en_mask))
		return 0;

	if (clk->bank_info) {
		const struct bank_masks *bank_masks = clk->bank_info;
=======
/* Return the nth supported frequency for a given clock. */
static int rcg_clk_list_rate(struct clk *c, unsigned n)
{
	struct rcg_clk *rcg = to_rcg_clk(c);

	if (!rcg->freq_tbl || rcg->freq_tbl->freq_hz == FREQ_END)
		return -ENXIO;

	return (rcg->freq_tbl + n)->freq_hz;
}

static struct clk *rcg_clk_get_parent(struct clk *c)
{
	return to_rcg_clk(c)->current_freq->src_clk;
}

/* Disable hw clock gating if not set at boot */
enum handoff branch_handoff(struct branch *b, struct clk *c)
{
	if (!branch_in_hwcg_mode(b)) {
		b->hwcg_mask = 0;
		c->flags &= ~CLKFLAG_HWCG;
		if (b->ctl_reg && readl_relaxed(b->ctl_reg) & b->en_mask)
			return HANDOFF_ENABLED_CLK;
	} else {
		c->flags |= CLKFLAG_HWCG;
	}
	return HANDOFF_DISABLED_CLK;
}

static enum handoff branch_clk_handoff(struct clk *c)
{
	struct branch_clk *br = to_branch_clk(c);
	return branch_handoff(&br->b, &br->c);
}

static enum handoff rcg_clk_handoff(struct clk *c)
{
	struct rcg_clk *rcg = to_rcg_clk(c);
	uint32_t ctl_val, ns_val, md_val, ns_mask;
	struct clk_freq_tbl *freq;
	enum handoff ret;

	ctl_val = readl_relaxed(rcg->b.ctl_reg);
	ret = branch_handoff(&rcg->b, &rcg->c);
	if (ret == HANDOFF_DISABLED_CLK)
		return HANDOFF_DISABLED_CLK;

	if (rcg->bank_info) {
		const struct bank_masks *bank_masks = rcg->bank_info;
>>>>>>> cm-10.0
		const struct bank_mask_info *bank_info;
		if (!(ctl_val & bank_masks->bank_sel_mask))
			bank_info = &bank_masks->bank0_mask;
		else
			bank_info = &bank_masks->bank1_mask;

		ns_mask = bank_info->ns_mask;
<<<<<<< HEAD
		md_val = readl_relaxed(bank_info->md_reg);
	} else {
		ns_mask = clk->ns_mask;
		md_val = clk->md_reg ? readl_relaxed(clk->md_reg) : 0;
	}

	ns_val = readl_relaxed(clk->ns_reg) & ns_mask;
	for (freq = clk->freq_tbl; freq->freq_hz != FREQ_END; freq++) {
		if ((freq->ns_val & ns_mask) == ns_val &&
		    (freq->mnd_en_mask || freq->md_val == md_val)) {
			pr_info("%s rate=%d\n", clk->c.dbg_name, freq->freq_hz);
			break;
		}
	}
	if (freq->freq_hz == FREQ_END)
		return 0;

	clk->current_freq = freq;

	return 1;
}

int pll_vote_clk_enable(struct clk *clk)
{
	u32 ena;
	unsigned long flags;
	struct pll_vote_clk *pll = to_pll_vote_clk(clk);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	ena = readl_relaxed(pll->en_reg);
	ena |= pll->en_mask;
	writel_relaxed(ena, pll->en_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);

	/* Wait until PLL is enabled */
	while ((readl_relaxed(pll->status_reg) & BIT(16)) == 0)
		cpu_relax();

	return 0;
}

void pll_vote_clk_disable(struct clk *clk)
{
	u32 ena;
	unsigned long flags;
	struct pll_vote_clk *pll = to_pll_vote_clk(clk);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	ena = readl_relaxed(pll->en_reg);
	ena &= ~(pll->en_mask);
	writel_relaxed(ena, pll->en_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

unsigned long pll_vote_clk_get_rate(struct clk *clk)
{
	struct pll_vote_clk *pll = to_pll_vote_clk(clk);
	return pll->rate;
}

struct clk *pll_vote_clk_get_parent(struct clk *clk)
{
	struct pll_vote_clk *pll = to_pll_vote_clk(clk);
	return pll->parent;
}

int pll_vote_clk_is_enabled(struct clk *clk)
{
	struct pll_vote_clk *pll = to_pll_vote_clk(clk);
	return !!(readl_relaxed(pll->status_reg) & BIT(16));
}

struct clk_ops clk_ops_pll_vote = {
	.enable = pll_vote_clk_enable,
	.disable = pll_vote_clk_disable,
	.auto_off = pll_vote_clk_disable,
	.is_enabled = pll_vote_clk_is_enabled,
	.get_rate = pll_vote_clk_get_rate,
	.get_parent = pll_vote_clk_get_parent,
	.is_local = local_clk_is_local,
};

static int pll_clk_enable(struct clk *clk)
{
	u32 mode;
	unsigned long flags;
	struct pll_clk *pll = to_pll_clk(clk);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	mode = readl_relaxed(pll->mode_reg);
	/* Disable PLL bypass mode. */
	mode |= BIT(1);
	writel_relaxed(mode, pll->mode_reg);

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-asserting the reset. Delay 10us just to be safe.
	 */
	mb();
	udelay(10);

	/* De-assert active-low PLL reset. */
	mode |= BIT(2);
	writel_relaxed(mode, pll->mode_reg);

	/* Wait until PLL is locked. */
	mb();
	udelay(50);

	/* Enable PLL output. */
	mode |= BIT(0);
	writel_relaxed(mode, pll->mode_reg);

	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
	return 0;
}

static void pll_clk_disable(struct clk *clk)
{
	u32 mode;
	unsigned long flags;
	struct pll_clk *pll = to_pll_clk(clk);

	/*
	 * Disable the PLL output, disable test mode, enable
	 * the bypass mode, and assert the reset.
	 */
	spin_lock_irqsave(&local_clock_reg_lock, flags);
	mode = readl_relaxed(pll->mode_reg);
	mode &= ~BM(3, 0);
	writel_relaxed(mode, pll->mode_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

static unsigned long pll_clk_get_rate(struct clk *clk)
{
	struct pll_clk *pll = to_pll_clk(clk);
	return pll->rate;
}

static struct clk *pll_clk_get_parent(struct clk *clk)
{
	struct pll_clk *pll = to_pll_clk(clk);
	return pll->parent;
}

int sr_pll_clk_enable(struct clk *clk)
{
	u32 mode;
	unsigned long flags;
	struct pll_clk *pll = to_pll_clk(clk);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	mode = readl_relaxed(pll->mode_reg);
	/* De-assert active-low PLL reset. */
	mode |= BIT(2);
	writel_relaxed(mode, pll->mode_reg);

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-asserting the reset. Delay 10us just to be safe.
	 */
	mb();
	udelay(10);

	/* Disable PLL bypass mode. */
	mode |= BIT(1);
	writel_relaxed(mode, pll->mode_reg);

	/* Wait until PLL is locked. */
	mb();
	udelay(60);

	/* Enable PLL output. */
	mode |= BIT(0);
	writel_relaxed(mode, pll->mode_reg);

	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
	return 0;
}

struct clk_ops clk_ops_pll = {
	.enable = pll_clk_enable,
	.disable = pll_clk_disable,
	.auto_off = pll_clk_disable,
	.get_rate = pll_clk_get_rate,
	.get_parent = pll_clk_get_parent,
	.is_local = local_clk_is_local,
};

struct clk_ops clk_ops_gnd = {
	.get_rate = fixed_clk_get_rate,
	.is_local = local_clk_is_local,
};
=======
		md_val = bank_info->md_reg ?
				readl_relaxed(bank_info->md_reg) : 0;
	} else {
		ns_mask = rcg->ns_mask;
		md_val = rcg->md_reg ? readl_relaxed(rcg->md_reg) : 0;
	}
	if (!ns_mask)
		return HANDOFF_UNKNOWN_RATE;
	ns_val = readl_relaxed(rcg->ns_reg) & ns_mask;
	for (freq = rcg->freq_tbl; freq->freq_hz != FREQ_END; freq++) {
		if ((freq->ns_val & ns_mask) == ns_val &&
		    (!freq->md_val || freq->md_val == md_val))
			break;
	}
	if (freq->freq_hz == FREQ_END)
		return HANDOFF_UNKNOWN_RATE;

	rcg->current_freq = freq;
	c->rate = freq->freq_hz;

	return HANDOFF_ENABLED_CLK;
}

struct clk_ops clk_ops_empty;
>>>>>>> cm-10.0

struct fixed_clk gnd_clk = {
	.c = {
		.dbg_name = "ground_clk",
<<<<<<< HEAD
		.ops = &clk_ops_gnd,
=======
		.ops = &clk_ops_empty,
>>>>>>> cm-10.0
		CLK_INIT(gnd_clk.c),
	},
};

<<<<<<< HEAD
struct clk_ops clk_ops_measure = {
	.is_local = local_clk_is_local,
};

int branch_clk_enable(struct clk *clk)
{
	unsigned long flags;
	struct branch_clk *branch = to_branch_clk(clk);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_clk_enable_reg(&branch->b, branch->c.dbg_name);
	branch->enabled = true;
=======
static int branch_clk_enable(struct clk *c)
{
	unsigned long flags;
	struct branch_clk *br = to_branch_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_enable_reg(&br->b, br->c.dbg_name);
	br->enabled = true;
>>>>>>> cm-10.0
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);

	return 0;
}

<<<<<<< HEAD
void branch_clk_disable(struct clk *clk)
{
	unsigned long flags;
	struct branch_clk *branch = to_branch_clk(clk);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_clk_disable_reg(&branch->b, branch->c.dbg_name);
	branch->enabled = false;
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

struct clk *branch_clk_get_parent(struct clk *clk)
{
	struct branch_clk *branch = to_branch_clk(clk);
	return branch->parent;
}

int branch_clk_set_parent(struct clk *clk, struct clk *parent)
{
	/*
	 * We setup the parent pointer at init time in msm_clock_init().
	 * This check is to make sure drivers can't change the parent.
	 */
	if (parent && list_empty(&clk->siblings)) {
		list_add(&clk->siblings, &parent->children);
		return 0;
	}
	return -EINVAL;
}

int branch_clk_is_enabled(struct clk *clk)
{
	struct branch_clk *branch = to_branch_clk(clk);
	return branch->enabled;
=======
static void branch_clk_disable(struct clk *c)
{
	unsigned long flags;
	struct branch_clk *br = to_branch_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_disable_reg(&br->b, br->c.dbg_name);
	br->enabled = false;
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

static struct clk *branch_clk_get_parent(struct clk *c)
{
	return to_branch_clk(c)->parent;
}

static int branch_clk_is_enabled(struct clk *c)
{
	return to_branch_clk(c)->enabled;
>>>>>>> cm-10.0
}

static void branch_enable_hwcg(struct branch *b)
{
	unsigned long flags;
	u32 reg_val;

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	reg_val = readl_relaxed(b->hwcg_reg);
	reg_val |= b->hwcg_mask;
	writel_relaxed(reg_val, b->hwcg_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

static void branch_disable_hwcg(struct branch *b)
{
	unsigned long flags;
	u32 reg_val;

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	reg_val = readl_relaxed(b->hwcg_reg);
	reg_val &= ~b->hwcg_mask;
	writel_relaxed(reg_val, b->hwcg_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

<<<<<<< HEAD
void branch_clk_enable_hwcg(struct clk *clk)
{
	struct branch_clk *branch = to_branch_clk(clk);
	branch_enable_hwcg(&branch->b);
}

void branch_clk_disable_hwcg(struct clk *clk)
{
	struct branch_clk *branch = to_branch_clk(clk);
	branch_disable_hwcg(&branch->b);
=======
static void branch_clk_enable_hwcg(struct clk *c)
{
	branch_enable_hwcg(&to_branch_clk(c)->b);
}

static void branch_clk_disable_hwcg(struct clk *c)
{
	branch_disable_hwcg(&to_branch_clk(c)->b);
>>>>>>> cm-10.0
}

static int branch_set_flags(struct branch *b, unsigned flags)
{
	unsigned long irq_flags;
	u32 reg_val;
	int ret = 0;

	if (!b->retain_reg)
		return -EPERM;

	spin_lock_irqsave(&local_clock_reg_lock, irq_flags);
	reg_val = readl_relaxed(b->retain_reg);
	switch (flags) {
	case CLKFLAG_RETAIN:
		reg_val |= b->retain_mask;
		break;
	case CLKFLAG_NORETAIN:
		reg_val &= ~b->retain_mask;
		break;
	default:
		ret = -EINVAL;
	}
	writel_relaxed(reg_val, b->retain_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, irq_flags);

	return ret;
}

<<<<<<< HEAD
int branch_clk_set_flags(struct clk *clk, unsigned flags)
=======
static int branch_clk_set_flags(struct clk *clk, unsigned flags)
>>>>>>> cm-10.0
{
	return branch_set_flags(&to_branch_clk(clk)->b, flags);
}

<<<<<<< HEAD
int branch_clk_in_hwcg_mode(struct clk *c)
{
	struct branch_clk *clk = to_branch_clk(c);
	return branch_in_hwcg_mode(&clk->b);
}

void rcg_clk_enable_hwcg(struct clk *clk)
{
	struct rcg_clk *rcg = to_rcg_clk(clk);
	branch_enable_hwcg(&rcg->b);
}

void rcg_clk_disable_hwcg(struct clk *clk)
{
	struct rcg_clk *rcg = to_rcg_clk(clk);
	branch_disable_hwcg(&rcg->b);
}

int rcg_clk_in_hwcg_mode(struct clk *c)
{
	struct rcg_clk *clk = to_rcg_clk(c);
	return branch_in_hwcg_mode(&clk->b);
}

int rcg_clk_set_flags(struct clk *clk, unsigned flags)
=======
static int branch_clk_in_hwcg_mode(struct clk *c)
{
	return branch_in_hwcg_mode(&to_branch_clk(c)->b);
}

static void rcg_clk_enable_hwcg(struct clk *c)
{
	branch_enable_hwcg(&to_rcg_clk(c)->b);
}

static void rcg_clk_disable_hwcg(struct clk *c)
{
	branch_disable_hwcg(&to_rcg_clk(c)->b);
}

static int rcg_clk_in_hwcg_mode(struct clk *c)
{
	return branch_in_hwcg_mode(&to_rcg_clk(c)->b);
}

static int rcg_clk_set_flags(struct clk *clk, unsigned flags)
>>>>>>> cm-10.0
{
	return branch_set_flags(&to_rcg_clk(clk)->b, flags);
}

int branch_reset(struct branch *b, enum clk_reset_action action)
{
	int ret = 0;
	u32 reg_val;
	unsigned long flags;

	if (!b->reset_reg)
		return -EPERM;

	/* Disable hw gating when asserting a reset */
	if (b->hwcg_mask && action == CLK_RESET_ASSERT)
		branch_disable_hwcg(b);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	/* Assert/Deassert reset */
	reg_val = readl_relaxed(b->reset_reg);
	switch (action) {
	case CLK_RESET_ASSERT:
		reg_val |= b->reset_mask;
		break;
	case CLK_RESET_DEASSERT:
		reg_val &= ~b->reset_mask;
		break;
	default:
		ret = -EINVAL;
	}
	writel_relaxed(reg_val, b->reset_reg);
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);

	/* Enable hw gating when deasserting a reset */
	if (b->hwcg_mask && action == CLK_RESET_DEASSERT)
		branch_enable_hwcg(b);
	/* Make sure write is issued before returning. */
	mb();
	return ret;
}

<<<<<<< HEAD
int branch_clk_reset(struct clk *clk, enum clk_reset_action action)
{
	return branch_reset(&to_branch_clk(clk)->b, action);
}

int rcg_clk_reset(struct clk *clk, enum clk_reset_action action)
{
	return branch_reset(&to_rcg_clk(clk)->b, action);
}
=======
static int branch_clk_reset(struct clk *c, enum clk_reset_action action)
{
	return branch_reset(&to_branch_clk(c)->b, action);
}

struct clk_ops clk_ops_branch = {
	.enable = branch_clk_enable,
	.disable = branch_clk_disable,
	.enable_hwcg = branch_clk_enable_hwcg,
	.disable_hwcg = branch_clk_disable_hwcg,
	.in_hwcg_mode = branch_clk_in_hwcg_mode,
	.is_enabled = branch_clk_is_enabled,
	.reset = branch_clk_reset,
	.get_parent = branch_clk_get_parent,
	.handoff = branch_clk_handoff,
	.set_flags = branch_clk_set_flags,
};

struct clk_ops clk_ops_reset = {
	.reset = branch_clk_reset,
};

static int rcg_clk_reset(struct clk *c, enum clk_reset_action action)
{
	return branch_reset(&to_rcg_clk(c)->b, action);
}

struct clk_ops clk_ops_rcg = {
	.enable = rcg_clk_enable,
	.disable = rcg_clk_disable,
	.enable_hwcg = rcg_clk_enable_hwcg,
	.disable_hwcg = rcg_clk_disable_hwcg,
	.in_hwcg_mode = rcg_clk_in_hwcg_mode,
	.handoff = rcg_clk_handoff,
	.set_rate = rcg_clk_set_rate,
	.list_rate = rcg_clk_list_rate,
	.is_enabled = rcg_clk_is_enabled,
	.round_rate = rcg_clk_round_rate,
	.reset = rcg_clk_reset,
	.get_parent = rcg_clk_get_parent,
	.set_flags = rcg_clk_set_flags,
};
>>>>>>> cm-10.0

static int cdiv_clk_enable(struct clk *c)
{
	unsigned long flags;
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_clk_enable_reg(&clk->b, clk->c.dbg_name);
=======
	struct cdiv_clk *cdiv = to_cdiv_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_enable_reg(&cdiv->b, cdiv->c.dbg_name);
>>>>>>> cm-10.0
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);

	return 0;
}

static void cdiv_clk_disable(struct clk *c)
{
	unsigned long flags;
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_clk_disable_reg(&clk->b, clk->c.dbg_name);
=======
	struct cdiv_clk *cdiv = to_cdiv_clk(c);

	spin_lock_irqsave(&local_clock_reg_lock, flags);
	__branch_disable_reg(&cdiv->b, cdiv->c.dbg_name);
>>>>>>> cm-10.0
	spin_unlock_irqrestore(&local_clock_reg_lock, flags);
}

static int cdiv_clk_set_rate(struct clk *c, unsigned long rate)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	u32 reg_val;

	if (rate > clk->max_div)
		return -EINVAL;
	/* Check if frequency is actually changed. */
	if (rate == clk->cur_div)
		return 0;

	spin_lock(&local_clock_reg_lock);
	reg_val = readl_relaxed(clk->ns_reg);
	reg_val &= ~(clk->ext_mask | (clk->max_div - 1) << clk->div_offset);
	/* Non-zero rates mean set a divider, zero means use external input */
	if (rate)
		reg_val |= (rate - 1) << clk->div_offset;
	else
		reg_val |= clk->ext_mask;
	writel_relaxed(reg_val, clk->ns_reg);
	spin_unlock(&local_clock_reg_lock);

	clk->cur_div = rate;
=======
	struct cdiv_clk *cdiv = to_cdiv_clk(c);
	u32 reg_val;

	if (rate > cdiv->max_div)
		return -EINVAL;

	spin_lock(&local_clock_reg_lock);
	reg_val = readl_relaxed(cdiv->ns_reg);
	reg_val &= ~(cdiv->ext_mask | (cdiv->max_div - 1) << cdiv->div_offset);
	/* Non-zero rates mean set a divider, zero means use external input */
	if (rate)
		reg_val |= (rate - 1) << cdiv->div_offset;
	else
		reg_val |= cdiv->ext_mask;
	writel_relaxed(reg_val, cdiv->ns_reg);
	spin_unlock(&local_clock_reg_lock);

	cdiv->cur_div = rate;
>>>>>>> cm-10.0
	return 0;
}

static unsigned long cdiv_clk_get_rate(struct clk *c)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	return clk->cur_div;
=======
	return to_cdiv_clk(c)->cur_div;
>>>>>>> cm-10.0
}

static long cdiv_clk_round_rate(struct clk *c, unsigned long rate)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	return rate > clk->max_div ? -EPERM : rate;
=======
	return rate > to_cdiv_clk(c)->max_div ? -EPERM : rate;
>>>>>>> cm-10.0
}

static int cdiv_clk_list_rate(struct clk *c, unsigned n)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	return n > clk->max_div ? -ENXIO : n;
}

static int cdiv_clk_handoff(struct clk *c)
{
	struct cdiv_clk *clk = to_cdiv_clk(c);
	u32 reg_val;

	branch_handoff(&clk->b, &clk->c);

	reg_val = readl_relaxed(clk->ns_reg);
	if (reg_val & clk->ext_mask) {
		clk->cur_div = 0;
	} else {
		reg_val >>= clk->div_offset;
		clk->cur_div = (reg_val & (clk->max_div - 1)) + 1;
	}

	return 0;
=======
	return n > to_cdiv_clk(c)->max_div ? -ENXIO : n;
}

static enum handoff cdiv_clk_handoff(struct clk *c)
{
	struct cdiv_clk *cdiv = to_cdiv_clk(c);
	enum handoff ret;
	u32 reg_val;

	ret = branch_handoff(&cdiv->b, &cdiv->c);
	if (ret == HANDOFF_DISABLED_CLK)
		return ret;

	reg_val = readl_relaxed(cdiv->ns_reg);
	if (reg_val & cdiv->ext_mask) {
		cdiv->cur_div = 0;
	} else {
		reg_val >>= cdiv->div_offset;
		cdiv->cur_div = (reg_val & (cdiv->max_div - 1)) + 1;
	}

	return HANDOFF_ENABLED_CLK;
>>>>>>> cm-10.0
}

static void cdiv_clk_enable_hwcg(struct clk *c)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	branch_enable_hwcg(&clk->b);
=======
	branch_enable_hwcg(&to_cdiv_clk(c)->b);
>>>>>>> cm-10.0
}

static void cdiv_clk_disable_hwcg(struct clk *c)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	branch_disable_hwcg(&clk->b);
=======
	branch_disable_hwcg(&to_cdiv_clk(c)->b);
>>>>>>> cm-10.0
}

static int cdiv_clk_in_hwcg_mode(struct clk *c)
{
<<<<<<< HEAD
	struct cdiv_clk *clk = to_cdiv_clk(c);
	return branch_in_hwcg_mode(&clk->b);
=======
	return branch_in_hwcg_mode(&to_cdiv_clk(c)->b);
>>>>>>> cm-10.0
}

struct clk_ops clk_ops_cdiv = {
	.enable = cdiv_clk_enable,
	.disable = cdiv_clk_disable,
	.in_hwcg_mode = cdiv_clk_in_hwcg_mode,
	.enable_hwcg = cdiv_clk_enable_hwcg,
	.disable_hwcg = cdiv_clk_disable_hwcg,
<<<<<<< HEAD
	.auto_off = cdiv_clk_disable,
=======
>>>>>>> cm-10.0
	.handoff = cdiv_clk_handoff,
	.set_rate = cdiv_clk_set_rate,
	.get_rate = cdiv_clk_get_rate,
	.list_rate = cdiv_clk_list_rate,
	.round_rate = cdiv_clk_round_rate,
<<<<<<< HEAD
	.is_local = local_clk_is_local,
=======
>>>>>>> cm-10.0
};
