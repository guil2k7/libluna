cmake_minimum_required(VERSION 3.22)
project("Dear ImGui" LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCE_FILES
    imconfig.h
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    imgui.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
)

add_library(imgui STATIC ${SOURCE_FILES})
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR})
