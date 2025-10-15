# Copyright (c) 2025, Frank Li<lgl88911@163.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

add_subdirectory(gui)
target_link_libraries(lib-ui PRIVATE zephyr_interface)
target_include_directories(lib-ui PRIVATE ${ZEPHYR_LVGL_MODULE_DIR}/..)
target_include_directories(lib-ui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gui)

FILE(GLOB app_sources src/*.c)
target_include_directories(app PRIVATE ${ZEPHYR_LVGL_MODULE_DIR}/..)
target_include_directories(app PRIVATE gui)
target_sources(app PRIVATE ${app_sources})

target_link_libraries(app PRIVATE lib-ui)
