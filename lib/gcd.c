#include <linux/kernel.h>
#include <linux/gcd.h>
<<<<<<< HEAD
#include <linux/module.h>
=======
#include <linux/export.h>
>>>>>>> cm-10.0

/* Greatest common divisor */
unsigned long gcd(unsigned long a, unsigned long b)
{
	unsigned long r;

	if (a < b)
		swap(a, b);
	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}
	return b;
}
EXPORT_SYMBOL_GPL(gcd);
