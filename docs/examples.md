## Example

The example project from the LVGL Editor GitHub repository:
[https://github.com/lvgl/lvgl_editor/tree/master/examples](https://github.com/lvgl/lvgl_editor/tree/master/examples).
It contains usage examples for most widgets. The demo works best on a 480×480 screen. In order to run it on the ESP32-S3, several modifications were made, embedding images and fonts directly into the code as data.

Usage steps:

1. Switch branches to **lvgl_examples**

```bash
cd ~/lzp/LVGLXMLwZephyr
git checkout lvgl_examples
cd ~/lzp/ePTest
git checkout lvgl_examples
cd ~/lzp
west update
```

2. Export code from XML

* Launch **LVGL_Pro_Editor-1.0.1.AppImage**
* Run **Project → Open UI Project**, and open **ePTest**
* Run **Project → Build UI Project**
* Execute the following command:
```bash
cd ~/lzp
west lvglxml ./ePTest/
```

3. Add the `const` qualifier to all C arrays in every file under
   `~/lzp/LVGLXMLwZephyr/app/gui/fonts`

4. Compile and flash the code

```bash
west build -b esp32s3_touch_lcd_2/esp32s3/procpu LVGLXMLwZephyr/app/
west flash
```

## You will see:
