/* $Id: mic.c,v 1.12.2.4 2004/01/13 23:48:39 keil Exp $
 *
 * low level stuff for mic cards
 *
 * Author       Stephan von Krawczynski
 * Copyright    by Stephan von Krawczynski <skraw@ithnet.com>
<<<<<<< HEAD
 * 
=======
 *
>>>>>>> cm-10.0
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#include <linux/init.h>
#include "hisax.h"
#include "isac.h"
#include "hscx.h"
#include "isdnl1.h"

static const char *mic_revision = "$Revision: 1.12.2.4 $";

<<<<<<< HEAD
#define byteout(addr,val) outb(val,addr)
=======
#define byteout(addr, val) outb(val, addr)
>>>>>>> cm-10.0
#define bytein(addr) inb(addr)

#define MIC_ISAC	2
#define MIC_HSCX	1
#define MIC_ADR		7

/* CARD_ADR (Write) */
#define MIC_RESET      0x3	/* same as DOS driver */

static inline u_char
readreg(unsigned int ale, unsigned int adr, u_char off)
{
	register u_char ret;

	byteout(ale, off);
	ret = bytein(adr);
	return (ret);
}

static inline void
<<<<<<< HEAD
readfifo(unsigned int ale, unsigned int adr, u_char off, u_char * data, int size)
=======
readfifo(unsigned int ale, unsigned int adr, u_char off, u_char *data, int size)
>>>>>>> cm-10.0
{
	byteout(ale, off);
	insb(adr, data, size);
}


static inline void
writereg(unsigned int ale, unsigned int adr, u_char off, u_char data)
{
	byteout(ale, off);
	byteout(adr, data);
}

static inline void
<<<<<<< HEAD
writefifo(unsigned int ale, unsigned int adr, u_char off, u_char * data, int size)
=======
writefifo(unsigned int ale, unsigned int adr, u_char off, u_char *data, int size)
>>>>>>> cm-10.0
{
	byteout(ale, off);
	outsb(adr, data, size);
}

/* Interface functions */

static u_char
ReadISAC(struct IsdnCardState *cs, u_char offset)
{
	return (readreg(cs->hw.mic.adr, cs->hw.mic.isac, offset));
}

static void
WriteISAC(struct IsdnCardState *cs, u_char offset, u_char value)
{
	writereg(cs->hw.mic.adr, cs->hw.mic.isac, offset, value);
}

static void
<<<<<<< HEAD
ReadISACfifo(struct IsdnCardState *cs, u_char * data, int size)
=======
ReadISACfifo(struct IsdnCardState *cs, u_char *data, int size)
>>>>>>> cm-10.0
{
	readfifo(cs->hw.mic.adr, cs->hw.mic.isac, 0, data, size);
}

static void
<<<<<<< HEAD
WriteISACfifo(struct IsdnCardState *cs, u_char * data, int size)
=======
WriteISACfifo(struct IsdnCardState *cs, u_char *data, int size)
>>>>>>> cm-10.0
{
	writefifo(cs->hw.mic.adr, cs->hw.mic.isac, 0, data, size);
}

static u_char
ReadHSCX(struct IsdnCardState *cs, int hscx, u_char offset)
{
	return (readreg(cs->hw.mic.adr,
			cs->hw.mic.hscx, offset + (hscx ? 0x40 : 0)));
}

static void
WriteHSCX(struct IsdnCardState *cs, int hscx, u_char offset, u_char value)
{
	writereg(cs->hw.mic.adr,
		 cs->hw.mic.hscx, offset + (hscx ? 0x40 : 0), value);
}

/*
 * fast interrupt HSCX stuff goes here
 */

<<<<<<< HEAD
#define READHSCX(cs, nr, reg) readreg(cs->hw.mic.adr, \
		cs->hw.mic.hscx, reg + (nr ? 0x40 : 0))
#define WRITEHSCX(cs, nr, reg, data) writereg(cs->hw.mic.adr, \
		cs->hw.mic.hscx, reg + (nr ? 0x40 : 0), data)

#define READHSCXFIFO(cs, nr, ptr, cnt) readfifo(cs->hw.mic.adr, \
		cs->hw.mic.hscx, (nr ? 0x40 : 0), ptr, cnt)

#define WRITEHSCXFIFO(cs, nr, ptr, cnt) writefifo(cs->hw.mic.adr, \
		cs->hw.mic.hscx, (nr ? 0x40 : 0), ptr, cnt)
=======
#define READHSCX(cs, nr, reg) readreg(cs->hw.mic.adr,			\
				      cs->hw.mic.hscx, reg + (nr ? 0x40 : 0))
#define WRITEHSCX(cs, nr, reg, data) writereg(cs->hw.mic.adr,		\
					      cs->hw.mic.hscx, reg + (nr ? 0x40 : 0), data)

#define READHSCXFIFO(cs, nr, ptr, cnt) readfifo(cs->hw.mic.adr,		\
						cs->hw.mic.hscx, (nr ? 0x40 : 0), ptr, cnt)

#define WRITEHSCXFIFO(cs, nr, ptr, cnt) writefifo(cs->hw.mic.adr,	\
						  cs->hw.mic.hscx, (nr ? 0x40 : 0), ptr, cnt)
>>>>>>> cm-10.0

#include "hscx_irq.c"

static irqreturn_t
mic_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char val;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	val = readreg(cs->hw.mic.adr, cs->hw.mic.hscx, HSCX_ISTA + 0x40);
<<<<<<< HEAD
      Start_HSCX:
	if (val)
		hscx_int_main(cs, val);
	val = readreg(cs->hw.mic.adr, cs->hw.mic.isac, ISAC_ISTA);
      Start_ISAC:
=======
Start_HSCX:
	if (val)
		hscx_int_main(cs, val);
	val = readreg(cs->hw.mic.adr, cs->hw.mic.isac, ISAC_ISTA);
Start_ISAC:
>>>>>>> cm-10.0
	if (val)
		isac_interrupt(cs, val);
	val = readreg(cs->hw.mic.adr, cs->hw.mic.hscx, HSCX_ISTA + 0x40);
	if (val) {
		if (cs->debug & L1_DEB_HSCX)
			debugl1(cs, "HSCX IntStat after IntRoutine");
		goto Start_HSCX;
	}
	val = readreg(cs->hw.mic.adr, cs->hw.mic.isac, ISAC_ISTA);
	if (val) {
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "ISAC IntStat after IntRoutine");
		goto Start_ISAC;
	}
	writereg(cs->hw.mic.adr, cs->hw.mic.hscx, HSCX_MASK, 0xFF);
	writereg(cs->hw.mic.adr, cs->hw.mic.hscx, HSCX_MASK + 0x40, 0xFF);
	writereg(cs->hw.mic.adr, cs->hw.mic.isac, ISAC_MASK, 0xFF);
	writereg(cs->hw.mic.adr, cs->hw.mic.isac, ISAC_MASK, 0x0);
	writereg(cs->hw.mic.adr, cs->hw.mic.hscx, HSCX_MASK, 0x0);
	writereg(cs->hw.mic.adr, cs->hw.mic.hscx, HSCX_MASK + 0x40, 0x0);
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}

static void
release_io_mic(struct IsdnCardState *cs)
{
	int bytecnt = 8;

	if (cs->hw.mic.cfg_reg)
		release_region(cs->hw.mic.cfg_reg, bytecnt);
}

static int
mic_card_msg(struct IsdnCardState *cs, int mt, void *arg)
{
	u_long flags;

	switch (mt) {
<<<<<<< HEAD
		case CARD_RESET:
			return(0);
		case CARD_RELEASE:
			release_io_mic(cs);
			return(0);
		case CARD_INIT:
			spin_lock_irqsave(&cs->lock, flags);
			inithscx(cs); /* /RTSA := ISAC RST */
			inithscxisac(cs, 3);
			spin_unlock_irqrestore(&cs->lock, flags);
			return(0);
		case CARD_TEST:
			return(0);
	}
	return(0);
=======
	case CARD_RESET:
		return (0);
	case CARD_RELEASE:
		release_io_mic(cs);
		return (0);
	case CARD_INIT:
		spin_lock_irqsave(&cs->lock, flags);
		inithscx(cs); /* /RTSA := ISAC RST */
		inithscxisac(cs, 3);
		spin_unlock_irqrestore(&cs->lock, flags);
		return (0);
	case CARD_TEST:
		return (0);
	}
	return (0);
>>>>>>> cm-10.0
}

int __devinit
setup_mic(struct IsdnCard *card)
{
	int bytecnt;
	struct IsdnCardState *cs = card->cs;
	char tmp[64];

	strcpy(tmp, mic_revision);
	printk(KERN_INFO "HiSax: mic driver Rev. %s\n", HiSax_getrev(tmp));
	if (cs->typ != ISDN_CTYPE_MIC)
		return (0);

	bytecnt = 8;
	cs->hw.mic.cfg_reg = card->para[1];
	cs->irq = card->para[0];
	cs->hw.mic.adr = cs->hw.mic.cfg_reg + MIC_ADR;
	cs->hw.mic.isac = cs->hw.mic.cfg_reg + MIC_ISAC;
	cs->hw.mic.hscx = cs->hw.mic.cfg_reg + MIC_HSCX;

	if (!request_region(cs->hw.mic.cfg_reg, bytecnt, "mic isdn")) {
		printk(KERN_WARNING
		       "HiSax: ith mic config port %x-%x already in use\n",
		       cs->hw.mic.cfg_reg,
		       cs->hw.mic.cfg_reg + bytecnt);
		return (0);
	}
	printk(KERN_INFO "mic: defined at 0x%x IRQ %d\n",
<<<<<<< HEAD
		cs->hw.mic.cfg_reg, cs->irq);
=======
	       cs->hw.mic.cfg_reg, cs->irq);
>>>>>>> cm-10.0
	setup_isac(cs);
	cs->readisac = &ReadISAC;
	cs->writeisac = &WriteISAC;
	cs->readisacfifo = &ReadISACfifo;
	cs->writeisacfifo = &WriteISACfifo;
	cs->BC_Read_Reg = &ReadHSCX;
	cs->BC_Write_Reg = &WriteHSCX;
	cs->BC_Send_Data = &hscx_fill_fifo;
	cs->cardmsg = &mic_card_msg;
	cs->irq_func = &mic_interrupt;
	ISACVersion(cs, "mic:");
	if (HscxVersion(cs, "mic:")) {
		printk(KERN_WARNING
<<<<<<< HEAD
		    "mic: wrong HSCX versions check IO address\n");
=======
		       "mic: wrong HSCX versions check IO address\n");
>>>>>>> cm-10.0
		release_io_mic(cs);
		return (0);
	}
	return (1);
}
