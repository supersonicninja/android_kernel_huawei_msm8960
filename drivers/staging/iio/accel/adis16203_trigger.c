#include <linux/interrupt.h>
<<<<<<< HEAD
#include <linux/irq.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/list.h>
#include <linux/spi/spi.h>

#include "../iio.h"
#include "../sysfs.h"
=======
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/export.h>

#include "../iio.h"
>>>>>>> cm-10.0
#include "../trigger.h"
#include "adis16203.h"

/**
 * adis16203_data_rdy_trigger_set_state() set datardy interrupt state
 **/
static int adis16203_data_rdy_trigger_set_state(struct iio_trigger *trig,
						bool state)
{
<<<<<<< HEAD
	struct adis16203_state *st = trig->private_data;
	struct iio_dev *indio_dev = st->indio_dev;

	dev_dbg(&indio_dev->dev, "%s (%d)\n", __func__, state);
	return adis16203_set_irq(st->indio_dev, state);
}

int adis16203_probe_trigger(struct iio_dev *indio_dev)
{
	int ret;
	struct adis16203_state *st = indio_dev->dev_data;
=======
	struct iio_dev *indio_dev = trig->private_data;

	dev_dbg(&indio_dev->dev, "%s (%d)\n", __func__, state);
	return adis16203_set_irq(indio_dev, state);
}

static const struct iio_trigger_ops adis16203_trigger_ops = {
	.owner = THIS_MODULE,
	.set_trigger_state = &adis16203_data_rdy_trigger_set_state,
};

int adis16203_probe_trigger(struct iio_dev *indio_dev)
{
	int ret;
	struct adis16203_state *st = iio_priv(indio_dev);
>>>>>>> cm-10.0

	st->trig = iio_allocate_trigger("adis16203-dev%d", indio_dev->id);
	if (st->trig == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}

	ret = request_irq(st->us->irq,
			  &iio_trigger_generic_data_rdy_poll,
			  IRQF_TRIGGER_RISING,
			  "adis16203",
			  st->trig);
	if (ret)
		goto error_free_trig;

	st->trig->dev.parent = &st->us->dev;
<<<<<<< HEAD
	st->trig->owner = THIS_MODULE;
	st->trig->private_data = st;
	st->trig->set_trigger_state = &adis16203_data_rdy_trigger_set_state;
=======
	st->trig->ops = &adis16203_trigger_ops;
	st->trig->private_data = indio_dev;
>>>>>>> cm-10.0
	ret = iio_trigger_register(st->trig);

	/* select default trigger */
	indio_dev->trig = st->trig;
	if (ret)
		goto error_free_irq;

	return 0;

error_free_irq:
	free_irq(st->us->irq, st->trig);
error_free_trig:
	iio_free_trigger(st->trig);
error_ret:
	return ret;
}

void adis16203_remove_trigger(struct iio_dev *indio_dev)
{
<<<<<<< HEAD
	struct adis16203_state *state = indio_dev->dev_data;

	iio_trigger_unregister(state->trig);
	free_irq(state->us->irq, state->trig);
	iio_free_trigger(state->trig);
=======
	struct adis16203_state *st = iio_priv(indio_dev);

	iio_trigger_unregister(st->trig);
	free_irq(st->us->irq, st->trig);
	iio_free_trigger(st->trig);
>>>>>>> cm-10.0
}
