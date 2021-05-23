cmake_minimum_required(VERSION 3.13.4)

# todo clear this is up
if (MGB_GUI)
    add_library(imgui
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui.h
    )

    include_directories(imgui)
    target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

    if(ANDROID)
        target_sources(imgui PRIVATE imgui/backends/imgui_impl_opengl3.cpp)
        target_link_libraries(imgui GLESv2)
        target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_ES2=1)

    else()
        target_sources(imgui PRIVATE imgui/backends/imgui_impl_opengl2.cpp)
    endif()
endif()


if(ANDROID)
    add_subdirectory(SDL2)
endif()


if (MGB_MINIZIP)
    set(MZ_FETCH_LIBS ON)
    set(MZ_COMPAT ON) # this will be disabled soon once i use new api

    # the comp methods i care about
    set(MZ_ZLIB MGB_ZIP)
    set(MZ_LZMA MGB_7Z)
    set(MZ_BZIP2 OFF)
    set(MZ_ZSTD OFF)

    set(MZ_LIBCOMP OFF)
    set(MZ_PKCRYPT OFF)
    set(MZ_WZAES OFF)
    set(MZ_OPENSSL OFF)
    set(MZ_SIGNING OFF)
    set(MZ_ICONV OFF)
    set(MZ_LIBBSD OFF)
    set(MZ_FILE32_API OFF)
    set(MZ_BUILD_TESTS OFF)
    set(MZ_BUILD_UNIT_TESTS OFF)
    set(MZ_BUILD_FUZZ_TESTS OFF)
    set(MZ_CODE_COVERAGE OFF)
    add_subdirectory(minizip-ng)
else()
    message(STATUS "minizip disabled")
endif()

# fix tgb cmake file so that it builds as a lib by default
# not a test application
add_subdirectory(TotalGB/src)
