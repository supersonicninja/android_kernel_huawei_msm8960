/*
 * SELinux services exported to the rest of the kernel.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2005 Red Hat, Inc., James Morris <jmorris@redhat.com>
 * Copyright (C) 2006 Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 * Copyright (C) 2006 IBM Corporation, Timothy R. Chavez <tinytim@us.ibm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2,
 * as published by the Free Software Foundation.
 */
#include <linux/module.h>
<<<<<<< HEAD
=======
#include <linux/selinux.h>
>>>>>>> cm-10.0

#include "security.h"

bool selinux_is_enabled(void)
{
	return selinux_enabled;
}
EXPORT_SYMBOL_GPL(selinux_is_enabled);
