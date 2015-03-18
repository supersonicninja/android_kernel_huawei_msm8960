/*
 * ad2s1210.c support for the ADI Resolver to Digital Converters: AD2S1210
 *
 * Copyright (c) 2010-2010 Analog Devices Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/spi/spi.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/delay.h>
#include <linux/gpio.h>
<<<<<<< HEAD

#include "../iio.h"
#include "../sysfs.h"

#define DRV_NAME "ad2s1210"

#define DEF_CONTROL		0x7E

#define MSB_IS_HIGH		0x80
#define MSB_IS_LOW		0x7F
#define PHASE_LOCK_RANGE_44	0x20
#define ENABLE_HYSTERESIS	0x10
#define SET_ENRES1		0x08
#define SET_ENRES0		0x04
#define SET_RES1		0x02
#define SET_RES0		0x01

#define SET_ENRESOLUTION	(SET_ENRES1 | SET_ENRES0)
#define SET_RESOLUTION		(SET_RES1 | SET_RES0)

#define REG_POSITION		0x80
#define REG_VELOCITY		0x82
#define REG_LOS_THRD		0x88
#define REG_DOS_OVR_THRD	0x89
#define REG_DOS_MIS_THRD	0x8A
#define REG_DOS_RST_MAX_THRD	0x8B
#define REG_DOS_RST_MIN_THRD	0x8C
#define REG_LOT_HIGH_THRD	0x8D
#define REG_LOT_LOW_THRD	0x8E
#define REG_EXCIT_FREQ		0x91
#define REG_CONTROL		0x92
#define REG_SOFT_RESET		0xF0
#define REG_FAULT		0xFF

/* pin SAMPLE, A0, A1, RES0, RES1, is controlled by driver */
#define AD2S1210_SAA		3
#if defined(CONFIG_AD2S1210_GPIO_INPUT) || defined(CONFIG_AD2S1210_GPIO_OUTPUT)
# define AD2S1210_RES		2
#else
# define AD2S1210_RES		0
#endif
=======
#include <linux/module.h>

#include "../iio.h"
#include "../sysfs.h"
#include "ad2s1210.h"

#define DRV_NAME "ad2s1210"

#define AD2S1210_DEF_CONTROL		0x7E

#define AD2S1210_MSB_IS_HIGH		0x80
#define AD2S1210_MSB_IS_LOW		0x7F
#define AD2S1210_PHASE_LOCK_RANGE_44	0x20
#define AD2S1210_ENABLE_HYSTERESIS	0x10
#define AD2S1210_SET_ENRES1		0x08
#define AD2S1210_SET_ENRES0		0x04
#define AD2S1210_SET_RES1		0x02
#define AD2S1210_SET_RES0		0x01

#define AD2S1210_SET_ENRESOLUTION	(AD2S1210_SET_ENRES1 |	\
					 AD2S1210_SET_ENRES0)
#define AD2S1210_SET_RESOLUTION		(AD2S1210_SET_RES1 | AD2S1210_SET_RES0)

#define AD2S1210_REG_POSITION		0x80
#define AD2S1210_REG_VELOCITY		0x82
#define AD2S1210_REG_LOS_THRD		0x88
#define AD2S1210_REG_DOS_OVR_THRD	0x89
#define AD2S1210_REG_DOS_MIS_THRD	0x8A
#define AD2S1210_REG_DOS_RST_MAX_THRD	0x8B
#define AD2S1210_REG_DOS_RST_MIN_THRD	0x8C
#define AD2S1210_REG_LOT_HIGH_THRD	0x8D
#define AD2S1210_REG_LOT_LOW_THRD	0x8E
#define AD2S1210_REG_EXCIT_FREQ		0x91
#define AD2S1210_REG_CONTROL		0x92
#define AD2S1210_REG_SOFT_RESET		0xF0
#define AD2S1210_REG_FAULT		0xFF

/* pin SAMPLE, A0, A1, RES0, RES1, is controlled by driver */
#define AD2S1210_SAA		3
>>>>>>> cm-10.0
#define AD2S1210_PN		(AD2S1210_SAA + AD2S1210_RES)

#define AD2S1210_MIN_CLKIN	6144000
#define AD2S1210_MAX_CLKIN	10240000
#define AD2S1210_MIN_EXCIT	2000
#define AD2S1210_MAX_EXCIT	20000
#define AD2S1210_MIN_FCW	0x4
#define AD2S1210_MAX_FCW	0x50

/* default input clock on serial interface */
#define AD2S1210_DEF_CLKIN	8192000
/* clock period in nano second */
#define AD2S1210_DEF_TCK	(1000000000/AD2S1210_DEF_CLKIN)
#define AD2S1210_DEF_EXCIT	10000

enum ad2s1210_mode {
	MOD_POS = 0,
	MOD_VEL,
<<<<<<< HEAD
	MOD_RESERVED,
	MOD_CONFIG,
};

enum ad2s1210_res {
	RES_10 = 10,
	RES_12 = 12,
	RES_14 = 14,
	RES_16 = 16,
};

static unsigned int resolution_value[] = {
		RES_10, RES_12, RES_14, RES_16};

struct ad2s1210_state {
	struct mutex lock;
	struct iio_dev *idev;
	struct spi_device *sdev;
	struct spi_transfer xfer;
	unsigned int hysteresis;
	unsigned int old_data;
	enum ad2s1210_mode mode;
	enum ad2s1210_res resolution;
	unsigned int fclkin;
	unsigned int fexcit;
	unsigned short sample;
	unsigned short a0;
	unsigned short a1;
	unsigned short res0;
	unsigned short res1;
	u8 rx[3];
	u8 tx[3];
};

static inline void start_sample(struct ad2s1210_state *st)
{
	gpio_set_value(st->sample, 0);
}

static inline void stop_sample(struct ad2s1210_state *st)
{
	gpio_set_value(st->sample, 1);
}

static inline void set_mode(enum ad2s1210_mode mode, struct ad2s1210_state *st)
{
	switch (mode) {
	case MOD_POS:
		gpio_set_value(st->a0, 0);
		gpio_set_value(st->a1, 0);
		break;
	case MOD_VEL:
		gpio_set_value(st->a0, 0);
		gpio_set_value(st->a1, 1);
		break;
	case MOD_CONFIG:
		gpio_set_value(st->a0, 1);
		gpio_set_value(st->a1, 1);
		break;
	default:
		/* set to reserved mode */
		gpio_set_value(st->a0, 1);
		gpio_set_value(st->a1, 0);
	}
=======
	MOD_CONFIG,
	MOD_RESERVED,
};

static const unsigned int ad2s1210_resolution_value[] = { 10, 12, 14, 16 };

struct ad2s1210_state {
	const struct ad2s1210_platform_data *pdata;
	struct mutex lock;
	struct spi_device *sdev;
	unsigned int fclkin;
	unsigned int fexcit;
	bool hysteresis;
	bool old_data;
	u8 resolution;
	enum ad2s1210_mode mode;
	u8 rx[2] ____cacheline_aligned;
	u8 tx[2] ____cacheline_aligned;
};

static const int ad2s1210_mode_vals[4][2] = {
	[MOD_POS] = { 0, 0 },
	[MOD_VEL] = { 0, 1 },
	[MOD_CONFIG] = { 1, 0 },
};
static inline void ad2s1210_set_mode(enum ad2s1210_mode mode,
				     struct ad2s1210_state *st)
{
	gpio_set_value(st->pdata->a[0], ad2s1210_mode_vals[mode][0]);
	gpio_set_value(st->pdata->a[1], ad2s1210_mode_vals[mode][1]);
>>>>>>> cm-10.0
	st->mode = mode;
}

/* write 1 bytes (address or data) to the chip */
<<<<<<< HEAD
static int config_write(struct ad2s1210_state *st,
					unsigned char data)
{
	struct spi_message msg;
	int ret = 0;

	st->xfer.len = 1;
	set_mode(MOD_CONFIG, st);

	spi_message_init(&msg);
	spi_message_add_tail(&st->xfer, &msg);
	st->tx[0] = data;
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		return ret;
	st->old_data = 1;
	return ret;
}

/* read value from one of the registers */
static int config_read(struct ad2s1210_state *st,
				unsigned char address,
					unsigned char *data)
{
	struct spi_message msg;
	int ret = 0;

	st->xfer.len = 2;
	set_mode(MOD_CONFIG, st);

	spi_message_init(&msg);
	spi_message_add_tail(&st->xfer, &msg);
	st->tx[0] = address | MSB_IS_HIGH;
	st->tx[1] = REG_FAULT;
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		return ret;
	*data = st->rx[1];
	st->old_data = 1;
	return ret;
}

static inline void update_frequency_control_word(struct ad2s1210_state *st)
{
	unsigned char fcw;
	fcw = (unsigned char)(st->fexcit * (1 << 15) / st->fclkin);
	if (fcw >= AD2S1210_MIN_FCW && fcw <= AD2S1210_MAX_FCW) {
		config_write(st, REG_EXCIT_FREQ);
		config_write(st, fcw);
	} else
		pr_err("ad2s1210: FCW out of range\n");
}

#if defined(CONFIG_AD2S1210_GPIO_INPUT)
static inline unsigned char read_resolution_pin(struct ad2s1210_state *st)
{
	unsigned int data;
	data = (gpio_get_value(st->res0) << 1)  |
			gpio_get_value(st->res1);
	return resolution_value[data];
}
#elif defined(CONFIG_AD2S1210_GPIO_OUTPUT)
static inline void set_resolution_pin(struct ad2s1210_state *st)
{
	switch (st->resolution) {
	case RES_10:
		gpio_set_value(st->res0, 0);
		gpio_set_value(st->res1, 0);
		break;
	case RES_12:
		gpio_set_value(st->res0, 0);
		gpio_set_value(st->res1, 1);
		break;
	case RES_14:
		gpio_set_value(st->res0, 1);
		gpio_set_value(st->res1, 0);
		break;
	case RES_16:
		gpio_set_value(st->res0, 1);
		gpio_set_value(st->res1, 1);
		break;
	}
}
#endif

static inline void soft_reset(struct ad2s1210_state *st)
{
	config_write(st, REG_SOFT_RESET);
	config_write(st, 0x0);
}


/* return the OLD DATA since last spi bus write */
static ssize_t ad2s1210_show_raw(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
	int ret;

	mutex_lock(&st->lock);
	if (st->old_data) {
		ret = sprintf(buf, "0x%x\n", st->rx[0]);
		st->old_data = 0;
	} else
		ret = 0;
	mutex_unlock(&st->lock);
	return ret;
}

static ssize_t ad2s1210_store_raw(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t len)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
	unsigned long udata;
	unsigned char data;
	int ret;

	ret = strict_strtoul(buf, 16, &udata);
	if (ret)
		return -EINVAL;
	data = udata & 0xff;
	mutex_lock(&st->lock);
	config_write(st, data);
	mutex_unlock(&st->lock);
	return 1;
}

static ssize_t ad2s1210_store_softreset(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t len)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
	mutex_lock(&st->lock);
	soft_reset(st);
	mutex_unlock(&st->lock);
	return len;
}

static ssize_t ad2s1210_show_fclkin(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
static int ad2s1210_config_write(struct ad2s1210_state *st, u8 data)
{
	int ret;

	ad2s1210_set_mode(MOD_CONFIG, st);
	st->tx[0] = data;
	ret = spi_write(st->sdev, st->tx, 1);
	if (ret < 0)
		return ret;
	st->old_data = true;

	return 0;
}

/* read value from one of the registers */
static int ad2s1210_config_read(struct ad2s1210_state *st,
		       unsigned char address)
{
	struct spi_transfer xfer = {
		.len = 2,
		.rx_buf = st->rx,
		.tx_buf = st->tx,
	};
	struct spi_message msg;
	int ret = 0;

	ad2s1210_set_mode(MOD_CONFIG, st);
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	st->tx[0] = address | AD2S1210_MSB_IS_HIGH;
	st->tx[1] = AD2S1210_REG_FAULT;
	ret = spi_sync(st->sdev, &msg);
	if (ret < 0)
		return ret;
	st->old_data = true;

	return st->rx[1];
}

static inline
int ad2s1210_update_frequency_control_word(struct ad2s1210_state *st)
{
	int ret;
	unsigned char fcw;

	fcw = (unsigned char)(st->fexcit * (1 << 15) / st->fclkin);
	if (fcw < AD2S1210_MIN_FCW || fcw > AD2S1210_MAX_FCW) {
		pr_err("ad2s1210: FCW out of range\n");
		return -ERANGE;
	}

	ret = ad2s1210_config_write(st, AD2S1210_REG_EXCIT_FREQ);
	if (ret < 0)
		return ret;

	return ad2s1210_config_write(st, fcw);
}

static unsigned char ad2s1210_read_resolution_pin(struct ad2s1210_state *st)
{
	return ad2s1210_resolution_value[
		(gpio_get_value(st->pdata->res[0]) << 1) |
		gpio_get_value(st->pdata->res[1])];
}

static const int ad2s1210_res_pins[4][2] = {
	{ 0, 0 }, {0, 1}, {1, 0}, {1, 1}
};

static inline void ad2s1210_set_resolution_pin(struct ad2s1210_state *st)
{
	gpio_set_value(st->pdata->res[0],
		       ad2s1210_res_pins[(st->resolution - 10)/2][0]);
	gpio_set_value(st->pdata->res[1],
		       ad2s1210_res_pins[(st->resolution - 10)/2][1]);
}

static inline int ad2s1210_soft_reset(struct ad2s1210_state *st)
{
	int ret;

	ret = ad2s1210_config_write(st, AD2S1210_REG_SOFT_RESET);
	if (ret < 0)
		return ret;

	return ad2s1210_config_write(st, 0x0);
}

static ssize_t ad2s1210_store_softreset(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
	int ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_soft_reset(st);
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : len;
}

static ssize_t ad2s1210_show_fclkin(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	return sprintf(buf, "%d\n", st->fclkin);
}

static ssize_t ad2s1210_store_fclkin(struct device *dev,
<<<<<<< HEAD
			struct device_attribute *attr,
			const char *buf, size_t len)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
				     struct device_attribute *attr,
				     const char *buf,
				     size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	unsigned long fclkin;
	int ret;

	ret = strict_strtoul(buf, 10, &fclkin);
<<<<<<< HEAD
	if (!ret && fclkin >= AD2S1210_MIN_CLKIN &&
				fclkin <= AD2S1210_MAX_CLKIN) {
		mutex_lock(&st->lock);
		st->fclkin = fclkin;
	} else {
		pr_err("ad2s1210: fclkin out of range\n");
		return -EINVAL;
	}
	update_frequency_control_word(st);
	soft_reset(st);
	mutex_unlock(&st->lock);
	return len;
}

static ssize_t ad2s1210_show_fexcit(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
	if (ret)
		return ret;
	if (fclkin < AD2S1210_MIN_CLKIN || fclkin > AD2S1210_MAX_CLKIN) {
		pr_err("ad2s1210: fclkin out of range\n");
		return -EINVAL;
	}

	mutex_lock(&st->lock);
	st->fclkin = fclkin;

	ret = ad2s1210_update_frequency_control_word(st);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_soft_reset(st);
error_ret:
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : len;
}

static ssize_t ad2s1210_show_fexcit(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	return sprintf(buf, "%d\n", st->fexcit);
}

static ssize_t ad2s1210_store_fexcit(struct device *dev,
<<<<<<< HEAD
			struct device_attribute *attr,
			const char *buf, size_t len)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
				     struct device_attribute *attr,
				     const char *buf, size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	unsigned long fexcit;
	int ret;

	ret = strict_strtoul(buf, 10, &fexcit);
<<<<<<< HEAD
	if (!ret && fexcit >= AD2S1210_MIN_EXCIT &&
				fexcit <= AD2S1210_MAX_EXCIT) {
		mutex_lock(&st->lock);
		st->fexcit = fexcit;
	} else {
		pr_err("ad2s1210: excitation frequency out of range\n");
		return -EINVAL;
	}
	update_frequency_control_word(st);
	soft_reset(st);
	mutex_unlock(&st->lock);
	return len;
}

static ssize_t ad2s1210_show_control(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
	unsigned char data;
	mutex_lock(&st->lock);
	config_read(st, REG_CONTROL, &data);
	mutex_unlock(&st->lock);
	return sprintf(buf, "0x%x\n", data);
=======
	if (ret < 0)
		return ret;
	if (fexcit < AD2S1210_MIN_EXCIT || fexcit > AD2S1210_MAX_EXCIT) {
		pr_err("ad2s1210: excitation frequency out of range\n");
		return -EINVAL;
	}
	mutex_lock(&st->lock);
	st->fexcit = fexcit;
	ret = ad2s1210_update_frequency_control_word(st);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_soft_reset(st);
error_ret:
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : len;
}

static ssize_t ad2s1210_show_control(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
	int ret;
	mutex_lock(&st->lock);
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	mutex_unlock(&st->lock);
	return ret < 0 ? ret : sprintf(buf, "0x%x\n", ret);
>>>>>>> cm-10.0
}

static ssize_t ad2s1210_store_control(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t len)
{
<<<<<<< HEAD
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	unsigned long udata;
	unsigned char data;
	int ret;

	ret = strict_strtoul(buf, 16, &udata);
<<<<<<< HEAD
	if (ret) {
		ret = -EINVAL;
		goto error_ret;
	}
	mutex_lock(&st->lock);
	config_write(st, REG_CONTROL);
	data = udata & MSB_IS_LOW;
	config_write(st, data);
	config_read(st, REG_CONTROL, &data);
	if (data & MSB_IS_HIGH) {
=======
	if (ret)
		return -EINVAL;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_write(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = udata & AD2S1210_MSB_IS_LOW;
	ret = ad2s1210_config_write(st, data);
	if (ret < 0)
		goto error_ret;

	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	if (ret & AD2S1210_MSB_IS_HIGH) {
>>>>>>> cm-10.0
		ret = -EIO;
		pr_err("ad2s1210: write control register fail\n");
		goto error_ret;
	}
<<<<<<< HEAD
	st->resolution = resolution_value[data & SET_RESOLUTION];
#if defined(CONFIG_AD2S1210_GPIO_INPUT)
	data = read_resolution_pin(st);
	if (data != st->resolution)
		pr_warning("ad2s1210: resolution settings not match\n");
#elif defined(CONFIG_AD2S1210_GPIO_OUTPUT)
	set_resolution_pin(st);
#endif
	ret = len;
	if (data & ENABLE_HYSTERESIS)
		st->hysteresis = 1;
	else
		st->hysteresis = 0;
=======
	st->resolution
		= ad2s1210_resolution_value[data & AD2S1210_SET_RESOLUTION];
	if (st->pdata->gpioin) {
		data = ad2s1210_read_resolution_pin(st);
		if (data != st->resolution)
			pr_warning("ad2s1210: resolution settings not match\n");
	} else
		ad2s1210_set_resolution_pin(st);

	ret = len;
	st->hysteresis = !!(data & AD2S1210_ENABLE_HYSTERESIS);

>>>>>>> cm-10.0
error_ret:
	mutex_unlock(&st->lock);
	return ret;
}

static ssize_t ad2s1210_show_resolution(struct device *dev,
			struct device_attribute *attr, char *buf)
{
<<<<<<< HEAD
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	return sprintf(buf, "%d\n", st->resolution);
}

static ssize_t ad2s1210_store_resolution(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t len)
{
<<<<<<< HEAD
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	unsigned char data;
	unsigned long udata;
	int ret;

	ret = strict_strtoul(buf, 10, &udata);
<<<<<<< HEAD
	if (ret || udata < RES_10 || udata > RES_16) {
=======
	if (ret || udata < 10 || udata > 16) {
>>>>>>> cm-10.0
		pr_err("ad2s1210: resolution out of range\n");
		return -EINVAL;
	}
	mutex_lock(&st->lock);
<<<<<<< HEAD
	config_read(st, REG_CONTROL, &data);
	data &= ~SET_RESOLUTION;
	data |= (udata - RES_10) >> 1;
	config_write(st, REG_CONTROL);
	config_write(st, data & MSB_IS_LOW);
	config_read(st, REG_CONTROL, &data);
	if (data & MSB_IS_HIGH) {
=======
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = ret;
	data &= ~AD2S1210_SET_RESOLUTION;
	data |= (udata - 10) >> 1;
	ret = ad2s1210_config_write(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_write(st, data & AD2S1210_MSB_IS_LOW);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = ret;
	if (data & AD2S1210_MSB_IS_HIGH) {
>>>>>>> cm-10.0
		ret = -EIO;
		pr_err("ad2s1210: setting resolution fail\n");
		goto error_ret;
	}
<<<<<<< HEAD
	st->resolution = resolution_value[data & SET_RESOLUTION];
#if defined(CONFIG_AD2S1210_GPIO_INPUT)
	data = read_resolution_pin(st);
	if (data != st->resolution)
		pr_warning("ad2s1210: resolution settings not match\n");
#elif defined(CONFIG_AD2S1210_GPIO_OUTPUT)
	set_resolution_pin(st);
#endif
=======
	st->resolution
		= ad2s1210_resolution_value[data & AD2S1210_SET_RESOLUTION];
	if (st->pdata->gpioin) {
		data = ad2s1210_read_resolution_pin(st);
		if (data != st->resolution)
			pr_warning("ad2s1210: resolution settings not match\n");
	} else
		ad2s1210_set_resolution_pin(st);
>>>>>>> cm-10.0
	ret = len;
error_ret:
	mutex_unlock(&st->lock);
	return ret;
}
<<<<<<< HEAD
=======

>>>>>>> cm-10.0
/* read the fault register since last sample */
static ssize_t ad2s1210_show_fault(struct device *dev,
			struct device_attribute *attr, char *buf)
{
<<<<<<< HEAD
	int ret = 0;
	ssize_t len = 0;
	unsigned char data;
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;

	mutex_lock(&st->lock);
	ret = config_read(st, REG_FAULT, &data);

	if (ret)
		goto error_ret;
	len = sprintf(buf, "0x%x\n", data);
error_ret:
	mutex_unlock(&st->lock);
	return ret ? ret : len;
}

static ssize_t ad2s1210_clear_fault(struct device *dev,
			struct device_attribute *attr,
			const char *buf, size_t len)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
	unsigned char data;

	mutex_lock(&st->lock);
	start_sample(st);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	stop_sample(st);
	config_read(st, REG_FAULT, &data);
	start_sample(st);
	stop_sample(st);
	mutex_unlock(&st->lock);

	return 0;
}

static ssize_t ad2s1210_show_reg(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
	unsigned char data;
	struct iio_dev_attr *iattr = to_iio_dev_attr(attr);

	mutex_lock(&st->lock);
	config_read(st, iattr->address, &data);
	mutex_unlock(&st->lock);
	return sprintf(buf, "%d\n", data);
=======
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
	int ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_read(st, AD2S1210_REG_FAULT);
	mutex_unlock(&st->lock);

	return ret ? ret : sprintf(buf, "0x%x\n", ret);
}

static ssize_t ad2s1210_clear_fault(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
	int ret;

	mutex_lock(&st->lock);
	gpio_set_value(st->pdata->sample, 0);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	gpio_set_value(st->pdata->sample, 1);
	ret = ad2s1210_config_read(st, AD2S1210_REG_FAULT);
	if (ret < 0)
		goto error_ret;
	gpio_set_value(st->pdata->sample, 0);
	gpio_set_value(st->pdata->sample, 1);
error_ret:
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : len;
}

static ssize_t ad2s1210_show_reg(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
	struct iio_dev_attr *iattr = to_iio_dev_attr(attr);
	int ret;

	mutex_lock(&st->lock);
	ret = ad2s1210_config_read(st, iattr->address);
	mutex_unlock(&st->lock);

	return ret < 0 ? ret : sprintf(buf, "%d\n", ret);
>>>>>>> cm-10.0
}

static ssize_t ad2s1210_store_reg(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
<<<<<<< HEAD
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;
=======
	struct ad2s1210_state *st = iio_priv(dev_get_drvdata(dev));
>>>>>>> cm-10.0
	unsigned long data;
	int ret;
	struct iio_dev_attr *iattr = to_iio_dev_attr(attr);

	ret = strict_strtoul(buf, 10, &data);
	if (ret)
		return -EINVAL;
	mutex_lock(&st->lock);
<<<<<<< HEAD
	config_write(st, iattr->address);
	config_write(st, data & MSB_IS_LOW);
	mutex_unlock(&st->lock);
	return len;
}

static ssize_t ad2s1210_show_pos(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct spi_message msg;
	int ret = 0;
	ssize_t len = 0;
	u16 pos;
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;

	st->xfer.len = 2;
	mutex_lock(&st->lock);
	start_sample(st);
	/* delay (6 * tck + 20) nano seconds */
	udelay(1);

	set_mode(MOD_POS, st);

	spi_message_init(&msg);
	spi_message_add_tail(&st->xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
	pos = ((((u16)(st->rx[0])) << 8) | (st->rx[1]));
	if (st->hysteresis)
		pos >>= 16 - st->resolution;
	len = sprintf(buf, "%d\n", pos);
error_ret:
	stop_sample(st);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static ssize_t ad2s1210_show_vel(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct spi_message msg;
	unsigned short negative;
	int ret = 0;
	ssize_t len = 0;
	s16 vel;
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;

	st->xfer.len = 2;
	mutex_lock(&st->lock);
	start_sample(st);
	/* delay (6 * tck + 20) nano seconds */
	udelay(1);

	set_mode(MOD_VEL, st);

	spi_message_init(&msg);
	spi_message_add_tail(&st->xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
	negative = st->rx[0] & 0x80;
	vel = ((((s16)(st->rx[0])) << 8) | (st->rx[1]));
	vel >>= 16 - st->resolution;
	if (negative) {
		negative = (0xffff >> st->resolution) << st->resolution;
		vel |= negative;
	}
	len = sprintf(buf, "%d\n", vel);
error_ret:
	stop_sample(st);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static ssize_t ad2s1210_show_pos_vel(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct spi_message msg;
	unsigned short negative;
	int ret = 0;
	ssize_t len = 0;
	u16 pos;
	s16 vel;
	struct iio_dev *idev = dev_get_drvdata(dev);
	struct ad2s1210_state *st = idev->dev_data;

	st->xfer.len = 2;
	mutex_lock(&st->lock);
	start_sample(st);
	/* delay (6 * tck + 20) nano seconds */
	udelay(1);

	set_mode(MOD_POS, st);

	spi_message_init(&msg);
	spi_message_add_tail(&st->xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
	pos = ((((u16)(st->rx[0])) << 8) | (st->rx[1]));
	if (st->hysteresis)
		pos >>= 16 - st->resolution;
	len = sprintf(buf, "%d ", pos);

	st->xfer.len = 2;
	set_mode(MOD_VEL, st);
	spi_message_init(&msg);
	spi_message_add_tail(&st->xfer, &msg);
	ret = spi_sync(st->sdev, &msg);
	if (ret)
		goto error_ret;
	negative = st->rx[0] & 0x80;
	vel = ((((s16)(st->rx[0])) << 8) | (st->rx[1]));
	vel >>= 16 - st->resolution;
	if (negative) {
		negative = (0xffff >> st->resolution) << st->resolution;
		vel |= negative;
	}
	len += sprintf(buf + len, "%d\n", vel);
error_ret:
	stop_sample(st);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static IIO_CONST_ATTR(description,
	"Variable Resolution, 10-Bit to 16Bit R/D\n\
Converter with Reference Oscillator");
static IIO_DEVICE_ATTR(raw_io, S_IRUGO | S_IWUSR,
		ad2s1210_show_raw, ad2s1210_store_raw, 0);
static IIO_DEVICE_ATTR(reset, S_IWUSR,
		NULL, ad2s1210_store_softreset, 0);
static IIO_DEVICE_ATTR(fclkin, S_IRUGO | S_IWUSR,
		ad2s1210_show_fclkin, ad2s1210_store_fclkin, 0);
static IIO_DEVICE_ATTR(fexcit, S_IRUGO | S_IWUSR,
		ad2s1210_show_fexcit,	ad2s1210_store_fexcit, 0);
static IIO_DEVICE_ATTR(control, S_IRUGO | S_IWUSR,
		ad2s1210_show_control, ad2s1210_store_control, 0);
static IIO_DEVICE_ATTR(bits, S_IRUGO | S_IWUSR,
		ad2s1210_show_resolution, ad2s1210_store_resolution, 0);
static IIO_DEVICE_ATTR(fault, S_IRUGO | S_IWUSR,
		ad2s1210_show_fault, ad2s1210_clear_fault, 0);
static IIO_DEVICE_ATTR(pos, S_IRUGO,
		ad2s1210_show_pos, NULL, 0);
static IIO_DEVICE_ATTR(vel, S_IRUGO,
		ad2s1210_show_vel, NULL, 0);
static IIO_DEVICE_ATTR(pos_vel, S_IRUGO,
		ad2s1210_show_pos_vel, NULL, 0);
static IIO_DEVICE_ATTR(los_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_LOS_THRD);
static IIO_DEVICE_ATTR(dos_ovr_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_DOS_OVR_THRD);
static IIO_DEVICE_ATTR(dos_mis_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_DOS_MIS_THRD);
static IIO_DEVICE_ATTR(dos_rst_max_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_DOS_RST_MAX_THRD);
static IIO_DEVICE_ATTR(dos_rst_min_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_DOS_RST_MIN_THRD);
static IIO_DEVICE_ATTR(lot_high_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_LOT_HIGH_THRD);
static IIO_DEVICE_ATTR(lot_low_thrd, S_IRUGO | S_IWUSR,
		ad2s1210_show_reg, ad2s1210_store_reg, REG_LOT_LOW_THRD);

static struct attribute *ad2s1210_attributes[] = {
	&iio_const_attr_description.dev_attr.attr,
	&iio_dev_attr_raw_io.dev_attr.attr,
=======
	ret = ad2s1210_config_write(st, iattr->address);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_write(st, data & AD2S1210_MSB_IS_LOW);
error_ret:
	mutex_unlock(&st->lock);
	return ret < 0 ? ret : len;
}

static int ad2s1210_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val,
			     int *val2,
			     long m)
{
	struct ad2s1210_state *st = iio_priv(indio_dev);
	bool negative;
	int ret = 0;
	u16 pos;
	s16 vel;

	mutex_lock(&st->lock);
	gpio_set_value(st->pdata->sample, 0);
	/* delay (6 * tck + 20) nano seconds */
	udelay(1);

	switch (chan->type) {
	case IIO_ANGL:
		ad2s1210_set_mode(MOD_POS, st);
		break;
	case IIO_ANGL_VEL:
		ad2s1210_set_mode(MOD_VEL, st);
		break;
	default:
	       ret = -EINVAL;
	       break;
	}
	if (ret < 0)
		goto error_ret;
	ret = spi_read(st->sdev, st->rx, 2);
	if (ret < 0)
		goto error_ret;

	switch (chan->type) {
	case IIO_ANGL:
		pos = be16_to_cpup((u16 *)st->rx);
		if (st->hysteresis)
			pos >>= 16 - st->resolution;
		*val = pos;
		ret = IIO_VAL_INT;
		break;
	case IIO_ANGL_VEL:
		negative = st->rx[0] & 0x80;
		vel = be16_to_cpup((s16 *)st->rx);
		vel >>= 16 - st->resolution;
		if (vel & 0x8000) {
			negative = (0xffff >> st->resolution) << st->resolution;
			vel |= negative;
		}
		*val = vel;
		ret = IIO_VAL_INT;
		break;
	default:
		mutex_unlock(&st->lock);
		return -EINVAL;
	}

error_ret:
	gpio_set_value(st->pdata->sample, 1);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	mutex_unlock(&st->lock);
	return ret;
}

static IIO_DEVICE_ATTR(reset, S_IWUSR,
		       NULL, ad2s1210_store_softreset, 0);
static IIO_DEVICE_ATTR(fclkin, S_IRUGO | S_IWUSR,
		       ad2s1210_show_fclkin, ad2s1210_store_fclkin, 0);
static IIO_DEVICE_ATTR(fexcit, S_IRUGO | S_IWUSR,
		       ad2s1210_show_fexcit,	ad2s1210_store_fexcit, 0);
static IIO_DEVICE_ATTR(control, S_IRUGO | S_IWUSR,
		       ad2s1210_show_control, ad2s1210_store_control, 0);
static IIO_DEVICE_ATTR(bits, S_IRUGO | S_IWUSR,
		       ad2s1210_show_resolution, ad2s1210_store_resolution, 0);
static IIO_DEVICE_ATTR(fault, S_IRUGO | S_IWUSR,
		       ad2s1210_show_fault, ad2s1210_clear_fault, 0);

static IIO_DEVICE_ATTR(los_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_LOS_THRD);
static IIO_DEVICE_ATTR(dos_ovr_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_OVR_THRD);
static IIO_DEVICE_ATTR(dos_mis_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_MIS_THRD);
static IIO_DEVICE_ATTR(dos_rst_max_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_RST_MAX_THRD);
static IIO_DEVICE_ATTR(dos_rst_min_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_DOS_RST_MIN_THRD);
static IIO_DEVICE_ATTR(lot_high_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_LOT_HIGH_THRD);
static IIO_DEVICE_ATTR(lot_low_thrd, S_IRUGO | S_IWUSR,
		       ad2s1210_show_reg, ad2s1210_store_reg,
		       AD2S1210_REG_LOT_LOW_THRD);


static struct iio_chan_spec ad2s1210_channels[] = {
	{
		.type = IIO_ANGL,
		.indexed = 1,
		.channel = 0,
	}, {
		.type = IIO_ANGL_VEL,
		.indexed = 1,
		.channel = 0,
	}
};

static struct attribute *ad2s1210_attributes[] = {
>>>>>>> cm-10.0
	&iio_dev_attr_reset.dev_attr.attr,
	&iio_dev_attr_fclkin.dev_attr.attr,
	&iio_dev_attr_fexcit.dev_attr.attr,
	&iio_dev_attr_control.dev_attr.attr,
	&iio_dev_attr_bits.dev_attr.attr,
	&iio_dev_attr_fault.dev_attr.attr,
<<<<<<< HEAD
	&iio_dev_attr_pos.dev_attr.attr,
	&iio_dev_attr_vel.dev_attr.attr,
	&iio_dev_attr_pos_vel.dev_attr.attr,
=======
>>>>>>> cm-10.0
	&iio_dev_attr_los_thrd.dev_attr.attr,
	&iio_dev_attr_dos_ovr_thrd.dev_attr.attr,
	&iio_dev_attr_dos_mis_thrd.dev_attr.attr,
	&iio_dev_attr_dos_rst_max_thrd.dev_attr.attr,
	&iio_dev_attr_dos_rst_min_thrd.dev_attr.attr,
	&iio_dev_attr_lot_high_thrd.dev_attr.attr,
	&iio_dev_attr_lot_low_thrd.dev_attr.attr,
	NULL,
};

static const struct attribute_group ad2s1210_attribute_group = {
<<<<<<< HEAD
	.name = DRV_NAME,
=======
>>>>>>> cm-10.0
	.attrs = ad2s1210_attributes,
};

static int __devinit ad2s1210_initial(struct ad2s1210_state *st)
{
	unsigned char data;
	int ret;

	mutex_lock(&st->lock);
<<<<<<< HEAD
#if defined(CONFIG_AD2S1210_GPIO_INPUT)
	st->resolution = read_resolution_pin(st);
#elif defined(CONFIG_AD2S1210_GPIO_OUTPUT)
	set_resolution_pin(st);
#endif

	config_write(st, REG_CONTROL);
	data = DEF_CONTROL & ~(SET_RESOLUTION);
	data |= (st->resolution - RES_10) >> 1;
	config_write(st, data);
	ret = config_read(st, REG_CONTROL, &data);
	if (ret)
		goto error_ret;

	if (data & MSB_IS_HIGH) {
=======
	if (st->pdata->gpioin)
		st->resolution = ad2s1210_read_resolution_pin(st);
	else
		ad2s1210_set_resolution_pin(st);

	ret = ad2s1210_config_write(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;
	data = AD2S1210_DEF_CONTROL & ~(AD2S1210_SET_RESOLUTION);
	data |= (st->resolution - 10) >> 1;
	ret = ad2s1210_config_write(st, data);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_read(st, AD2S1210_REG_CONTROL);
	if (ret < 0)
		goto error_ret;

	if (ret & AD2S1210_MSB_IS_HIGH) {
>>>>>>> cm-10.0
		ret = -EIO;
		goto error_ret;
	}

<<<<<<< HEAD
	update_frequency_control_word(st);
	soft_reset(st);
=======
	ret = ad2s1210_update_frequency_control_word(st);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_soft_reset(st);
>>>>>>> cm-10.0
error_ret:
	mutex_unlock(&st->lock);
	return ret;
}

static const struct iio_info ad2s1210_info = {
<<<<<<< HEAD
=======
	.read_raw = &ad2s1210_read_raw,
>>>>>>> cm-10.0
	.attrs = &ad2s1210_attribute_group,
	.driver_module = THIS_MODULE,
};

<<<<<<< HEAD
static int __devinit ad2s1210_probe(struct spi_device *spi)
{
	struct ad2s1210_state *st;
	int pn, ret = 0;
	unsigned short *pins = spi->dev.platform_data;

	for (pn = 0; pn < AD2S1210_PN; pn++) {
		if (gpio_request(pins[pn], DRV_NAME)) {
			pr_err("%s: request gpio pin %d failed\n",
						DRV_NAME, pins[pn]);
			goto error_ret;
		}
		if (pn < AD2S1210_SAA)
			gpio_direction_output(pins[pn], 1);
		else {
#if defined(CONFIG_AD2S1210_GPIO_INPUT)
			gpio_direction_input(pins[pn]);
#elif defined(CONFIG_AD2S1210_GPIO_OUTPUT)
			gpio_direction_output(pins[pn], 1);
#endif
		}
	}

	st = kzalloc(sizeof(*st), GFP_KERNEL);
	if (st == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	spi_set_drvdata(spi, st);

	mutex_init(&st->lock);
	st->sdev = spi;
	st->xfer.tx_buf = st->tx;
	st->xfer.rx_buf = st->rx;
	st->hysteresis = 1;
	st->mode = MOD_CONFIG;
	st->resolution = RES_12;
	st->fclkin = AD2S1210_DEF_CLKIN;
	st->fexcit = AD2S1210_DEF_EXCIT;
	st->sample = pins[0];
	st->a0 = pins[1];
	st->a1 = pins[2];
	st->res0 = pins[3];
	st->res1 = pins[4];

	st->idev = iio_allocate_device(0);
	if (st->idev == NULL) {
		ret = -ENOMEM;
		goto error_free_st;
	}
	st->idev->dev.parent = &spi->dev;

	st->idev->info = &ad2s1210_info;
	st->idev->dev_data = (void *)(st);
	st->idev->modes = INDIO_DIRECT_MODE;

	ret = iio_device_register(st->idev);
	if (ret)
		goto error_free_dev;

	if (spi->max_speed_hz != AD2S1210_DEF_CLKIN)
		st->fclkin = spi->max_speed_hz;
	spi->mode = SPI_MODE_3;
	spi_setup(spi);

	ad2s1210_initial(st);
	return 0;

error_free_dev:
	iio_free_device(st->idev);
error_free_st:
	kfree(st);
error_ret:
	for (--pn; pn >= 0; pn--)
		gpio_free(pins[pn]);
=======
static int ad2s1210_setup_gpios(struct ad2s1210_state *st)
{
	unsigned long flags = st->pdata->gpioin ? GPIOF_DIR_IN : GPIOF_DIR_OUT;
	struct gpio ad2s1210_gpios[] = {
		{ st->pdata->sample, GPIOF_DIR_IN, "sample" },
		{ st->pdata->a[0], flags, "a0" },
		{ st->pdata->a[1], flags, "a1" },
		{ st->pdata->res[0], flags, "res0" },
		{ st->pdata->res[0], flags, "res1" },
	};

	return gpio_request_array(ad2s1210_gpios, ARRAY_SIZE(ad2s1210_gpios));
}

static void ad2s1210_free_gpios(struct ad2s1210_state *st)
{
	unsigned long flags = st->pdata->gpioin ? GPIOF_DIR_IN : GPIOF_DIR_OUT;
	struct gpio ad2s1210_gpios[] = {
		{ st->pdata->sample, GPIOF_DIR_IN, "sample" },
		{ st->pdata->a[0], flags, "a0" },
		{ st->pdata->a[1], flags, "a1" },
		{ st->pdata->res[0], flags, "res0" },
		{ st->pdata->res[0], flags, "res1" },
	};

	gpio_free_array(ad2s1210_gpios, ARRAY_SIZE(ad2s1210_gpios));
}

static int __devinit ad2s1210_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct ad2s1210_state *st;
	int ret;

	if (spi->dev.platform_data == NULL)
		return -EINVAL;

	indio_dev = iio_allocate_device(sizeof(*st));
	if (indio_dev == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	st = iio_priv(indio_dev);
	st->pdata = spi->dev.platform_data;
	ret = ad2s1210_setup_gpios(st);
	if (ret < 0)
		goto error_free_dev;

	spi_set_drvdata(spi, indio_dev);

	mutex_init(&st->lock);
	st->sdev = spi;
	st->hysteresis = true;
	st->mode = MOD_CONFIG;
	st->resolution = 12;
	st->fexcit = AD2S1210_DEF_EXCIT;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ad2s1210_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad2s1210_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad2s1210_channels);
	indio_dev->name = spi_get_device_id(spi)->name;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_free_gpios;

	st->fclkin = spi->max_speed_hz;
	spi->mode = SPI_MODE_3;
	spi_setup(spi);
	ad2s1210_initial(st);

	return 0;

error_free_gpios:
	ad2s1210_free_gpios(st);
error_free_dev:
	iio_free_device(indio_dev);
error_ret:
>>>>>>> cm-10.0
	return ret;
}

static int __devexit ad2s1210_remove(struct spi_device *spi)
{
<<<<<<< HEAD
	struct ad2s1210_state *st = spi_get_drvdata(spi);

	iio_device_unregister(st->idev);
	kfree(st);
=======
	struct iio_dev *indio_dev = spi_get_drvdata(spi);

	iio_device_unregister(indio_dev);
	ad2s1210_free_gpios(iio_priv(indio_dev));
	iio_free_device(indio_dev);
>>>>>>> cm-10.0

	return 0;
}

<<<<<<< HEAD
=======
static const struct spi_device_id ad2s1210_id[] = {
	{ "ad2s1210" },
	{}
};
MODULE_DEVICE_TABLE(spi, ad2s1210_id);

>>>>>>> cm-10.0
static struct spi_driver ad2s1210_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = ad2s1210_probe,
	.remove = __devexit_p(ad2s1210_remove),
<<<<<<< HEAD
};

static __init int ad2s1210_spi_init(void)
{
	return spi_register_driver(&ad2s1210_driver);
}
module_init(ad2s1210_spi_init);

static __exit void ad2s1210_spi_exit(void)
{
	spi_unregister_driver(&ad2s1210_driver);
}
module_exit(ad2s1210_spi_exit);
=======
	.id_table = ad2s1210_id,
};
module_spi_driver(ad2s1210_driver);
>>>>>>> cm-10.0

MODULE_AUTHOR("Graff Yang <graff.yang@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD2S1210 Resolver to Digital SPI driver");
MODULE_LICENSE("GPL v2");
