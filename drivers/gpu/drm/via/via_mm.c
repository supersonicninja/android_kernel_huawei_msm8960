/*
 * Copyright 2006 Tungsten Graphics Inc., Bismarck, ND., USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*
 * Authors: Thomas Hellström <thomas-at-tungstengraphics-dot-com>
 */

#include "drmP.h"
#include "via_drm.h"
#include "via_drv.h"
<<<<<<< HEAD
#include "drm_sman.h"
=======
>>>>>>> cm-10.0

#define VIA_MM_ALIGN_SHIFT 4
#define VIA_MM_ALIGN_MASK ((1 << VIA_MM_ALIGN_SHIFT) - 1)

<<<<<<< HEAD
=======
struct via_memblock {
	struct drm_mm_node mm_node;
	struct list_head owner_list;
};

>>>>>>> cm-10.0
int via_agp_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_agp_t *agp = data;
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
<<<<<<< HEAD
	int ret;

	mutex_lock(&dev->struct_mutex);
	ret = drm_sman_set_range(&dev_priv->sman, VIA_MEM_AGP, 0,
				 agp->size >> VIA_MM_ALIGN_SHIFT);

	if (ret) {
		DRM_ERROR("AGP memory manager initialisation error\n");
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}
=======

	mutex_lock(&dev->struct_mutex);
	drm_mm_init(&dev_priv->agp_mm, 0, agp->size >> VIA_MM_ALIGN_SHIFT);
>>>>>>> cm-10.0

	dev_priv->agp_initialized = 1;
	dev_priv->agp_offset = agp->offset;
	mutex_unlock(&dev->struct_mutex);

	DRM_DEBUG("offset = %u, size = %u\n", agp->offset, agp->size);
	return 0;
}

int via_fb_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_fb_t *fb = data;
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
<<<<<<< HEAD
	int ret;

	mutex_lock(&dev->struct_mutex);
	ret = drm_sman_set_range(&dev_priv->sman, VIA_MEM_VIDEO, 0,
				 fb->size >> VIA_MM_ALIGN_SHIFT);

	if (ret) {
		DRM_ERROR("VRAM memory manager initialisation error\n");
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}
=======

	mutex_lock(&dev->struct_mutex);
	drm_mm_init(&dev_priv->vram_mm, 0, fb->size >> VIA_MM_ALIGN_SHIFT);
>>>>>>> cm-10.0

	dev_priv->vram_initialized = 1;
	dev_priv->vram_offset = fb->offset;

	mutex_unlock(&dev->struct_mutex);
	DRM_DEBUG("offset = %u, size = %u\n", fb->offset, fb->size);

	return 0;

}

int via_final_context(struct drm_device *dev, int context)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;

	via_release_futex(dev_priv, context);

	/* Linux specific until context tracking code gets ported to BSD */
	/* Last context, perform cleanup */
	if (dev->ctx_count == 1 && dev->dev_private) {
		DRM_DEBUG("Last Context\n");
		drm_irq_uninstall(dev);
		via_cleanup_futex(dev_priv);
		via_do_cleanup_map(dev);
	}
	return 1;
}

void via_lastclose(struct drm_device *dev)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;

	if (!dev_priv)
		return;

	mutex_lock(&dev->struct_mutex);
<<<<<<< HEAD
	drm_sman_cleanup(&dev_priv->sman);
	dev_priv->vram_initialized = 0;
	dev_priv->agp_initialized = 0;
=======
	if (dev_priv->vram_initialized) {
		drm_mm_takedown(&dev_priv->vram_mm);
		dev_priv->vram_initialized = 0;
	}
	if (dev_priv->agp_initialized) {
		drm_mm_takedown(&dev_priv->agp_mm);
		dev_priv->agp_initialized = 0;
	}
>>>>>>> cm-10.0
	mutex_unlock(&dev->struct_mutex);
}

int via_mem_alloc(struct drm_device *dev, void *data,
<<<<<<< HEAD
		  struct drm_file *file_priv)
{
	drm_via_mem_t *mem = data;
	int retval = 0;
	struct drm_memblock_item *item;
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
=======
		  struct drm_file *file)
{
	drm_via_mem_t *mem = data;
	int retval = 0, user_key;
	struct via_memblock *item;
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
	struct via_file_private *file_priv = file->driver_priv;
>>>>>>> cm-10.0
	unsigned long tmpSize;

	if (mem->type > VIA_MEM_AGP) {
		DRM_ERROR("Unknown memory type allocation\n");
		return -EINVAL;
	}
	mutex_lock(&dev->struct_mutex);
	if (0 == ((mem->type == VIA_MEM_VIDEO) ? dev_priv->vram_initialized :
		      dev_priv->agp_initialized)) {
		DRM_ERROR
		    ("Attempt to allocate from uninitialized memory manager.\n");
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}

<<<<<<< HEAD
	tmpSize = (mem->size + VIA_MM_ALIGN_MASK) >> VIA_MM_ALIGN_SHIFT;
	item = drm_sman_alloc(&dev_priv->sman, mem->type, tmpSize, 0,
			      (unsigned long)file_priv);
	mutex_unlock(&dev->struct_mutex);
	if (item) {
		mem->offset = ((mem->type == VIA_MEM_VIDEO) ?
			      dev_priv->vram_offset : dev_priv->agp_offset) +
		    (item->mm->
		     offset(item->mm, item->mm_info) << VIA_MM_ALIGN_SHIFT);
		mem->index = item->user_hash.key;
	} else {
		mem->offset = 0;
		mem->size = 0;
		mem->index = 0;
		DRM_DEBUG("Video memory allocation failed\n");
		retval = -ENOMEM;
	}

=======
	item = kzalloc(sizeof(*item), GFP_KERNEL);
	if (!item) {
		retval = -ENOMEM;
		goto fail_alloc;
	}

	tmpSize = (mem->size + VIA_MM_ALIGN_MASK) >> VIA_MM_ALIGN_SHIFT;
	if (mem->type == VIA_MEM_AGP)
		retval = drm_mm_insert_node(&dev_priv->agp_mm,
					    &item->mm_node,
					    tmpSize, 0);
	else
		retval = drm_mm_insert_node(&dev_priv->vram_mm,
					    &item->mm_node,
					    tmpSize, 0);
	if (retval)
		goto fail_alloc;

again:
	if (idr_pre_get(&dev_priv->object_idr, GFP_KERNEL) == 0) {
		retval = -ENOMEM;
		goto fail_idr;
	}

	retval = idr_get_new_above(&dev_priv->object_idr, item, 1, &user_key);
	if (retval == -EAGAIN)
		goto again;
	if (retval)
		goto fail_idr;

	list_add(&item->owner_list, &file_priv->obj_list);
	mutex_unlock(&dev->struct_mutex);

	mem->offset = ((mem->type == VIA_MEM_VIDEO) ?
		      dev_priv->vram_offset : dev_priv->agp_offset) +
	    ((item->mm_node.start) << VIA_MM_ALIGN_SHIFT);
	mem->index = user_key;

	return 0;

fail_idr:
	drm_mm_remove_node(&item->mm_node);
fail_alloc:
	kfree(item);
	mutex_unlock(&dev->struct_mutex);

	mem->offset = 0;
	mem->size = 0;
	mem->index = 0;
	DRM_DEBUG("Video memory allocation failed\n");

>>>>>>> cm-10.0
	return retval;
}

int via_mem_free(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_private_t *dev_priv = dev->dev_private;
	drm_via_mem_t *mem = data;
<<<<<<< HEAD
	int ret;

	mutex_lock(&dev->struct_mutex);
	ret = drm_sman_free_key(&dev_priv->sman, mem->index);
	mutex_unlock(&dev->struct_mutex);
	DRM_DEBUG("free = 0x%lx\n", mem->index);

	return ret;
=======
	struct via_memblock *obj;

	mutex_lock(&dev->struct_mutex);
	obj = idr_find(&dev_priv->object_idr, mem->index);
	if (obj == NULL) {
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}

	idr_remove(&dev_priv->object_idr, mem->index);
	list_del(&obj->owner_list);
	drm_mm_remove_node(&obj->mm_node);
	kfree(obj);
	mutex_unlock(&dev->struct_mutex);

	DRM_DEBUG("free = 0x%lx\n", mem->index);

	return 0;
>>>>>>> cm-10.0
}


void via_reclaim_buffers_locked(struct drm_device *dev,
<<<<<<< HEAD
				struct drm_file *file_priv)
{
	drm_via_private_t *dev_priv = dev->dev_private;

	mutex_lock(&dev->struct_mutex);
	if (drm_sman_owner_clean(&dev_priv->sman, (unsigned long)file_priv)) {
=======
				struct drm_file *file)
{
	struct via_file_private *file_priv = file->driver_priv;
	struct via_memblock *entry, *next;

	mutex_lock(&dev->struct_mutex);
	if (list_empty(&file_priv->obj_list)) {
>>>>>>> cm-10.0
		mutex_unlock(&dev->struct_mutex);
		return;
	}

	if (dev->driver->dma_quiescent)
		dev->driver->dma_quiescent(dev);

<<<<<<< HEAD
	drm_sman_owner_cleanup(&dev_priv->sman, (unsigned long)file_priv);
=======
	list_for_each_entry_safe(entry, next, &file_priv->obj_list,
				 owner_list) {
		list_del(&entry->owner_list);
		drm_mm_remove_node(&entry->mm_node);
		kfree(entry);
	}
>>>>>>> cm-10.0
	mutex_unlock(&dev->struct_mutex);
	return;
}
