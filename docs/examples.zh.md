## 示例 ([English](examples.md))

这是LVGL Editor github 仓库的示例项目 https://github.com/lvgl/lvgl_editor/tree/master/examples, 涵盖了大多数控件的使用示例。其在480x480的屏幕上运行效果最好。为了让其能在esp32s3上运行，做了一些改动，将图片和字体都以数据的形式嵌入到了代码中。

使用方法如下：

1. 切换分支到 lvgl_examples
   
```bash
cd ~/lzp/LVGLXMLwZephyr
git checkout lvgl_examples
cd ~/lzp/ePTest
git checkout lvgl_examples
cd ~/lzp
west update
```

2. XML导出代码

- 启动 LVGL_Pro_Editor-1.0.1.AppImage
- 执行 Project->Open UI Project, 打开 ePTest
- 执行 Project->Build UI Project
- 执行命令
```bash
cd ~/lzp
west lvglxml ./ePTest/
```

3. 修改 `~/lzp/LVGLXMLwZephyr/app/gui/fonts`下所有文件中C数组都加上`const`修饰符

4. 编译烧写代码
```bash
west build -b esp32s3_touch_lcd_2/esp32s3/procpu LVGLXMLwZephyr/app/
west flash
```

你可以看到:

![](e.gif)