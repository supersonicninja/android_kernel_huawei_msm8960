/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include <linux/delay.h>
<<<<<<< HEAD
#include <linux/io.h>
=======
>>>>>>> cm-10.0
#include <linux/slab.h>
#include "./common.h"
#include "./pipe.h"

/*
 *		macros
 */
<<<<<<< HEAD
#define usbhsp_priv_to_pipeinfo(pr)	(&(pr)->pipe_info)
#define usbhsp_pipe_to_priv(p)		((p)->priv)

#define usbhsp_addr_offset(p)	((usbhs_pipe_number(p) - 1) * 2)

#define usbhsp_is_dcp(p)	((p)->priv->pipe_info.pipe == (p))

=======
#define usbhsp_addr_offset(p)	((usbhs_pipe_number(p) - 1) * 2)

>>>>>>> cm-10.0
#define usbhsp_flags_set(p, f)	((p)->flags |=  USBHS_PIPE_FLAGS_##f)
#define usbhsp_flags_clr(p, f)	((p)->flags &= ~USBHS_PIPE_FLAGS_##f)
#define usbhsp_flags_has(p, f)	((p)->flags &   USBHS_PIPE_FLAGS_##f)
#define usbhsp_flags_init(p)	do {(p)->flags = 0; } while (0)

<<<<<<< HEAD
#define usbhsp_type(p)		((p)->pipe_type)
#define usbhsp_type_is(p, t)	((p)->pipe_type == t)

=======
>>>>>>> cm-10.0
/*
 * for debug
 */
static char *usbhsp_pipe_name[] = {
	[USB_ENDPOINT_XFER_CONTROL]	= "DCP",
	[USB_ENDPOINT_XFER_BULK]	= "BULK",
	[USB_ENDPOINT_XFER_INT]		= "INT",
	[USB_ENDPOINT_XFER_ISOC]	= "ISO",
};

<<<<<<< HEAD
/*
 *		usb request functions
 */
void usbhs_usbreq_get_val(struct usbhs_priv *priv, struct usb_ctrlrequest *req)
{
	u16 val;

	val = usbhs_read(priv, USBREQ);
	req->bRequest		= (val >> 8) & 0xFF;
	req->bRequestType	= (val >> 0) & 0xFF;

	req->wValue	= usbhs_read(priv, USBVAL);
	req->wIndex	= usbhs_read(priv, USBINDX);
	req->wLength	= usbhs_read(priv, USBLENG);
}

void usbhs_usbreq_set_val(struct usbhs_priv *priv, struct usb_ctrlrequest *req)
{
	usbhs_write(priv, USBREQ,  (req->bRequest << 8) | req->bRequestType);
	usbhs_write(priv, USBVAL,  req->wValue);
	usbhs_write(priv, USBINDX, req->wIndex);
	usbhs_write(priv, USBLENG, req->wLength);
=======
char *usbhs_pipe_name(struct usbhs_pipe *pipe)
{
	return usbhsp_pipe_name[usbhs_pipe_type(pipe)];
>>>>>>> cm-10.0
}

/*
 *		DCPCTR/PIPEnCTR functions
 */
static void usbhsp_pipectrl_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
<<<<<<< HEAD
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
	int offset = usbhsp_addr_offset(pipe);

	if (usbhsp_is_dcp(pipe))
=======
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	int offset = usbhsp_addr_offset(pipe);

	if (usbhs_pipe_is_dcp(pipe))
>>>>>>> cm-10.0
		usbhs_bset(priv, DCPCTR, mask, val);
	else
		usbhs_bset(priv, PIPEnCTR + offset, mask, val);
}

static u16 usbhsp_pipectrl_get(struct usbhs_pipe *pipe)
{
<<<<<<< HEAD
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
	int offset = usbhsp_addr_offset(pipe);

	if (usbhsp_is_dcp(pipe))
=======
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	int offset = usbhsp_addr_offset(pipe);

	if (usbhs_pipe_is_dcp(pipe))
>>>>>>> cm-10.0
		return usbhs_read(priv, DCPCTR);
	else
		return usbhs_read(priv, PIPEnCTR + offset);
}

/*
 *		DCP/PIPE functions
 */
static void __usbhsp_pipe_xxx_set(struct usbhs_pipe *pipe,
				  u16 dcp_reg, u16 pipe_reg,
				  u16 mask, u16 val)
{
<<<<<<< HEAD
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);

	if (usbhsp_is_dcp(pipe))
=======
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	if (usbhs_pipe_is_dcp(pipe))
>>>>>>> cm-10.0
		usbhs_bset(priv, dcp_reg, mask, val);
	else
		usbhs_bset(priv, pipe_reg, mask, val);
}

<<<<<<< HEAD
static u16 __usbhsp_pipe_xxx_get(struct usbhs_pipe *pipe,
				 u16 dcp_reg, u16 pipe_reg)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);

	if (usbhsp_is_dcp(pipe))
		return usbhs_read(priv, dcp_reg);
	else
		return usbhs_read(priv, pipe_reg);
}

=======
>>>>>>> cm-10.0
/*
 *		DCPCFG/PIPECFG functions
 */
static void usbhsp_pipe_cfg_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
	__usbhsp_pipe_xxx_set(pipe, DCPCFG, PIPECFG, mask, val);
}

/*
 *		PIPEBUF
 */
static void usbhsp_pipe_buf_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
<<<<<<< HEAD
	if (usbhsp_is_dcp(pipe))
=======
	if (usbhs_pipe_is_dcp(pipe))
>>>>>>> cm-10.0
		return;

	__usbhsp_pipe_xxx_set(pipe, 0, PIPEBUF, mask, val);
}

/*
 *		DCPMAXP/PIPEMAXP
 */
static void usbhsp_pipe_maxp_set(struct usbhs_pipe *pipe, u16 mask, u16 val)
{
	__usbhsp_pipe_xxx_set(pipe, DCPMAXP, PIPEMAXP, mask, val);
}

<<<<<<< HEAD
static u16 usbhsp_pipe_maxp_get(struct usbhs_pipe *pipe)
{
	return __usbhsp_pipe_xxx_get(pipe, DCPMAXP, PIPEMAXP);
}

=======
>>>>>>> cm-10.0
/*
 *		pipe control functions
 */
static void usbhsp_pipe_select(struct usbhs_pipe *pipe)
{
<<<<<<< HEAD
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
=======
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
>>>>>>> cm-10.0

	/*
	 * On pipe, this is necessary before
	 * accesses to below registers.
	 *
	 * PIPESEL	: usbhsp_pipe_select
	 * PIPECFG	: usbhsp_pipe_cfg_xxx
	 * PIPEBUF	: usbhsp_pipe_buf_xxx
	 * PIPEMAXP	: usbhsp_pipe_maxp_xxx
	 * PIPEPERI
	 */

	/*
	 * if pipe is dcp, no pipe is selected.
	 * it is no problem, because dcp have its register
	 */
	usbhs_write(priv, PIPESEL, 0xF & usbhs_pipe_number(pipe));
}

static int usbhsp_pipe_barrier(struct usbhs_pipe *pipe)
{
<<<<<<< HEAD
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
=======
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
>>>>>>> cm-10.0
	int timeout = 1024;
	u16 val;

	/*
	 * make sure....
	 *
	 * Modify these bits when CSSTS = 0, PID = NAK, and no pipe number is
	 * specified by the CURPIPE bits.
	 * When changing the setting of this bit after changing
	 * the PID bits for the selected pipe from BUF to NAK,
	 * check that CSSTS = 0 and PBUSY = 0.
	 */

	/*
	 * CURPIPE bit = 0
	 *
	 * see also
	 *  "Operation"
	 *  - "Pipe Control"
	 *   - "Pipe Control Registers Switching Procedure"
	 */
	usbhs_write(priv, CFIFOSEL, 0);
<<<<<<< HEAD
	usbhs_fifo_disable(pipe);
=======
	usbhs_pipe_disable(pipe);
>>>>>>> cm-10.0

	do {
		val  = usbhsp_pipectrl_get(pipe);
		val &= CSSTS | PID_MASK;
		if (!val)
			return 0;

		udelay(10);

	} while (timeout--);

	return -EBUSY;
}

<<<<<<< HEAD
static int usbhsp_pipe_is_accessible(struct usbhs_pipe *pipe)
=======
int usbhs_pipe_is_accessible(struct usbhs_pipe *pipe)
>>>>>>> cm-10.0
{
	u16 val;

	val = usbhsp_pipectrl_get(pipe);
	if (val & BSTS)
		return 0;

	return -EBUSY;
}

/*
 *		PID ctrl
 */
static void __usbhsp_pid_try_nak_if_stall(struct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectrl_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Control Register" - "PID"
	 */
	switch (pid) {
	case PID_STALL11:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL10);
		/* fall-through */
	case PID_STALL10:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_NAK);
	}
}

<<<<<<< HEAD
void usbhs_fifo_disable(struct usbhs_pipe *pipe)
=======
void usbhs_pipe_disable(struct usbhs_pipe *pipe)
>>>>>>> cm-10.0
{
	int timeout = 1024;
	u16 val;

	/* see "Pipe n Control Register" - "PID" */
	__usbhsp_pid_try_nak_if_stall(pipe);

	usbhsp_pipectrl_set(pipe, PID_MASK, PID_NAK);

	do {
		val  = usbhsp_pipectrl_get(pipe);
		val &= PBUSY;
		if (!val)
			break;

		udelay(10);
	} while (timeout--);
}

<<<<<<< HEAD
void usbhs_fifo_enable(struct usbhs_pipe *pipe)
=======
void usbhs_pipe_enable(struct usbhs_pipe *pipe)
>>>>>>> cm-10.0
{
	/* see "Pipe n Control Register" - "PID" */
	__usbhsp_pid_try_nak_if_stall(pipe);

	usbhsp_pipectrl_set(pipe, PID_MASK, PID_BUF);
}

<<<<<<< HEAD
void usbhs_fifo_stall(struct usbhs_pipe *pipe)
=======
void usbhs_pipe_stall(struct usbhs_pipe *pipe)
>>>>>>> cm-10.0
{
	u16 pid = usbhsp_pipectrl_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Control Register" - "PID"
	 */
	switch (pid) {
	case PID_NAK:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL10);
		break;
	case PID_BUF:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL11);
		break;
	}
}

<<<<<<< HEAD
/*
 *		CFIFO ctrl
 */
void usbhs_fifo_send_terminator(struct usbhs_pipe *pipe)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);

	usbhs_bset(priv, CFIFOCTR, BVAL, BVAL);
}

static void usbhsp_fifo_clear(struct usbhs_pipe *pipe)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);

	usbhs_write(priv, CFIFOCTR, BCLR);
}

static int usbhsp_fifo_barrier(struct usbhs_priv *priv)
{
	int timeout = 1024;

	do {
		/* The FIFO port is accessible */
		if (usbhs_read(priv, CFIFOCTR) & FRDY)
			return 0;

		udelay(10);
	} while (timeout--);

	return -EBUSY;
}

static int usbhsp_fifo_rcv_len(struct usbhs_priv *priv)
{
	return usbhs_read(priv, CFIFOCTR) & DTLN_MASK;
}

static int usbhsp_fifo_select(struct usbhs_pipe *pipe, int write)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
	struct device *dev = usbhs_priv_to_dev(priv);
	int timeout = 1024;
	u16 mask = ((1 << 5) | 0xF);		/* mask of ISEL | CURPIPE */
	u16 base = usbhs_pipe_number(pipe);	/* CURPIPE */

	if (usbhsp_is_dcp(pipe))
		base |= (1 == write) << 5;	/* ISEL */

	/* "base" will be used below  */
	usbhs_write(priv, CFIFOSEL, base | MBW_32);

	/* check ISEL and CURPIPE value */
	while (timeout--) {
		if (base == (mask & usbhs_read(priv, CFIFOSEL)))
			return 0;
		udelay(10);
	}

	dev_err(dev, "fifo select error\n");

	return -EIO;
}

int usbhs_fifo_prepare_write(struct usbhs_pipe *pipe)
{
	return usbhsp_fifo_select(pipe, 1);
}

int usbhs_fifo_write(struct usbhs_pipe *pipe, u8 *buf, int len)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
	void __iomem *addr = priv->base + CFIFO;
	int maxp = usbhs_pipe_get_maxpacket(pipe);
	int total_len;
	int i, ret;

	ret = usbhsp_pipe_is_accessible(pipe);
	if (ret < 0)
		return ret;

	ret = usbhsp_fifo_select(pipe, 1);
	if (ret < 0)
		return ret;

	ret = usbhsp_fifo_barrier(priv);
	if (ret < 0)
		return ret;

	len = min(len, maxp);
	total_len = len;

	/*
	 * FIXME
	 *
	 * 32-bit access only
	 */
	if (len >= 4 &&
	    !((unsigned long)buf & 0x03)) {
		iowrite32_rep(addr, buf, len / 4);
		len %= 4;
		buf += total_len - len;
	}

	/* the rest operation */
	for (i = 0; i < len; i++)
		iowrite8(buf[i], addr + (0x03 - (i & 0x03)));

	if (total_len < maxp)
		usbhs_fifo_send_terminator(pipe);

	return total_len;
}

int usbhs_fifo_prepare_read(struct usbhs_pipe *pipe)
{
	int ret;

	/*
	 * select pipe and enable it to prepare packet receive
	 */
	ret = usbhsp_fifo_select(pipe, 0);
	if (ret < 0)
		return ret;

	usbhs_fifo_enable(pipe);

	return ret;
}

int usbhs_fifo_read(struct usbhs_pipe *pipe, u8 *buf, int len)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
	void __iomem *addr = priv->base + CFIFO;
	int rcv_len;
	int i, ret;
	int total_len;
	u32 data = 0;

	ret = usbhsp_fifo_select(pipe, 0);
	if (ret < 0)
		return ret;

	ret = usbhsp_fifo_barrier(priv);
	if (ret < 0)
		return ret;

	rcv_len = usbhsp_fifo_rcv_len(priv);

	/*
	 * Buffer clear if Zero-Length packet
	 *
	 * see
	 * "Operation" - "FIFO Buffer Memory" - "FIFO Port Function"
	 */
	if (0 == rcv_len) {
		usbhsp_fifo_clear(pipe);
		return 0;
	}

	len = min(rcv_len, len);
	total_len = len;

	/*
	 * FIXME
	 *
	 * 32-bit access only
	 */
	if (len >= 4 &&
	    !((unsigned long)buf & 0x03)) {
		ioread32_rep(addr, buf, len / 4);
		len %= 4;
		buf += rcv_len - len;
	}

	/* the rest operation */
	for (i = 0; i < len; i++) {
		if (!(i & 0x03))
			data = ioread32(addr);

		buf[i] = (data >> ((i & 0x03) * 8)) & 0xff;
	}

	return total_len;
=======
int usbhs_pipe_is_stall(struct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectrl_get(pipe) & PID_MASK;

	return (int)(pid == PID_STALL10 || pid == PID_STALL11);
>>>>>>> cm-10.0
}

/*
 *		pipe setup
 */
static int usbhsp_possible_double_buffer(struct usbhs_pipe *pipe)
{
	/*
	 * only ISO / BULK pipe can use double buffer
	 */
<<<<<<< HEAD
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_BULK) ||
	    usbhsp_type_is(pipe, USB_ENDPOINT_XFER_ISOC))
=======
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC))
>>>>>>> cm-10.0
		return 1;

	return 0;
}

static u16 usbhsp_setup_pipecfg(struct usbhs_pipe *pipe,
<<<<<<< HEAD
				const struct usb_endpoint_descriptor *desc,
				int is_host)
=======
				int is_host,
				int dir_in)
>>>>>>> cm-10.0
{
	u16 type = 0;
	u16 bfre = 0;
	u16 dblb = 0;
	u16 cntmd = 0;
	u16 dir = 0;
	u16 epnum = 0;
	u16 shtnak = 0;
	u16 type_array[] = {
		[USB_ENDPOINT_XFER_BULK] = TYPE_BULK,
		[USB_ENDPOINT_XFER_INT]  = TYPE_INT,
		[USB_ENDPOINT_XFER_ISOC] = TYPE_ISO,
	};
	int is_double = usbhsp_possible_double_buffer(pipe);

<<<<<<< HEAD
	if (usbhsp_is_dcp(pipe))
=======
	if (usbhs_pipe_is_dcp(pipe))
>>>>>>> cm-10.0
		return -EINVAL;

	/*
	 * PIPECFG
	 *
	 * see
	 *  - "Register Descriptions" - "PIPECFG" register
	 *  - "Features"  - "Pipe configuration"
	 *  - "Operation" - "Pipe Control"
	 */

	/* TYPE */
<<<<<<< HEAD
	type = type_array[usbhsp_type(pipe)];

	/* BFRE */
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_ISOC) ||
	    usbhsp_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		bfre = 0; /* FIXME */

	/* DBLB */
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_ISOC) ||
	    usbhsp_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		dblb = (is_double) ? DBLB : 0;

	/* CNTMD */
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		cntmd = 0; /* FIXME */

	/* DIR */
	if (usb_endpoint_dir_in(desc))
		usbhsp_flags_set(pipe, IS_DIR_IN);

	if ((is_host  && usb_endpoint_dir_out(desc)) ||
	    (!is_host && usb_endpoint_dir_in(desc)))
		dir |= DIR_OUT;

	/* SHTNAK */
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_BULK) &&
=======
	type = type_array[usbhs_pipe_type(pipe)];

	/* BFRE */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		bfre = 0; /* FIXME */

	/* DBLB */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		dblb = (is_double) ? DBLB : 0;

	/* CNTMD */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK))
		cntmd = 0; /* FIXME */

	/* DIR */
	if (dir_in)
		usbhsp_flags_set(pipe, IS_DIR_HOST);

	if (!!is_host ^ !!dir_in)
		dir |= DIR_OUT;

	if (!dir)
		usbhsp_flags_set(pipe, IS_DIR_IN);

	/* SHTNAK */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_BULK) &&
>>>>>>> cm-10.0
	    !dir)
		shtnak = SHTNAK;

	/* EPNUM */
<<<<<<< HEAD
	epnum = 0xF & usb_endpoint_num(desc);
=======
	epnum = 0; /* see usbhs_pipe_config_update() */
>>>>>>> cm-10.0

	return	type	|
		bfre	|
		dblb	|
		cntmd	|
		dir	|
		shtnak	|
		epnum;
}

<<<<<<< HEAD
static u16 usbhsp_setup_pipemaxp(struct usbhs_pipe *pipe,
				 const struct usb_endpoint_descriptor *desc,
				 int is_host)
{
	/* host should set DEVSEL */

	/* reutn MXPS */
	return PIPE_MAXP_MASK & le16_to_cpu(desc->wMaxPacketSize);
}

static u16 usbhsp_setup_pipebuff(struct usbhs_pipe *pipe,
				 const struct usb_endpoint_descriptor *desc,
				 int is_host)
{
	struct usbhs_priv *priv = usbhsp_pipe_to_priv(pipe);
	struct usbhs_pipe_info *info = usbhsp_priv_to_pipeinfo(priv);
=======
static u16 usbhsp_setup_pipebuff(struct usbhs_pipe *pipe)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
>>>>>>> cm-10.0
	struct device *dev = usbhs_priv_to_dev(priv);
	int pipe_num = usbhs_pipe_number(pipe);
	int is_double = usbhsp_possible_double_buffer(pipe);
	u16 buff_size;
	u16 bufnmb;
	u16 bufnmb_cnt;

	/*
	 * PIPEBUF
	 *
	 * see
	 *  - "Register Descriptions" - "PIPEBUF" register
	 *  - "Features"  - "Pipe configuration"
	 *  - "Operation" - "FIFO Buffer Memory"
	 *  - "Operation" - "Pipe Control"
	 *
	 * ex) if pipe6 - pipe9 are USB_ENDPOINT_XFER_INT (SH7724)
	 *
	 * BUFNMB:	PIPE
	 * 0:		pipe0 (DCP 256byte)
	 * 1:		-
	 * 2:		-
	 * 3:		-
	 * 4:		pipe6 (INT 64byte)
	 * 5:		pipe7 (INT 64byte)
	 * 6:		pipe8 (INT 64byte)
	 * 7:		pipe9 (INT 64byte)
	 * 8 - xx:	free (for BULK, ISOC)
	 */

	/*
	 * FIXME
	 *
	 * it doesn't have good buffer allocator
	 *
	 * DCP : 256 byte
	 * BULK: 512 byte
	 * INT :  64 byte
	 * ISOC: 512 byte
	 */
<<<<<<< HEAD
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_CONTROL))
		buff_size = 256;
	else if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_INT))
=======
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_CONTROL))
		buff_size = 256;
	else if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_INT))
>>>>>>> cm-10.0
		buff_size = 64;
	else
		buff_size = 512;

	/* change buff_size to register value */
	bufnmb_cnt = (buff_size / 64) - 1;

	/* BUFNMB has been reserved for INT pipe
	 * see above */
<<<<<<< HEAD
	if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_INT)) {
=======
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_INT)) {
>>>>>>> cm-10.0
		bufnmb = pipe_num - 2;
	} else {
		bufnmb = info->bufnmb_last;
		info->bufnmb_last += bufnmb_cnt + 1;

		/*
		 * double buffer
		 */
		if (is_double)
			info->bufnmb_last += bufnmb_cnt + 1;
	}

	dev_dbg(dev, "pipe : %d : buff_size 0x%x: bufnmb 0x%x\n",
		pipe_num, buff_size, bufnmb);

	return	(0x1f & bufnmb_cnt)	<< 10 |
		(0xff & bufnmb)		<<  0;
}

<<<<<<< HEAD
=======
void usbhs_pipe_config_update(struct usbhs_pipe *pipe, u16 devsel,
			      u16 epnum, u16 maxp)
{
	if (devsel > 0xA) {
		struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
		struct device *dev = usbhs_priv_to_dev(priv);

		dev_err(dev, "devsel error %d\n", devsel);

		devsel = 0;
	}

	usbhsp_pipe_barrier(pipe);

	pipe->maxp = maxp;

	usbhsp_pipe_select(pipe);
	usbhsp_pipe_maxp_set(pipe, 0xFFFF,
			     (devsel << 12) |
			     maxp);

	if (!usbhs_pipe_is_dcp(pipe))
		usbhsp_pipe_cfg_set(pipe,  0x000F, epnum);
}

>>>>>>> cm-10.0
/*
 *		pipe control
 */
int usbhs_pipe_get_maxpacket(struct usbhs_pipe *pipe)
{
<<<<<<< HEAD
	u16 mask = usbhsp_is_dcp(pipe) ? DCP_MAXP_MASK : PIPE_MAXP_MASK;

	usbhsp_pipe_select(pipe);

	return (int)(usbhsp_pipe_maxp_get(pipe) & mask);
=======
	/*
	 * see
	 *	usbhs_pipe_config_update()
	 *	usbhs_dcp_malloc()
	 */
	return pipe->maxp;
>>>>>>> cm-10.0
}

int usbhs_pipe_is_dir_in(struct usbhs_pipe *pipe)
{
	return usbhsp_flags_has(pipe, IS_DIR_IN);
}

<<<<<<< HEAD
void usbhs_pipe_clear_sequence(struct usbhs_pipe *pipe)
{
	usbhsp_pipectrl_set(pipe, SQCLR, SQCLR);
=======
int usbhs_pipe_is_dir_host(struct usbhs_pipe *pipe)
{
	return usbhsp_flags_has(pipe, IS_DIR_HOST);
}

void usbhs_pipe_data_sequence(struct usbhs_pipe *pipe, int sequence)
{
	u16 mask = (SQCLR | SQSET);
	u16 val;

	/*
	 * sequence
	 *  0  : data0
	 *  1  : data1
	 *  -1 : no change
	 */
	switch (sequence) {
	case 0:
		val = SQCLR;
		break;
	case 1:
		val = SQSET;
		break;
	default:
		return;
	}

	usbhsp_pipectrl_set(pipe, mask, val);
}

void usbhs_pipe_clear(struct usbhs_pipe *pipe)
{
	usbhsp_pipectrl_set(pipe, ACLRM, ACLRM);
	usbhsp_pipectrl_set(pipe, ACLRM, 0);
>>>>>>> cm-10.0
}

static struct usbhs_pipe *usbhsp_get_pipe(struct usbhs_priv *priv, u32 type)
{
	struct usbhs_pipe *pos, *pipe;
	int i;

	/*
	 * find target pipe
	 */
	pipe = NULL;
	usbhs_for_each_pipe_with_dcp(pos, priv, i) {
<<<<<<< HEAD
		if (!usbhsp_type_is(pos, type))
=======
		if (!usbhs_pipe_type_is(pos, type))
>>>>>>> cm-10.0
			continue;
		if (usbhsp_flags_has(pos, IS_USED))
			continue;

		pipe = pos;
		break;
	}

	if (!pipe)
		return NULL;

	/*
	 * initialize pipe flags
	 */
	usbhsp_flags_init(pipe);
	usbhsp_flags_set(pipe, IS_USED);

	return pipe;
}

<<<<<<< HEAD
void usbhs_pipe_init(struct usbhs_priv *priv)
{
	struct usbhs_pipe_info *info = usbhsp_priv_to_pipeinfo(priv);
=======
void usbhs_pipe_init(struct usbhs_priv *priv,
		     int (*dma_map_ctrl)(struct usbhs_pkt *pkt, int map))
{
	struct usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
>>>>>>> cm-10.0
	struct usbhs_pipe *pipe;
	int i;

	/*
	 * FIXME
	 *
	 * driver needs good allocator.
	 *
	 * find first free buffer area (BULK, ISOC)
	 * (DCP, INT area is fixed)
	 *
	 * buffer number 0 - 3 have been reserved for DCP
	 * see
	 *	usbhsp_to_bufnmb
	 */
	info->bufnmb_last = 4;
	usbhs_for_each_pipe_with_dcp(pipe, priv, i) {
<<<<<<< HEAD
		if (usbhsp_type_is(pipe, USB_ENDPOINT_XFER_INT))
			info->bufnmb_last++;

		usbhsp_flags_init(pipe);
		pipe->mod_private = NULL;

		usbhsp_fifo_clear(pipe);
	}
}

struct usbhs_pipe *usbhs_pipe_malloc(struct usbhs_priv *priv,
				     const struct usb_endpoint_descriptor *desc)
{
	struct device *dev = usbhs_priv_to_dev(priv);
	struct usbhs_mod *mod = usbhs_mod_get_current(priv);
	struct usbhs_pipe *pipe;
	int is_host = usbhs_mod_is_host(priv, mod);
	int ret;
	u16 pipecfg, pipebuf, pipemaxp;

	pipe = usbhsp_get_pipe(priv, usb_endpoint_type(desc));
	if (!pipe) {
		dev_err(dev, "can't get pipe (%s)\n",
			usbhsp_pipe_name[usb_endpoint_type(desc)]);
		return NULL;
	}

	usbhs_fifo_disable(pipe);
=======
		if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_INT))
			info->bufnmb_last++;

		usbhsp_flags_init(pipe);
		pipe->fifo = NULL;
		pipe->mod_private = NULL;
		INIT_LIST_HEAD(&pipe->list);

		/* pipe force init */
		usbhs_pipe_clear(pipe);
	}

	info->dma_map_ctrl = dma_map_ctrl;
}

struct usbhs_pipe *usbhs_pipe_malloc(struct usbhs_priv *priv,
				     int endpoint_type,
				     int dir_in)
{
	struct device *dev = usbhs_priv_to_dev(priv);
	struct usbhs_pipe *pipe;
	int is_host = usbhs_mod_is_host(priv);
	int ret;
	u16 pipecfg, pipebuf;

	pipe = usbhsp_get_pipe(priv, endpoint_type);
	if (!pipe) {
		dev_err(dev, "can't get pipe (%s)\n",
			usbhsp_pipe_name[endpoint_type]);
		return NULL;
	}

	INIT_LIST_HEAD(&pipe->list);

	usbhs_pipe_disable(pipe);
>>>>>>> cm-10.0

	/* make sure pipe is not busy */
	ret = usbhsp_pipe_barrier(pipe);
	if (ret < 0) {
		dev_err(dev, "pipe setup failed %d\n", usbhs_pipe_number(pipe));
		return NULL;
	}

<<<<<<< HEAD
	pipecfg  = usbhsp_setup_pipecfg(pipe,  desc, is_host);
	pipebuf  = usbhsp_setup_pipebuff(pipe, desc, is_host);
	pipemaxp = usbhsp_setup_pipemaxp(pipe, desc, is_host);

	/* buffer clear
	 * see PIPECFG :: BFRE */
	usbhsp_pipectrl_set(pipe, ACLRM, ACLRM);
	usbhsp_pipectrl_set(pipe, ACLRM, 0);
=======
	pipecfg  = usbhsp_setup_pipecfg(pipe, is_host, dir_in);
	pipebuf  = usbhsp_setup_pipebuff(pipe);
>>>>>>> cm-10.0

	usbhsp_pipe_select(pipe);
	usbhsp_pipe_cfg_set(pipe, 0xFFFF, pipecfg);
	usbhsp_pipe_buf_set(pipe, 0xFFFF, pipebuf);
<<<<<<< HEAD
	usbhsp_pipe_maxp_set(pipe, 0xFFFF, pipemaxp);

	usbhs_pipe_clear_sequence(pipe);

	dev_dbg(dev, "enable pipe %d : %s (%s)\n",
		usbhs_pipe_number(pipe),
		usbhsp_pipe_name[usb_endpoint_type(desc)],
		usbhs_pipe_is_dir_in(pipe) ? "in" : "out");

	return pipe;
}

=======

	usbhs_pipe_sequence_data0(pipe);

	dev_dbg(dev, "enable pipe %d : %s (%s)\n",
		usbhs_pipe_number(pipe),
		usbhs_pipe_name(pipe),
		usbhs_pipe_is_dir_in(pipe) ? "in" : "out");

	/*
	 * epnum / maxp are still not set to this pipe.
	 * call usbhs_pipe_config_update() after this function !!
	 */

	return pipe;
}

void usbhs_pipe_select_fifo(struct usbhs_pipe *pipe, struct usbhs_fifo *fifo)
{
	if (pipe->fifo)
		pipe->fifo->pipe = NULL;

	pipe->fifo = fifo;

	if (fifo)
		fifo->pipe = pipe;
}


>>>>>>> cm-10.0
/*
 *		dcp control
 */
struct usbhs_pipe *usbhs_dcp_malloc(struct usbhs_priv *priv)
{
	struct usbhs_pipe *pipe;

	pipe = usbhsp_get_pipe(priv, USB_ENDPOINT_XFER_CONTROL);
	if (!pipe)
		return NULL;

<<<<<<< HEAD
	/*
	 * dcpcfg  : default
	 * dcpmaxp : default
	 * pipebuf : nothing to do
	 */

	usbhsp_pipe_select(pipe);
	usbhs_pipe_clear_sequence(pipe);

=======
	INIT_LIST_HEAD(&pipe->list);

	/*
	 * call usbhs_pipe_config_update() after this function !!
	 */

>>>>>>> cm-10.0
	return pipe;
}

void usbhs_dcp_control_transfer_done(struct usbhs_pipe *pipe)
{
<<<<<<< HEAD
	WARN_ON(!usbhsp_is_dcp(pipe));

	usbhs_fifo_enable(pipe);
	usbhsp_pipectrl_set(pipe, CCPL, CCPL);
}

=======
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	WARN_ON(!usbhs_pipe_is_dcp(pipe));

	usbhs_pipe_enable(pipe);

	if (!usbhs_mod_is_host(priv)) /* funconly */
		usbhsp_pipectrl_set(pipe, CCPL, CCPL);
}

void usbhs_dcp_dir_for_host(struct usbhs_pipe *pipe, int dir_out)
{
	usbhsp_pipe_cfg_set(pipe, DIR_OUT,
			    dir_out ? DIR_OUT : 0);
}
>>>>>>> cm-10.0

/*
 *		pipe module function
 */
int usbhs_pipe_probe(struct usbhs_priv *priv)
{
<<<<<<< HEAD
	struct usbhs_pipe_info *info = usbhsp_priv_to_pipeinfo(priv);
=======
	struct usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
>>>>>>> cm-10.0
	struct usbhs_pipe *pipe;
	struct device *dev = usbhs_priv_to_dev(priv);
	u32 *pipe_type = usbhs_get_dparam(priv, pipe_type);
	int pipe_size = usbhs_get_dparam(priv, pipe_size);
	int i;

	/* This driver expects 1st pipe is DCP */
	if (pipe_type[0] != USB_ENDPOINT_XFER_CONTROL) {
		dev_err(dev, "1st PIPE is not DCP\n");
		return -EINVAL;
	}

	info->pipe = kzalloc(sizeof(struct usbhs_pipe) * pipe_size, GFP_KERNEL);
	if (!info->pipe) {
		dev_err(dev, "Could not allocate pipe\n");
		return -ENOMEM;
	}

	info->size = pipe_size;

	/*
	 * init pipe
	 */
	usbhs_for_each_pipe_with_dcp(pipe, priv, i) {
		pipe->priv = priv;
<<<<<<< HEAD
		usbhsp_type(pipe) = pipe_type[i] & USB_ENDPOINT_XFERTYPE_MASK;
=======

		usbhs_pipe_type(pipe) =
			pipe_type[i] & USB_ENDPOINT_XFERTYPE_MASK;
>>>>>>> cm-10.0

		dev_dbg(dev, "pipe %x\t: %s\n",
			i, usbhsp_pipe_name[pipe_type[i]]);
	}

	return 0;
}

void usbhs_pipe_remove(struct usbhs_priv *priv)
{
<<<<<<< HEAD
	struct usbhs_pipe_info *info = usbhsp_priv_to_pipeinfo(priv);
=======
	struct usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
>>>>>>> cm-10.0

	kfree(info->pipe);
}
