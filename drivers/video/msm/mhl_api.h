
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
 *
 */
#ifndef __MHL_API_H__
#define __MHL_API_H__

<<<<<<< HEAD
#ifdef CONFIG_FB_MSM_HDMI_MHL
=======
#ifdef CONFIG_FB_MSM_HDMI_MHL_8334
>>>>>>> cm-10.0
bool mhl_is_connected(void);
#else
static bool mhl_is_connected(void)
{
	return false;
}
#endif

#endif /* __MHL_API_H__ */
