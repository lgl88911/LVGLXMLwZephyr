# How to Use LVGLXMLwZephyr to Export LVGL XML and Run It in Zephyr [中文](README.zh.md)

This is a **Zephyr + [LVGL Pro](https://pro.lvgl.io/)** project example. The project provides a streamlined workflow for integrating LVGL Pro and Zephyr applications.
Within the Zephyr App, the integrated `west` command allows you to export the C code generated from LVGL Pro XML files directly into this project. With just **three lines of code modification**, you can run the LVGL code produced by LVGL Pro within Zephyr.


## Usage

All operations are performed under a **Linux system**.

Assume you have already installed the Zephyr development environment, including the `west` command.
If not, please refer to: [https://docs.zephyrproject.org/latest/develop/getting_started/index.html](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)

Assume you have also installed the **LVGL Pro XML Editor**.
If not, please refer to: [https://docs.lvgl.io/master/details/xml/editor/install.html](https://docs.lvgl.io/master/details/xml/editor/install.html)

### Step 1: Download the Zephyr Project

```bash
mkdir ~/lzp
cd ~/lzp
git clone https://github.com/frank-zpro/LVGLXMLwZephyr.git
west init -m ./LVGLXMLwZephyr
west update
```

### Step 2: Download the LVGL XML Project and Generate C Code

```bash
cd ~/lzp
git clone https://github.com/lgl88911/ePTest.git
```

1. Launch `LVGL_Pro_Editor-1.0.0-rc2.AppImage`
2. Go to **Project → Open UI Project**, and open `ePTest`
3. Go to **Project → Build UI Project**

### Step 3: Import and Run

[Basic Usage](docs/basic.md)

[tutorials](docs/tutorials.md)

[examples](docs/examples.md)


## How to Modify Your Own LVGL XML Project

If your LVGL XML project name is not `ePTest`, you will need to modify the file `LVGLXMLwZephyr/app/src/main.c`.

For example, if your project is named `MyProject`, and your main screen is named `MyScreen`, modify `LVGLXMLwZephyr/app/src/main.c` as follows:

* Replace `#include "ePTest.h"` with `#include "MyProject.h"`
* Replace `ePTest_init(NULL);` with `MyProject_init(NULL);`
* Replace `lv_screen_load(main_screen);` with `lv_screen_load(MyScreen);`
