#ifndef __ASM_SH7723_H__
#define __ASM_SH7723_H__

/* Boot Mode Pins:
 *
 * MD0: CPG - Clock Mode 0->3
 * MD1: CPG - Clock Mode 0->3
 * MD2: CPG - Reserved (L: Normal operation)
 * MD3: BSC - Area0 Bus Width (16/32-bit) [CS0BCR.9,10]
 * MD5: BSC - Endian Mode (L: Big, H: Little) [CMNCR.3]
 * MD8: Test Mode
 */

/* Pin Function Controller:
 * GPIO_FN_xx - GPIO used to select pin function
 * GPIO_Pxx - GPIO mapped to real I/O pin on CPU
 */
enum {
	/* PTA */
	GPIO_PTA7, GPIO_PTA6, GPIO_PTA5, GPIO_PTA4,
	GPIO_PTA3, GPIO_PTA2, GPIO_PTA1, GPIO_PTA0,

	/* PTB */
	GPIO_PTB7, GPIO_PTB6, GPIO_PTB5, GPIO_PTB4,
	GPIO_PTB3, GPIO_PTB2, GPIO_PTB1, GPIO_PTB0,

	/* PTC */
	GPIO_PTC7, GPIO_PTC6, GPIO_PTC5, GPIO_PTC4,
	GPIO_PTC3, GPIO_PTC2, GPIO_PTC1, GPIO_PTC0,

	/* PTD */
	GPIO_PTD7, GPIO_PTD6, GPIO_PTD5, GPIO_PTD4,
	GPIO_PTD3, GPIO_PTD2, GPIO_PTD1, GPIO_PTD0,

	/* PTE */
	GPIO_PTE5, GPIO_PTE4, GPIO_PTE3, GPIO_PTE2,
	GPIO_PTE1, GPIO_PTE0,

	/* PTF */
	GPIO_PTF7, GPIO_PTF6, GPIO_PTF5, GPIO_PTF4,
	GPIO_PTF3, GPIO_PTF2, GPIO_PTF1, GPIO_PTF0,

	/* PTG */
	GPIO_PTG5, GPIO_PTG4, GPIO_PTG3, GPIO_PTG2,
	GPIO_PTG1, GPIO_PTG0,

	/* PTH */
	GPIO_PTH7, GPIO_PTH6, GPIO_PTH5, GPIO_PTH4,
	GPIO_PTH3, GPIO_PTH2, GPIO_PTH1, GPIO_PTH0,

	/* PTJ */
	GPIO_PTJ7, GPIO_PTJ5, GPIO_PTJ3, GPIO_PTJ2,
	GPIO_PTJ1, GPIO_PTJ0,

	/* PTK */
	GPIO_PTK7, GPIO_PTK6, GPIO_PTK5, GPIO_PTK4,
	GPIO_PTK3, GPIO_PTK2, GPIO_PTK1, GPIO_PTK0,

	/* PTL */
	GPIO_PTL7, GPIO_PTL6, GPIO_PTL5, GPIO_PTL4,
	GPIO_PTL3, GPIO_PTL2, GPIO_PTL1, GPIO_PTL0,

	/* PTM */
	GPIO_PTM7, GPIO_PTM6, GPIO_PTM5, GPIO_PTM4,
	GPIO_PTM3, GPIO_PTM2, GPIO_PTM1, GPIO_PTM0,

	/* PTN */
	GPIO_PTN7, GPIO_PTN6, GPIO_PTN5, GPIO_PTN4,
	GPIO_PTN3, GPIO_PTN2, GPIO_PTN1, GPIO_PTN0,

	/* PTQ */
	GPIO_PTQ3, GPIO_PTQ2, GPIO_PTQ1, GPIO_PTQ0,

	/* PTR */
	GPIO_PTR7, GPIO_PTR6, GPIO_PTR5, GPIO_PTR4,
	GPIO_PTR3, GPIO_PTR2, GPIO_PTR1, GPIO_PTR0,

	/* PTS */
	GPIO_PTS7, GPIO_PTS6, GPIO_PTS5, GPIO_PTS4,
	GPIO_PTS3, GPIO_PTS2, GPIO_PTS1, GPIO_PTS0,

	/* PTT */
	GPIO_PTT5, GPIO_PTT4, GPIO_PTT3, GPIO_PTT2,
	GPIO_PTT1, GPIO_PTT0,

	/* PTU */
	GPIO_PTU5, GPIO_PTU4, GPIO_PTU3, GPIO_PTU2,
	GPIO_PTU1, GPIO_PTU0,

	/* PTV */
	GPIO_PTV7, GPIO_PTV6, GPIO_PTV5, GPIO_PTV4,
	GPIO_PTV3, GPIO_PTV2, GPIO_PTV1, GPIO_PTV0,

	/* PTW */
	GPIO_PTW7, GPIO_PTW6, GPIO_PTW5, GPIO_PTW4,
	GPIO_PTW3, GPIO_PTW2, GPIO_PTW1, GPIO_PTW0,

	/* PTX */
	GPIO_PTX7, GPIO_PTX6, GPIO_PTX5, GPIO_PTX4,
	GPIO_PTX3, GPIO_PTX2, GPIO_PTX1, GPIO_PTX0,

	/* PTY */
	GPIO_PTY7, GPIO_PTY6, GPIO_PTY5, GPIO_PTY4,
	GPIO_PTY3, GPIO_PTY2, GPIO_PTY1, GPIO_PTY0,

	/* PTZ */
	GPIO_PTZ7, GPIO_PTZ6, GPIO_PTZ5, GPIO_PTZ4,
	GPIO_PTZ3, GPIO_PTZ2, GPIO_PTZ1, GPIO_PTZ0,

	/* SCIF0 (SCIF: 3 pin PTT/PTU) */
	GPIO_FN_SCIF0_PTT_TXD, GPIO_FN_SCIF0_PTT_RXD, GPIO_FN_SCIF0_PTT_SCK,
	GPIO_FN_SCIF0_PTU_TXD, GPIO_FN_SCIF0_PTU_RXD, GPIO_FN_SCIF0_PTU_SCK,

	/* SCIF1 (SCIF: 3 pin PTS/PTV) */
	GPIO_FN_SCIF1_PTS_TXD, GPIO_FN_SCIF1_PTS_RXD, GPIO_FN_SCIF1_PTS_SCK,
	GPIO_FN_SCIF1_PTV_TXD, GPIO_FN_SCIF1_PTV_RXD, GPIO_FN_SCIF1_PTV_SCK,

	/* SCIF2 (SCIF: 3 pin PTT/PTU) */
	GPIO_FN_SCIF2_PTT_TXD, GPIO_FN_SCIF2_PTT_RXD, GPIO_FN_SCIF2_PTT_SCK,
	GPIO_FN_SCIF2_PTU_TXD, GPIO_FN_SCIF2_PTU_RXD, GPIO_FN_SCIF2_PTU_SCK,

	/* SCIF3 (SCIFA: 5 pin PTS/PTV) */
	GPIO_FN_SCIF3_PTS_TXD, GPIO_FN_SCIF3_PTS_RXD, GPIO_FN_SCIF3_PTS_SCK,
	GPIO_FN_SCIF3_PTS_RTS, GPIO_FN_SCIF3_PTS_CTS,
	GPIO_FN_SCIF3_PTV_TXD, GPIO_FN_SCIF3_PTV_RXD, GPIO_FN_SCIF3_PTV_SCK,
	GPIO_FN_SCIF3_PTV_RTS, GPIO_FN_SCIF3_PTV_CTS,

	/* SCIF4 (SCIFA: 3 pin PTE/PTN) */
	GPIO_FN_SCIF4_PTE_TXD, GPIO_FN_SCIF4_PTE_RXD, GPIO_FN_SCIF4_PTE_SCK,
	GPIO_FN_SCIF4_PTN_TXD, GPIO_FN_SCIF4_PTN_RXD, GPIO_FN_SCIF4_PTN_SCK,

	/* SCIF5 (SCIFA: 3 pin PTE/PTN) */
	GPIO_FN_SCIF5_PTE_TXD, GPIO_FN_SCIF5_PTE_RXD, GPIO_FN_SCIF5_PTE_SCK,
	GPIO_FN_SCIF5_PTN_TXD, GPIO_FN_SCIF5_PTN_RXD, GPIO_FN_SCIF5_PTN_SCK,

	/* CEU */
	GPIO_FN_VIO_D15, GPIO_FN_VIO_D14, GPIO_FN_VIO_D13, GPIO_FN_VIO_D12,
	GPIO_FN_VIO_D11, GPIO_FN_VIO_D10, GPIO_FN_VIO_D9, GPIO_FN_VIO_D8,
	GPIO_FN_VIO_D7, GPIO_FN_VIO_D6, GPIO_FN_VIO_D5, GPIO_FN_VIO_D4,
	GPIO_FN_VIO_D3, GPIO_FN_VIO_D2, GPIO_FN_VIO_D1, GPIO_FN_VIO_D0,
	GPIO_FN_VIO_FLD, GPIO_FN_VIO_CKO,
	GPIO_FN_VIO_VD1, GPIO_FN_VIO_HD1, GPIO_FN_VIO_CLK1,
	GPIO_FN_VIO_VD2, GPIO_FN_VIO_HD2, GPIO_FN_VIO_CLK2,

	/* LCDC */
	GPIO_FN_LCDD23, GPIO_FN_LCDD22, GPIO_FN_LCDD21, GPIO_FN_LCDD20,
	GPIO_FN_LCDD19, GPIO_FN_LCDD18, GPIO_FN_LCDD17, GPIO_FN_LCDD16,
	GPIO_FN_LCDD15, GPIO_FN_LCDD14, GPIO_FN_LCDD13, GPIO_FN_LCDD12,
	GPIO_FN_LCDD11, GPIO_FN_LCDD10, GPIO_FN_LCDD9, GPIO_FN_LCDD8,
	GPIO_FN_LCDD7, GPIO_FN_LCDD6, GPIO_FN_LCDD5, GPIO_FN_LCDD4,
	GPIO_FN_LCDD3, GPIO_FN_LCDD2, GPIO_FN_LCDD1, GPIO_FN_LCDD0,
	GPIO_FN_LCDLCLK_PTR, GPIO_FN_LCDLCLK_PTW,
	/* Main LCD */
	GPIO_FN_LCDDON, GPIO_FN_LCDVCPWC, GPIO_FN_LCDVEPWC, GPIO_FN_LCDVSYN,
	/* Main LCD - RGB Mode */
	GPIO_FN_LCDDCK, GPIO_FN_LCDHSYN, GPIO_FN_LCDDISP,
	/* Main LCD - SYS Mode */
	GPIO_FN_LCDRS, GPIO_FN_LCDCS, GPIO_FN_LCDWR, GPIO_FN_LCDRD,

	/* IRQ */
	GPIO_FN_IRQ0, GPIO_FN_IRQ1, GPIO_FN_IRQ2, GPIO_FN_IRQ3,
	GPIO_FN_IRQ4, GPIO_FN_IRQ5, GPIO_FN_IRQ6, GPIO_FN_IRQ7,

	/* AUD */
	GPIO_FN_AUDATA3, GPIO_FN_AUDATA2, GPIO_FN_AUDATA1, GPIO_FN_AUDATA0,
	GPIO_FN_AUDCK, GPIO_FN_AUDSYNC,

	/* SDHI0 (PTD) */
	GPIO_FN_SDHI0CD_PTD, GPIO_FN_SDHI0WP_PTD,
	GPIO_FN_SDHI0D3_PTD, GPIO_FN_SDHI0D2_PTD,
	GPIO_FN_SDHI0D1_PTD, GPIO_FN_SDHI0D0_PTD,
	GPIO_FN_SDHI0CMD_PTD, GPIO_FN_SDHI0CLK_PTD,

	/* SDHI0 (PTS) */
	GPIO_FN_SDHI0CD_PTS, GPIO_FN_SDHI0WP_PTS,
	GPIO_FN_SDHI0D3_PTS, GPIO_FN_SDHI0D2_PTS,
	GPIO_FN_SDHI0D1_PTS, GPIO_FN_SDHI0D0_PTS,
	GPIO_FN_SDHI0CMD_PTS, GPIO_FN_SDHI0CLK_PTS,

	/* SDHI1 */
	GPIO_FN_SDHI1CD, GPIO_FN_SDHI1WP, GPIO_FN_SDHI1D3, GPIO_FN_SDHI1D2,
	GPIO_FN_SDHI1D1, GPIO_FN_SDHI1D0, GPIO_FN_SDHI1CMD, GPIO_FN_SDHI1CLK,

	/* SIUA */
	GPIO_FN_SIUAFCK, GPIO_FN_SIUAILR, GPIO_FN_SIUAIBT, GPIO_FN_SIUAISLD,
	GPIO_FN_SIUAOLR, GPIO_FN_SIUAOBT, GPIO_FN_SIUAOSLD, GPIO_FN_SIUAMCK,
	GPIO_FN_SIUAISPD, GPIO_FN_SIUOSPD,

	/* SIUB */
	GPIO_FN_SIUBFCK, GPIO_FN_SIUBILR, GPIO_FN_SIUBIBT, GPIO_FN_SIUBISLD,
	GPIO_FN_SIUBOLR, GPIO_FN_SIUBOBT, GPIO_FN_SIUBOSLD, GPIO_FN_SIUBMCK,

	/* IRDA */
	GPIO_FN_IRDA_IN, GPIO_FN_IRDA_OUT,

	/* VOU */
	GPIO_FN_DV_CLKI, GPIO_FN_DV_CLK, GPIO_FN_DV_HSYNC, GPIO_FN_DV_VSYNC,
	GPIO_FN_DV_D15, GPIO_FN_DV_D14, GPIO_FN_DV_D13, GPIO_FN_DV_D12,
	GPIO_FN_DV_D11, GPIO_FN_DV_D10, GPIO_FN_DV_D9, GPIO_FN_DV_D8,
	GPIO_FN_DV_D7, GPIO_FN_DV_D6, GPIO_FN_DV_D5, GPIO_FN_DV_D4,
	GPIO_FN_DV_D3, GPIO_FN_DV_D2, GPIO_FN_DV_D1, GPIO_FN_DV_D0,

	/* KEYSC */
	GPIO_FN_KEYIN0, GPIO_FN_KEYIN1, GPIO_FN_KEYIN2, GPIO_FN_KEYIN3,
	GPIO_FN_KEYIN4, GPIO_FN_KEYOUT0, GPIO_FN_KEYOUT1, GPIO_FN_KEYOUT2,
	GPIO_FN_KEYOUT3, GPIO_FN_KEYOUT4_IN6, GPIO_FN_KEYOUT5_IN5,

	/* MSIOF0 (PTF) */
	GPIO_FN_MSIOF0_PTF_TXD, GPIO_FN_MSIOF0_PTF_RXD, GPIO_FN_MSIOF0_PTF_MCK,
	GPIO_FN_MSIOF0_PTF_TSYNC, GPIO_FN_MSIOF0_PTF_TSCK,
	GPIO_FN_MSIOF0_PTF_RSYNC, GPIO_FN_MSIOF0_PTF_RSCK,
	GPIO_FN_MSIOF0_PTF_SS1, GPIO_FN_MSIOF0_PTF_SS2,

	/* MSIOF0 (PTT+PTX) */
	GPIO_FN_MSIOF0_PTT_TXD, GPIO_FN_MSIOF0_PTT_RXD, GPIO_FN_MSIOF0_PTX_MCK,
	GPIO_FN_MSIOF0_PTT_TSYNC, GPIO_FN_MSIOF0_PTT_TSCK,
	GPIO_FN_MSIOF0_PTT_RSYNC, GPIO_FN_MSIOF0_PTT_RSCK,
	GPIO_FN_MSIOF0_PTT_SS1, GPIO_FN_MSIOF0_PTT_SS2,

	/* MSIOF1 */
	GPIO_FN_MSIOF1_TXD, GPIO_FN_MSIOF1_RXD, GPIO_FN_MSIOF1_MCK,
	GPIO_FN_MSIOF1_TSYNC, GPIO_FN_MSIOF1_TSCK,
	GPIO_FN_MSIOF1_RSYNC, GPIO_FN_MSIOF1_RSCK,
	GPIO_FN_MSIOF1_SS1, GPIO_FN_MSIOF1_SS2,

	/* TSIF */
	GPIO_FN_TS0_SDAT, GPIO_FN_TS0_SCK, GPIO_FN_TS0_SDEN, GPIO_FN_TS0_SPSYNC,

	/* FLCTL */
	GPIO_FN_FCE, GPIO_FN_NAF7, GPIO_FN_NAF6, GPIO_FN_NAF5, GPIO_FN_NAF4,
	GPIO_FN_NAF3, GPIO_FN_NAF2, GPIO_FN_NAF1, GPIO_FN_NAF0, GPIO_FN_FCDE,
	GPIO_FN_FOE, GPIO_FN_FSC, GPIO_FN_FWE, GPIO_FN_FRB,

	/* DMAC */
	GPIO_FN_DACK1, GPIO_FN_DREQ1, GPIO_FN_DACK0, GPIO_FN_DREQ0,

	/* ADC */
	GPIO_FN_AN3, GPIO_FN_AN2, GPIO_FN_AN1, GPIO_FN_AN0, GPIO_FN_ADTRG,

	/* CPG */
	GPIO_FN_STATUS0, GPIO_FN_PDSTATUS,

	/* TPU */
	GPIO_FN_TPUTO3, GPIO_FN_TPUTO2, GPIO_FN_TPUTO1, GPIO_FN_TPUTO0,

	/* BSC */
	GPIO_FN_D31, GPIO_FN_D30, GPIO_FN_D29, GPIO_FN_D28,
	GPIO_FN_D27, GPIO_FN_D26, GPIO_FN_D25, GPIO_FN_D24,
	GPIO_FN_D23, GPIO_FN_D22, GPIO_FN_D21, GPIO_FN_D20,
	GPIO_FN_D19, GPIO_FN_D18, GPIO_FN_D17, GPIO_FN_D16,
	GPIO_FN_IOIS16, GPIO_FN_WAIT, GPIO_FN_BS,
	GPIO_FN_A25, GPIO_FN_A24, GPIO_FN_A23, GPIO_FN_A22,
	GPIO_FN_CS6B_CE1B, GPIO_FN_CS6A_CE2B,
	GPIO_FN_CS5B_CE1A, GPIO_FN_CS5A_CE2A,
	GPIO_FN_WE3_ICIOWR, GPIO_FN_WE2_ICIORD,

	/* ATAPI */
	GPIO_FN_IDED15, GPIO_FN_IDED14, GPIO_FN_IDED13, GPIO_FN_IDED12,
	GPIO_FN_IDED11, GPIO_FN_IDED10, GPIO_FN_IDED9, GPIO_FN_IDED8,
	GPIO_FN_IDED7, GPIO_FN_IDED6, GPIO_FN_IDED5, GPIO_FN_IDED4,
	GPIO_FN_IDED3, GPIO_FN_IDED2, GPIO_FN_IDED1, GPIO_FN_IDED0,
	GPIO_FN_DIRECTION, GPIO_FN_EXBUF_ENB, GPIO_FN_IDERST, GPIO_FN_IODACK,
	GPIO_FN_IODREQ, GPIO_FN_IDEIORDY, GPIO_FN_IDEINT, GPIO_FN_IDEIOWR,
	GPIO_FN_IDEIORD, GPIO_FN_IDECS1, GPIO_FN_IDECS0, GPIO_FN_IDEA2,
	GPIO_FN_IDEA1, GPIO_FN_IDEA0,
};

enum {
<<<<<<< HEAD
	HWBLK_UNKNOWN = 0,
	HWBLK_TLB, HWBLK_IC, HWBLK_OC, HWBLK_L2C, HWBLK_ILMEM, HWBLK_FPU,
	HWBLK_INTC, HWBLK_DMAC0, HWBLK_SHYWAY,
	HWBLK_HUDI, HWBLK_DBG, HWBLK_UBC, HWBLK_SUBC,
=======
	HWBLK_TLB, HWBLK_IC, HWBLK_OC, HWBLK_L2C, HWBLK_ILMEM, HWBLK_FPU,
	HWBLK_INTC, HWBLK_DMAC0, HWBLK_SHYWAY,
	HWBLK_HUDI, HWBLK_UBC,
>>>>>>> cm-10.0
	HWBLK_TMU0, HWBLK_CMT, HWBLK_RWDT, HWBLK_DMAC1, HWBLK_TMU1,
	HWBLK_FLCTL,
	HWBLK_SCIF0, HWBLK_SCIF1, HWBLK_SCIF2,
	HWBLK_SCIF3, HWBLK_SCIF4, HWBLK_SCIF5,
	HWBLK_MSIOF0, HWBLK_MSIOF1, HWBLK_MERAM, HWBLK_IIC, HWBLK_RTC,
	HWBLK_ATAPI, HWBLK_ADC, HWBLK_TPU, HWBLK_IRDA, HWBLK_TSIF, HWBLK_ICB,
	HWBLK_SDHI0, HWBLK_SDHI1, HWBLK_KEYSC, HWBLK_USB,
	HWBLK_2DG, HWBLK_SIU, HWBLK_VEU2H1, HWBLK_VOU, HWBLK_BEU, HWBLK_CEU,
	HWBLK_VEU2H0, HWBLK_VPU, HWBLK_LCDC,
	HWBLK_NR,
};

#endif /* __ASM_SH7723_H__ */
