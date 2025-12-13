# 演示如何使用 LVGLXMLwZephyr 导出 LVGL XML 并在 Zephyr 中使用 [English](README.md)
这是一个 Zephyr+[LVGL Pro](https://pro.lvgl.io/) 项目示例。该项目为 LVGL Pro 和 Zephyr 应用整合开发提供了快捷的路径。在 Zephyr App 中集成了 west 命令可以将 LVGL Pro XML 文件生成的 C 代码导出到该项目下，只用修改 3 行代码既可以在 Zephyr 中运行 LVGL Pro 产生的 lvgl 代码。


## 使用方法
所有的操作都基于 Linux 系统。

假设你已经安装好了 Zephyr 开发环境，包括安装了 west 命令。如果没有请参考：https://docs.zephyrproject.org/latest/develop/getting_started/index.html

假设你已经安装好了 LVGL Pro XML Editor。如果没有请参考：https://docs.lvgl.io/master/details/xml/editor/install.html

### 第一步，下载 Zephyr 项目
```
mkdir ~/lzp
cd ~/lzp
git clone https://github.com/frank-zpro/LVGLXMLwZephyr.git
west init -m ./LVGLXMLwZephyr
west update
```
### 第二步，下载 LVGL XML 项目和产生 C 代码
```
cd ~/lzp
git clone https://github.com/lgl88911/ePTest.git
```

1. 启动 LVGL_Pro_Editor-1.0.0-rc2.AppImage
2. 执行 Project->Open UI Project, 打开 ePTest
3. 执行 Project->Build UI Project

### 第三步，导入和执行
下面的“教程”和“示例”是LVGL官方仓库的代码 https://github.com/lvgl/lvgl_editor@4b4d80bc

[基本使用](docs/basic.zh.md)

[教程](docs/tutorials.zh.md)

[示例](docs/examples.zh.md)


## 如何修改自建的 LVGL XML 项目
当你的 LVGL XML 项目名不是 ePTest 时，需要修改 LVGLXMLwZephyr/app/src/main.c 文件

假设你的项目名叫 MyProject，项目中主 screen 叫 MyScreen，你需要修改 LVGLXMLwZephyr/app/src/main.c 如下：
- 将`#include "ePTest.h"`替换为`#include "MyProject.h"`
- 将`ePTest_init(NULL);`替换为`MyProject_init(NULL);`
- 将`lv_screen_load(main_screen);`替换为`lv_screen_load(MyScreen);`
