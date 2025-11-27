/*
 * Copyright (c) 2025, Frank Li<lgl88911@163.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
 
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

//#define CONFIG_LVGL_XML_HELLO_WORLD_SUPPORT 1
//#define CONFIG_LVGL_XML_NEW_COMPONENT_SUPPORT 1
//#define CONFIG_LVGL_XML_ASSETS_SUPPORT 1
//#define CONFIG_LVGL_XML_SCREENS_SUPPORT 1
//#define CONFIG_LVGL_XML_LAYOUT_SUPPORT 1
//#define CONFIG_LVGL_XML_DATA_BINDING_SUPPORT 1
#define CONFIG_LVGL_XML_TRANSLATIONS_SUPPORT 1
//#define CONFIG_LVGL_XML_ANIMATIONS_SUPPORT 1

#if defined(CONFIG_FAT_FILESYSTEM_ELM)
#include <ff.h>
#include <zephyr/storage/disk_access.h>
#include <zephyr/fs/fs.h>
static FATFS fat_fs;
static const char *disk_mount_pt = "/SD:";
/* mounting info */
static struct fs_mount_t mp = {
	.type = FS_FATFS,
	.fs_data = &fat_fs,
};
static void fs_init(void)
{
	/* Filesystem initialization code can be added here if needed */
	do {
		static const char *disk_pdrv = "SD";
		uint64_t memory_size_mb;
		uint32_t block_count;
		uint32_t block_size;

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_CTRL_INIT, NULL) != 0) {
			LOG_ERR("Storage init ERROR!");
			break;
		}

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
			LOG_ERR("Unable to get sector count");
			break;
		}
		LOG_INF("Block count %u", block_count);

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
			LOG_ERR("Unable to get sector size");
			break;
		}
		printk("Sector size %u\n", block_size);

		memory_size_mb = (uint64_t)block_count * block_size;
		printk("Memory Size(MB) %u\n", (uint32_t)(memory_size_mb >> 20));

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_CTRL_DEINIT, NULL) != 0) {
			LOG_ERR("Storage deinit ERROR!");
			break;
		}
	} while (0);

	mp.mnt_point = disk_mount_pt;

	int res = fs_mount(&mp);

	if (res == FR_OK) {
		printk("Disk mounted.\n");
		/* Try to unmount and remount the disk */
		res = fs_unmount(&mp);
		if (res != FR_OK) {
			printk("Error unmounting disk\n");
		}
		res = fs_mount(&mp);
		if (res != FR_OK) {
			printk("Error remounting disk\n");
		}

	}
}
#else
static void fs_init(void)
{
	/* Filesystem initialization code can be added here if needed */
}
#endif

 


#if CONFIG_LVGL_XML_HELLO_WORLD_SUPPORT
#include "ui_hello_world.h"
static void initialize_gui(void)
{
	ui_hello_world_init(NULL);
	lv_screen_load(screen_hello_world_create());
}
#elif CONFIG_LVGL_XML_NEW_COMPONENT_SUPPORT
#include "ui_new_component.h"
static void initialize_gui(void)
{
	ui_new_component_init(NULL);
	lv_screen_load(screen_components_create());
}
#elif CONFIG_LVGL_XML_ASSETS_SUPPORT
#include "ui_assets.h"
static void initialize_gui(void)
{
	ui_assets_init("/SD:/");
	lv_screen_load(screen_assets_create());
}

#elif CONFIG_LVGL_XML_SCREENS_SUPPORT
#include "ui_screens.h"
static void initialize_gui(void)
{
	ui_screens_init(NULL);
	lv_screen_load(screen_main);
}
#elif CONFIG_LVGL_XML_LAYOUT_SUPPORT
#include "ui_layouts.h"
static void initialize_gui(void)
{
	ui_layouts_init(NULL);
	lv_screen_load(screen_layouts_create());
}
#elif CONFIG_LVGL_XML_DATA_BINDING_SUPPORT
#include "ui_data_binding.h"
static void initialize_gui(void)
{
	ui_data_binding_init(NULL);
	lv_screen_load(screen_data_bindings_create());
}
#elif CONFIG_LVGL_XML_TRANSLATIONS_SUPPORT
#include "ui_translations.h"
static void initialize_gui(void)
{
	ui_translations_init(NULL);
	
	lv_screen_load(screen_translations_create());
}
#elif CONFIG_LVGL_XML_ANIMATIONS_SUPPORT
#include "ui_animations.h"
static void initialize_gui(void)
{
	ui_animations_init(NULL);
	lv_screen_load(screen_animations_create());
}
#else
static void initialize_gui(void)
{
	/* No GUI to initialize */
}
#endif
 
 int main(void)
 {
	 const struct device *display_dev;
 
	 display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	 if (!device_is_ready(display_dev)) {
		 LOG_ERR("Device not ready, aborting test");
		 return -ENODEV;
	 }
 
	 fs_init();
	 initialize_gui();
 
	 lv_timer_handler();
	 display_blanking_off(display_dev);

 
	 while (1) {
		 uint32_t sleep_ms = lv_timer_handler();
 
		 k_msleep(MIN(sleep_ms, INT32_MAX));

		 #ifdef CONFIG_LVGL_XML_TRANSLATIONS_SUPPORT
		 static uint32_t last_switch_time = 0;
		 static uint8_t cnt = 0;
		 
		 last_switch_time += sleep_ms;
		 if(last_switch_time >= 2000) {
			last_switch_time = 0;
			cnt++;
			if((cnt & 0x01) == 0x01) {
				lv_translation_set_language("en");
			} else {
				lv_translation_set_language("de");
			}
		 }
		 #endif
	 }
 
	 return 0;
 }
 