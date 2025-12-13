Examples ([中文](examples.zh.md))

This is an example project from the LVGL Editor GitHub repository: https://github.com/lvgl/lvgl_editor/tree/master/examples, covering usage examples for most widgets. It performs best on 480x480 screens. To make it run on ESP32-S3, some modifications were made by embedding images and fonts as data directly into the code.

Usage instructions:

1. Switch to the lvgl_examples branch
cd ~/lzp/LVGLXMLwZephyr
git checkout lvgl_examples
cd ~/lzp/ePTest
git checkout lvgl_examples
cd ~/lzp
west update


2. Export code from XML

- Launch LVGL_Pro_Editor-1.0.1.AppImage
- Execute Project->Open UI Project, open ePTest
- Execute Project->Build UI Project
- Run command:
cd ~/lzp
west lvglxml ./ePTest/


3. Add const modifier to all C arrays in files under ~/lzp/LVGLXMLwZephyr/app/gui/fonts

4. Compile and flash the code
west build -b esp32s3_touch_lcd_2/esp32s3/procpu LVGLXMLwZephyr/app/
west flash


You will see:

![](e.gif)
