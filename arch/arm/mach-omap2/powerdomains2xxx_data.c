/*
 * OMAP2XXX powerdomain definitions
 *
<<<<<<< HEAD
 * Copyright (C) 2007-2008 Texas Instruments, Inc.
=======
 * Copyright (C) 2007-2008, 2011 Texas Instruments, Inc.
>>>>>>> cm-10.0
 * Copyright (C) 2007-2011 Nokia Corporation
 *
 * Paul Walmsley, Jouni Högander
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>

#include "powerdomain.h"
#include "powerdomains2xxx_3xxx_data.h"

#include "prcm-common.h"
#include "prm2xxx_3xxx.h"
#include "prm-regbits-24xx.h"

/* 24XX powerdomains and dependencies */

/* Powerdomains */

static struct powerdomain dsp_pwrdm = {
	.name		  = "dsp_pwrdm",
	.prcm_offs	  = OMAP24XX_DSP_MOD,
<<<<<<< HEAD
	.omap_chip	  = OMAP_CHIP_INIT(CHIP_IS_OMAP24XX),
=======
>>>>>>> cm-10.0
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = {
		[0] = PWRSTS_RET,
	},
	.pwrsts_mem_on	  = {
		[0] = PWRSTS_ON,
	},
<<<<<<< HEAD
=======
	.voltdm           = { .name = "core" },
>>>>>>> cm-10.0
};

static struct powerdomain mpu_24xx_pwrdm = {
	.name		  = "mpu_pwrdm",
	.prcm_offs	  = MPU_MOD,
<<<<<<< HEAD
	.omap_chip	  = OMAP_CHIP_INIT(CHIP_IS_OMAP24XX),
=======
>>>>>>> cm-10.0
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = {
		[0] = PWRSTS_RET,
	},
	.pwrsts_mem_on	  = {
		[0] = PWRSTS_ON,
	},
<<<<<<< HEAD
=======
	.voltdm           = { .name = "core" },
>>>>>>> cm-10.0
};

static struct powerdomain core_24xx_pwrdm = {
	.name		  = "core_pwrdm",
	.prcm_offs	  = CORE_MOD,
<<<<<<< HEAD
	.omap_chip	  = OMAP_CHIP_INIT(CHIP_IS_OMAP24XX),
=======
>>>>>>> cm-10.0
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.banks		  = 3,
	.pwrsts_mem_ret	  = {
		[0] = PWRSTS_OFF_RET,	 /* MEM1RETSTATE */
		[1] = PWRSTS_OFF_RET,	 /* MEM2RETSTATE */
		[2] = PWRSTS_OFF_RET,	 /* MEM3RETSTATE */
	},
	.pwrsts_mem_on	  = {
		[0] = PWRSTS_OFF_RET_ON, /* MEM1ONSTATE */
		[1] = PWRSTS_OFF_RET_ON, /* MEM2ONSTATE */
		[2] = PWRSTS_OFF_RET_ON, /* MEM3ONSTATE */
	},
<<<<<<< HEAD
=======
	.voltdm           = { .name = "core" },
>>>>>>> cm-10.0
};


/*
 * 2430-specific powerdomains
 */

<<<<<<< HEAD
#ifdef CONFIG_SOC_OMAP2430

=======
>>>>>>> cm-10.0
/* XXX 2430 KILLDOMAINWKUP bit?  No current users apparently */

static struct powerdomain mdm_pwrdm = {
	.name		  = "mdm_pwrdm",
	.prcm_offs	  = OMAP2430_MDM_MOD,
<<<<<<< HEAD
	.omap_chip	  = OMAP_CHIP_INIT(CHIP_IS_OMAP2430),
=======
>>>>>>> cm-10.0
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = {
		[0] = PWRSTS_RET, /* MEMRETSTATE */
	},
	.pwrsts_mem_on	  = {
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	},
<<<<<<< HEAD
};

#endif     /* CONFIG_SOC_OMAP2430 */

/* As powerdomains are added or removed above, this list must also be changed */
static struct powerdomain *powerdomains_omap2xxx[] __initdata = {

	&wkup_omap2_pwrdm,
	&gfx_omap2_pwrdm,

#ifdef CONFIG_ARCH_OMAP2
	&dsp_pwrdm,
	&mpu_24xx_pwrdm,
	&core_24xx_pwrdm,
#endif

#ifdef CONFIG_SOC_OMAP2430
	&mdm_pwrdm,
#endif
	NULL
};

void __init omap2xxx_powerdomains_init(void)
{
	pwrdm_init(powerdomains_omap2xxx, &omap2_pwrdm_operations);
=======
	.voltdm           = { .name = "core" },
};

/*
 *
 */

static struct powerdomain *powerdomains_omap24xx[] __initdata = {
	&wkup_omap2_pwrdm,
	&gfx_omap2_pwrdm,
	&dsp_pwrdm,
	&mpu_24xx_pwrdm,
	&core_24xx_pwrdm,
	NULL
};

static struct powerdomain *powerdomains_omap2430[] __initdata = {
	&mdm_pwrdm,
	NULL
};

void __init omap242x_powerdomains_init(void)
{
	if (!cpu_is_omap2420())
		return;

	pwrdm_register_platform_funcs(&omap2_pwrdm_operations);
	pwrdm_register_pwrdms(powerdomains_omap24xx);
	pwrdm_complete_init();
}

void __init omap243x_powerdomains_init(void)
{
	if (!cpu_is_omap2430())
		return;

	pwrdm_register_platform_funcs(&omap2_pwrdm_operations);
	pwrdm_register_pwrdms(powerdomains_omap24xx);
	pwrdm_register_pwrdms(powerdomains_omap2430);
	pwrdm_complete_init();
>>>>>>> cm-10.0
}
