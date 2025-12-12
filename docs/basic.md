```bash
cd ~/lzp
west lvglxml ./ePTest/
west build -b native_sim ./LVGLXMLwZephyr/app
west build -t run
```

You will see:

![native\_sim](native_sim.png)

This project also provides an example based on real **ESP32-S3** hardware:

```bash
west build -b esp32s3_touch_lcd_2/esp32s3/procpu LVGLXMLwZephyr/app/
west flash
```

You will see:
![esp32s3\_touch\_lcd\_2](esp32s3_touch_lcd_2.png)