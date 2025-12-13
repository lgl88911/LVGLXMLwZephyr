## 示例

这是LVGL Editor github 仓库的示例项目 https://github.com/lvgl/lvgl_editor/tree/master/examples, LVGL官方的教程示例会需要搭配文件系统使用，因此只提供在esp32s3上的真机演示。

使用方法如下：

1. 切换分支到 lvgl_examples
   
```bash
cd ~/lzp/LVGLXMLwZephyr
git checkout tutorials
cd ~/lzp/ePTest
git checkout tutorials
cd ~/lzp
west update
```

2. XML导出代码

- 启动 LVGL_Pro_Editor-1.0.1.AppImage
- 执行 Project->Open UI Project, 打开 ePTest/<demo>
- 执行 Project->Build UI Project
- 执行命令
```bash
cd ~/lzp
west lvglxml ./ePTest/<demo>
```
这里<demo>是指ePTest目录下的一个示例项目，例如：ePTest/1_hello_world


3. 修改 `~/lzp/LVGLXMLwZephyr/app/src/main.c`打开对应的宏`CONFIG_LVGL_XML_<demo>_SUPPORT`关闭其它宏，例如`#define CONFIG_LVGL_XML_HELLO_WORLD_SUPPORT 1`

宏和demo的对应关系
| demo文件夹名 | 宏 |
|-----|-----|
| 1_hello_world | CONFIG_LVGL_XML_HELLO_WORLD_SUPPORT |
| 2_new_component | CONFIG_LVGL_XML_NEW_COMPONENT_SUPPORT |
| 3_assets | CONFIG_LVGL_XML_ASSETS_SUPPORT |
| 4_screens | CONFIG_LVGL_XML_GAUGES_SUPPORT |
| 5_layouts | CONFIG_LVGL_XML_LAYOUTS_SUPPORT |
| 6_data_binding | CONFIG_LVGL_XML_DATA_BINDING_SUPPORT |
| 7_translations | CONFIG_LVGL_XML_TRANSLATIONS_SUPPORT |
| 8_animations | CONFIG_LVGL_XML_ANIMATIONS_SUPPORT |

4. 编译烧写代码
```bash
west build -b esp32s3_touch_lcd_2/esp32s3/procpu LVGLXMLwZephyr/app/
west flash
```

你可以看到:

1_hello_world 示例

![](1h.mp4)

2_new_component 示例

<video controls>
  <source src="2c.mp4" type="video/mp4">
</video>

3_assets 示例

![](3a.jpg)

4_screens 示例
<video controls>
  <source src="4s.mp4" type="video/mp4">
</video>

5_layouts 示例
<video controls>
  <source src="5l.mp4" type="video/mp4">
</video>

6_data_binding 示例
<video controls>
  <source src="6d.webm" type="video/webm">
</video>

7_translations 示例

<video controls>
  <source src="7t.mp4" type="video/mp4">
</video>

8_animations 示例
<video controls>
  <source src="8a.mp4" type="video/mp4">
</video>
