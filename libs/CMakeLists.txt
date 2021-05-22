add_library(imgui
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.h
)

if(ANDROID)
    target_sources(imgui PRIVATE imgui/backends/imgui_impl_opengl3.cpp)
    target_link_libraries(imgui GLESv2)
    add_definitions(-DIMGUI_IMPL_OPENGL_ES2)

    add_subdirectory(SDL2)
else()
    target_sources(imgui PRIVATE imgui/backends/imgui_impl_opengl2.cpp)
endif()

include_directories(imgui)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

set(MZ_FETCH_LIBS ON)
set(MZ_COMPAT ON)
set(MZ_ZLIB ON)
set(MZ_BZIP2 OFF)
set(MZ_LZMA OFF)
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

add_subdirectory(TotalGB/src)
