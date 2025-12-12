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


static void initialize_gui(void)
{
	examples_init(NULL);
	lv_screen_load(elements_create());
}

 
 int main(void)
 {
	 const struct device *display_dev;
 
	 display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	 if (!device_is_ready(display_dev)) {
		 LOG_ERR("Device not ready, aborting test");
		 return -ENODEV;
	 }
 
	 initialize_gui();
 
	 lv_timer_handler();
	 display_blanking_off(display_dev);

 
	 while (1) {
		 uint32_t sleep_ms = lv_timer_handler();
 
		 k_msleep(MIN(sleep_ms, INT32_MAX));
	 }
 
	 return 0;
 }
 