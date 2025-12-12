## 基本使用

一个最简单的 LVGL XML 和 Zephyr 整合的示例

```
cd ~/lzp
west lvglxml ./ePTest/
west build -b native_sim ./LVGLXMLwZephyr/app
west build -t run
```
你可以看到

![native_sim](native_sim.png)

本项目也提供了基于 esp32s3 真实硬件的示例

```
west build -b esp32s3_touch_lcd_2/esp32s3/procpu LVGLXMLwZephyr/app/
west flash
```
你可以看到
![esp32s3_touch_lcd_2](esp32s3_touch_lcd_2.png)