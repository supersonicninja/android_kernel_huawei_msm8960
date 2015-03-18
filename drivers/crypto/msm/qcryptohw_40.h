<<<<<<< HEAD
/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
=======
/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
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
 */

#ifndef _DRIVERS_CRYPTO_MSM_QCRYPTOHW_40_H_
#define _DRIVERS_CRYPTO_MSM_QCRYPTOHW_40_H_


#define QCE_AUTH_REG_BYTE_COUNT 4
#define CRYPTO_VERSION_REG			0x0
#define CRYPTO_DATA_IN_REG			0x008
#define CRYPTO_DATA_OUT_REG			0x010
#define CRYPTO_STATUS_REG			0x100
#define CRYPTO_ENGINES_AVAIL			0x104
#define CRYPTO3_VERSION_REG			0x108
#define CRYPTO_SEG_SIZE_REG			0x200
#define CRYPTO_GOPROC_REG			0x204
#define CRYPTO_ENCR_SEG_CFG_REG			0x300

#define CRYPTO_ENCR_SEG_SIZE_REG		0x304
#define CRYPTO_ENCR_SEG_START_REG		0x308

#define CRYPTO_ENCR_KEY0_REG			0x310
#define CRYPTO_ENCR_KEY1_REG			0x314
#define CRYPTO_ENCR_KEY2_REG			0x318
#define CRYPTO_ENCR_KEY3_REG			0x31C
#define CRYPTO_ENCR_KEY4_REG			0x320
#define CRYPTO_ENCR_KEY5_REG			0x324
#define CRYPTO_ENCR_KEY6_REG			0x328
#define CRYPTO_ENCR_KEY7_REG			0x32C

#define CRYPTO_ENCR_XTS_KEY0_REG		0x330
#define CRYPTO_ENCR_XTS_KEY1_REG		0x334
#define CRYPTO_ENCR_XTS_KEY2_REG		0x338
#define CRYPTO_ENCR_XTS_KEY3_REG		0x33C
#define CRYPTO_ENCR_XTS_KEY4_REG		0x340
#define CRYPTO_ENCR_XTS_KEY5_REG		0x344
#define CRYPTO_ENCR_XTS_KEY6_REG		0x348
#define CRYPTO_ENCR_XTS_KEY7_REG		0x34C

#define CRYPTO_CNTR0_IV0_REG			0x350
#define CRYPTO_CNTR1_IV1_REG			0x354
#define CRYPTO_CNTR2_IV2_REG			0x358
#define CRYPTO_CNTR3_IV3_REG			0x35C

#define CRYPTO_CNTR_MASK_REG			0x360

#define CRYPTO_ENCR_XTS_DU_SIZE_REG		0x364

#define CRYPTO_AUTH_SEG_CFG_REG			0x400
#define CRYPTO_AUTH_SEG_SIZE_REG		0x404
#define CRYPTO_AUTH_SEG_START_REG		0x408

#define CRYPTO_AUTH_KEY0_REG			0x410
#define CRYPTO_AUTH_KEY1_REG			0x414
#define CRYPTO_AUTH_KEY2_REG			0x418
#define CRYPTO_AUTH_KEY3_REG			0x41C
#define CRYPTO_AUTH_KEY4_REG			0x420
#define CRYPTO_AUTH_KEY5_REG			0x424
#define CRYPTO_AUTH_KEY6_REG			0x428
#define CRYPTO_AUTH_KEY7_REG			0x42C
#define CRYPTO_AUTH_KEY8_REG			0x430
#define CRYPTO_AUTH_KEY9_REG			0x434
#define CRYPTO_AUTH_KEY10_REG			0x438
#define CRYPTO_AUTH_KEY11_REG			0x43C
#define CRYPTO_AUTH_KEY12_REG			0x440
#define CRYPTO_AUTH_KEY13_REG			0x444
#define CRYPTO_AUTH_KEY14_REG			0x448
#define CRYPTO_AUTH_KEY15_REG			0x44C

#define CRYPTO_AUTH_IV0_REG			0x450
#define CRYPTO_AUTH_IV1_REG			0x454
#define CRYPTO_AUTH_IV2_REG			0x458
#define CRYPTO_AUTH_IV3_REG			0x45C
#define CRYPTO_AUTH_IV4_REG			0x460
#define CRYPTO_AUTH_IV5_REG			0x464
#define CRYPTO_AUTH_IV6_REG			0x468
#define CRYPTO_AUTH_IV7_REG			0x46C
#define CRYPTO_AUTH_IV8_REG			0x470
#define CRYPTO_AUTH_IV9_REG			0x474
#define CRYPTO_AUTH_IV10_REG			0x478
#define CRYPTO_AUTH_IV11_REG			0x47C
#define CRYPTO_AUTH_IV12_REG			0x480
#define CRYPTO_AUTH_IV13_REG			0x484
#define CRYPTO_AUTH_IV14_REG			0x488
#define CRYPTO_AUTH_IV15_REG			0x48C

#define CRYPTO_AUTH_INFO_NONCE0_REG		0x490
#define CRYPTO_AUTH_INFO_NONCE1_REG		0x494
#define CRYPTO_AUTH_INFO_NONCE2_REG		0x498
#define CRYPTO_AUTH_INFO_NONCE3_REG		0x49C

#define CRYPTO_AUTH_BYTECNT0_REG		0x4A0
#define CRYPTO_AUTH_BYTECNT1_REG		0x4A4
#define CRYPTO_AUTH_BYTECNT2_REG		0x4A8
#define CRYPTO_AUTH_BYTECNT3_REG		0x4AC

#define CRYPTO_AUTH_EXP_MAC0_REG		0x4B0
#define CRYPTO_AUTH_EXP_MAC1_REG		0x4B4
#define CRYPTO_AUTH_EXP_MAC2_REG		0x4B8
#define CRYPTO_AUTH_EXP_MAC3_REG		0x4BC
#define CRYPTO_AUTH_EXP_MAC4_REG		0x4C0
#define CRYPTO_AUTH_EXP_MAC5_REG		0x4C4
#define CRYPTO_AUTH_EXP_MAC6_REG		0x4C8
#define CRYPTO_AUTH_EXP_MAC7_REG		0x4CC

#define CRYPTO_CONFIG_REG			0x500
#define CRYPTO_SACR_REG				0x504
#define CRYPTO_DEBUG_REG			0x508

#define CRYPTO_DATA_SHADOW0			0x8000
#define CRYPTO_DATA_SHADOW8191			0x8FFC


/* Register bits */

#define CRYPTO_CORE_MAJOR_REV			4 /* bit 7-4 */
#define CRYPTO_CORE_MAJOR_REV_MASK		(0xF << CRYPTO_CORE_MAJOR_REV)
#define CRYPTO_CORE_MINOR_REV			0 /* bit 3-0 */
#define CRYPTO_CORE_MINOR_REV_MASK		(0xF << CRYPTO_CORE_MINOR_REV)
#define CRYPTO_CORE_REV_MASK			0xFF

/* status reg  */
#define CRYPTO_MAC_FAILED			25
#define CRYPTO_DOUT_SIZE_AVAIL			22 /* bit 24-22 */
#define CRYPTO_DOUT_SIZE_AVAIL_MASK		(0x7 << CRYPTO_DOUT_SIZE_AVAIL)
#define CRYPTO_DIN_SIZE_AVAIL			19 /* bit 21-19 */
#define CRYPTO_DIN_SIZE_AVAIL_MASK		(0x7 << CRYPTO_DIN_SIZE_AVAIL)
#define CRYPTO_ACCESS_VIOL			18
#define CRYPTO_SEG_CHNG_ERR			17
#define CRYPTO_CFH_CHNG_ERR			16
#define CRYPTO_DOUT_ERR				15
#define CRYPTO_DIN_ERR				14
#define CRYPTO_LOCKED				13
#define CRYPTO_CRYPTO_STATE			10 /* bit 12-10 */
#define CRYPTO_CRYPTO_STATE_MASK		(0x7 << CRYPTO_CRYPTO_STATE)
#define CRYPTO_ENCR_BUSY			9
#define CRYPTO_AUTH_BUSY			8
#define CRYPTO_DOUT_INTR			7
#define CRYPTO_DIN_INTR				6
#define CRYPTO_OP_DONE_INTR			5
#define CRYPTO_ERR_INTR				4
#define CRYPTO_DOUT_RDY				3
#define CRYPTO_DIN_RDY				2
#define CRYPTO_OPERATION_DONE			1
#define CRYPTO_SW_ERR				0

/* config reg */
#define CRYPTO_REQ_SIZE				30 /* bit 31-30 */
#define CRYPTO_REQ_SIZE_MASK			(0x3 << CRYPTO_REQ_SIZE)
#define CRYPTO_REQ_SIZE_ENUM_16_BYTES	0
#define CRYPTO_REQ_SIZE_ENUM_32_BYTES	1
#define CRYPTO_REQ_SIZE_ENUM_64_BYTES	2

#define CRYPTO_MAX_QUEUED_REQ			27 /* bit 29-27 */
#define CRYPTO_MAX_QUEUED_REQ_MASK		(0x7 << CRYPTO_MAX_QUEUED_REQ)
#define CRYPTO_ENUM1_QUEUED_REQS		0
#define CRYPTO_ENUM2_QUEUED_REQS		1
#define CRYPTO_ENUM3_QUEUED_REQS		2
#define CRYPTO_ENUM4_QUEUED_REQS		3

#define CRYPTO_FIFO_THRESHOLD			24 /* bit 26-24 */
#define CRYPTO_FIFO_THRESHOLD_MASK		(0x7 << CRYPTO_FIFO_THRESHOLD)
#define CRYPTO_FIFO_ENUM_16_BYTES		0
#define CRYPTO_FIFO_ENUM_32_BYTES		1
#define CRYPTO_FIFO_ENUM_48_BYTES		2
#define CRYPTO_FIFO_ENUM_64_BYTES		3

#define CRYPTO_IRQ_ENABLES			20	/* bit 23-20 */
#define CRYPTO_IRQ_ENABLES_MASK			(0xF << CRYPTO_IRQ_ENABLES)

#define CRYPTO_ACR_EN				18
#define CRYPTO_BAM_MODE				17
#define CRYPTO_LITTLE_ENDIAN_MODE		16
#define CRYPTO_HIGH_SPD_OUT_EN_N		14
#define CRYPTO_HIGH_SPD_IN_EN_N			13
#define CRYPTO_DBG_EN				12

#define CRYPTO_DBG_SEL				7 /* bit 11:7 */
#define CRYPTO_DBG_SEL_MASK			(0x1F << CRYPTO_DBG_SEL)

#define CRYPTO_MASK_DOUT_INTR			6
#define CRYPTO_MASK_DIN_INTR			5
#define CRYPTO_MASK_OP_DONE_INTR		4
#define CRYPTO_MASK_ERR_INTR			3
#define CRYPTO_AUTO_SHUTDOWN_EN			2
#define CRYPTO_CLK_EN_N				1

/* auth_seg_cfg reg */
#define CRYPTO_COMP_EXP_MAC			20
#define CRYPTO_COMP_EXP_MAC_DISABLED		0
#define CRYPTO_COMP_EXP_MAC_ENABLED		1

#define CRYPTO_F9_DIRECTION			19
#define CRYPTO_F9_DIRECTION_UPLINK		0
#define CRYPTO_F9_DIRECTION_DOWNLINK		1

#define CRYPTO_AUTH_NONCE_NUM_WORDS		16
#define CRYPTO_AUTH_NONCE_NUM_WORDS_MASK \
					(0x7 << CRYPTO_AUTH_NONCE_NUM_WORDS)

#define CRYPTO_USE_HW_KEY_AUTH			15

#define CRYPTO_LAST				14

#define CRYPTO_AUTH_POS				12 /* bit 13 .. 12*/
#define CRYPTO_AUTH_POS_MASK			(0x3 << CRYPTO_AUTH_POS)
#define CRYPTO_AUTH_POS_BEFORE			0
#define CRYPTO_AUTH_POS_AFTER			1

#define CRYPTO_AUTH_SIZE			9 /* bits 11 .. 9*/
#define CRYPTO_AUTH_SIZE_MASK			(0x7 << CRYPTO_AUTH_SIZE)
#define CRYPTO_AUTH_SIZE_SHA1			0
#define CRYPTO_AUTH_SIZE_SHA256			1
#define CRYPTO_AUTH_SIZE_ENUM_4_BYTES		0
#define CRYPTO_AUTH_SIZE_ENUM_6_BYTES		1
#define CRYPTO_AUTH_SIZE_ENUM_8_BYTES		2
#define CRYPTO_AUTH_SIZE_ENUM_10_BYTES		3
#define CRYPTO_AUTH_SIZE_ENUM_12_BYTES		4
#define CRYPTO_AUTH_SIZE_ENUM_14_BYTES		5
#define CRYPTO_AUTH_SIZE_ENUM_16_BYTES		6

#define CRYPTO_AUTH_MODE			6 /* bit 8 .. 6*/
#define CRYPTO_AUTH_MODE_MASK			(0x7 << CRYPTO_AUTH_MODE)
#define CRYPTO_AUTH_MODE_HASH			0
#define CRYPTO_AUTH_MODE_HMAC			1
#define CRYPTO_AUTH_MODE_CCM			0
#define CRYPTO_AUTH_MODE_CMAC			1

#define CRYPTO_AUTH_KEY_SIZE			3
#define CRYPTO_AUTH_KEY_SIZE_MASK		(0x7 << CRYPTO_AUTH_KEY_SIZE)
#define CRYPTO_AUTH_KEY_SZ_AES128		0
#define CRYPTO_AUTH_KEY_SZ_AES256		2

#define CRYPTO_AUTH_ALG				0 /* bit 2 .. 0*/
#define CRYPTO_AUTH_ALG_MASK			7
#define CRYPTO_AUTH_ALG_NONE			0
#define CRYPTO_AUTH_ALG_SHA			1
#define CRYPTO_AUTH_ALG_AES			2
#define CRYPTO_AUTH_ALG_KASUMI			3
#define CRYPTO_AUTH_ALG_SNOW3G			4

/* encr_xts_du_size reg */
#define CRYPTO_ENCR_XTS_DU_SIZE			0 /* bit 19-0  */
#define CRYPTO_ENCR_XTS_DU_SIZE_MASK		0xfffff

/* encr_seg_cfg reg */
#define CRYPTO_F8_KEYSTREAM_ENABLE		15
#define CRYPTO_F8_KEYSTREAM_DISABLED		0
#define CRYPTO_F8_KEYSTREAM_ENABLED		1

#define CRYPTO_F8_DIRECTION			14
#define CRYPTO_F8_DIRECTION_UPLINK		0
#define CRYPTO_F8_DIRECTION_DOWNLINK		1

#define CRYPTO_USE_HW_KEY_ENCR			13
#define CRYPTO_USE_HW_KEY_REG			0
#define CRYPTO_USE_HW_KEY			1

#define CRYPTO_CNTR_ALG				11 /* bit 12-11 */
#define CRYPTO_CNTR_ALG_MASK			(3 << CRYPTO_CNTR_ALG)
#define CRYPTO_CNTR_ALG_NIST			0

#define CRYPTO_ENCODE				10

#define CRYPTO_ENCR_MODE			6 /* bit 9-6 */
#define CRYPTO_ENCR_MODE_MASK			(0xF << CRYPTO_ENCR_MODE)
/* only valid when AES */
#define CRYPTO_ENCR_MODE_ECB			0
#define CRYPTO_ENCR_MODE_CBC			1
#define CRYPTO_ENCR_MODE_CTR			2
#define CRYPTO_ENCR_MODE_XTS			3
#define CRYPTO_ENCR_MODE_CCM			4

#define CRYPTO_ENCR_KEY_SZ			3 /* bit 5-3 */
#define CRYPTO_ENCR_KEY_SZ_MASK			(7 << CRYPTO_ENCR_KEY_SZ)
#define CRYPTO_ENCR_KEY_SZ_DES			0
#define CRYPTO_ENCR_KEY_SZ_3DES			1
#define CRYPTO_ENCR_KEY_SZ_AES128		0
#define CRYPTO_ENCR_KEY_SZ_AES256		2
#define CRYPTO_ENCR_KEY_SZ_UEA1			0
#define CRYPTO_ENCR_KEY_SZ_UEA2			1

#define CRYPTO_ENCR_ALG				0 /* bit 2-0 */
#define CRYPTO_ENCR_ALG_MASK			(7 << CRYPTO_ENCR_ALG)
#define CRYPTO_ENCR_ALG_NONE			0
#define CRYPTO_ENCR_ALG_DES			1
#define CRYPTO_ENCR_ALG_AES			2
#define CRYPTO_ENCR_ALG_KASUMI			3
#define CRYPTO_ENCR_ALG_SNOW_3G			5

/* goproc reg */
#define CRYPTO_GO				0
#define CRYPTO_CLR_CNTXT			1

/* engines_avail */
#define CRYPTO_ENCR_AES_SEL			0
#define CRYPTO_DES_SEL				3
#define CRYPTO_ENCR_SNOW3G_SEL			4
#define CRYPTO_ENCR_KASUMI_SEL			5
#define CRYPTO_SHA_SEL				6
#define CRYPTO_SHA512_SEL			7
#define CRYPTO_AUTH_AES_SEL			8
#define CRYPTO_AUTH_SNOW3G_SEL			9
#define CRYPTO_AUTH_KASUMI_SEL			10
#define CRYPTO_BAM_SEL				11

#endif /* _DRIVERS_CRYPTO_MSM_QCRYPTOHW_40_H_ */
