/* OLPC machine specific definitions */

#ifndef _ASM_X86_OLPC_H
#define _ASM_X86_OLPC_H

#include <asm/geode.h>

struct olpc_platform_t {
	int flags;
	uint32_t boardrev;
	int ecver;
};

#define OLPC_F_PRESENT		0x01
#define OLPC_F_DCON		0x02
<<<<<<< HEAD
=======
#define OLPC_F_EC_WIDE_SCI	0x04
>>>>>>> cm-10.0

#ifdef CONFIG_OLPC

extern struct olpc_platform_t olpc_platform_info;

/*
 * OLPC board IDs contain the major build number within the mask 0x0ff0,
 * and the minor build number within 0x000f.  Pre-builds have a minor
 * number less than 8, and normal builds start at 8.  For example, 0x0B10
 * is a PreB1, and 0x0C18 is a C1.
 */

static inline uint32_t olpc_board(uint8_t id)
{
	return (id << 4) | 0x8;
}

static inline uint32_t olpc_board_pre(uint8_t id)
{
	return id << 4;
}

static inline int machine_is_olpc(void)
{
	return (olpc_platform_info.flags & OLPC_F_PRESENT) ? 1 : 0;
}

/*
 * The DCON is OLPC's Display Controller.  It has a number of unique
 * features that we might want to take advantage of..
 */
static inline int olpc_has_dcon(void)
{
	return (olpc_platform_info.flags & OLPC_F_DCON) ? 1 : 0;
}

/*
 * The "Mass Production" version of OLPC's XO is identified as being model
 * C2.  During the prototype phase, the following models (in chronological
 * order) were created: A1, B1, B2, B3, B4, C1.  The A1 through B2 models
 * were based on Geode GX CPUs, and models after that were based upon
 * Geode LX CPUs.  There were also some hand-assembled models floating
 * around, referred to as PreB1, PreB2, etc.
 */
static inline int olpc_board_at_least(uint32_t rev)
{
	return olpc_platform_info.boardrev >= rev;
}

<<<<<<< HEAD
=======
extern void olpc_ec_wakeup_set(u16 value);
extern void olpc_ec_wakeup_clear(u16 value);
extern bool olpc_ec_wakeup_available(void);

extern int olpc_ec_mask_write(u16 bits);
extern int olpc_ec_sci_query(u16 *sci_value);

>>>>>>> cm-10.0
#else

static inline int machine_is_olpc(void)
{
	return 0;
}

static inline int olpc_has_dcon(void)
{
	return 0;
}

<<<<<<< HEAD
=======
static inline void olpc_ec_wakeup_set(u16 value) { }
static inline void olpc_ec_wakeup_clear(u16 value) { }

static inline bool olpc_ec_wakeup_available(void)
{
	return false;
}

#endif

#ifdef CONFIG_OLPC_XO1_PM
extern void do_olpc_suspend_lowlevel(void);
extern void olpc_xo1_pm_wakeup_set(u16 value);
extern void olpc_xo1_pm_wakeup_clear(u16 value);
>>>>>>> cm-10.0
#endif

extern int pci_olpc_init(void);

/* EC related functions */

extern int olpc_ec_cmd(unsigned char cmd, unsigned char *inbuf, size_t inlen,
		unsigned char *outbuf, size_t outlen);

<<<<<<< HEAD
extern int olpc_ec_mask_set(uint8_t bits);
extern int olpc_ec_mask_unset(uint8_t bits);

/* EC commands */

#define EC_FIRMWARE_REV		0x08
#define EC_WLAN_ENTER_RESET	0x35
#define EC_WLAN_LEAVE_RESET	0x25
=======
/* EC commands */

#define EC_FIRMWARE_REV			0x08
#define EC_WRITE_SCI_MASK		0x1b
#define EC_WAKE_UP_WLAN			0x24
#define EC_WLAN_LEAVE_RESET		0x25
#define EC_READ_EB_MODE			0x2a
#define EC_SET_SCI_INHIBIT		0x32
#define EC_SET_SCI_INHIBIT_RELEASE	0x34
#define EC_WLAN_ENTER_RESET		0x35
#define EC_WRITE_EXT_SCI_MASK		0x38
#define EC_SCI_QUERY			0x84
#define EC_EXT_SCI_QUERY		0x85
>>>>>>> cm-10.0

/* SCI source values */

#define EC_SCI_SRC_EMPTY	0x00
#define EC_SCI_SRC_GAME		0x01
#define EC_SCI_SRC_BATTERY	0x02
#define EC_SCI_SRC_BATSOC	0x04
#define EC_SCI_SRC_BATERR	0x08
<<<<<<< HEAD
#define EC_SCI_SRC_EBOOK	0x10
#define EC_SCI_SRC_WLAN		0x20
#define EC_SCI_SRC_ACPWR	0x40
#define EC_SCI_SRC_ALL		0x7F
=======
#define EC_SCI_SRC_EBOOK	0x10	/* XO-1 only */
#define EC_SCI_SRC_WLAN		0x20	/* XO-1 only */
#define EC_SCI_SRC_ACPWR	0x40
#define EC_SCI_SRC_BATCRIT	0x80
#define EC_SCI_SRC_GPWAKE	0x100	/* XO-1.5 only */
#define EC_SCI_SRC_ALL		0x1FF
>>>>>>> cm-10.0

/* GPIO assignments */

#define OLPC_GPIO_MIC_AC	1
#define OLPC_GPIO_DCON_STAT0	5
#define OLPC_GPIO_DCON_STAT1	6
#define OLPC_GPIO_DCON_IRQ	7
#define OLPC_GPIO_THRM_ALRM	geode_gpio(10)
#define OLPC_GPIO_DCON_LOAD    11
#define OLPC_GPIO_DCON_BLANK   12
#define OLPC_GPIO_SMB_CLK      14
#define OLPC_GPIO_SMB_DATA     15
#define OLPC_GPIO_WORKAUX	geode_gpio(24)
<<<<<<< HEAD
#define OLPC_GPIO_LID		geode_gpio(26)
#define OLPC_GPIO_ECSCI		geode_gpio(27)
=======
#define OLPC_GPIO_LID		26
#define OLPC_GPIO_ECSCI		27
>>>>>>> cm-10.0

#endif /* _ASM_X86_OLPC_H */
