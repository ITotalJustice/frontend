cmake_minimum_required(VERSION 3.13.4)
project(frontend)

# set the modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

option(MGB_ZIP "enable zip support, uses minizip" ON)
option(MGB_7Z "enable 7zip support, uses minizip" ON)
option(MGB_MINIZIP "enable minizip, needed for zip,7z support" ON)
option(MGB_GUI "enable the gui, depends on the backend" ON)

set(MGB_VO "sdl2" CACHE STRING "Video Backends")
set(MGB_AO "sdl2" CACHE STRING "Audio Backends")

list(APPEND _video_backends
    sdl1
    sdl1_gl
    sdl2
    sdl2_gl
    caca
    ncurses
)

list(APPEND _audio_backends
    none
    sdl1
    sdl2
)

# make sure that the user-set VO and AO is a valid option
if (NOT MGB_VO IN_LIST _video_backends)
    message(FATAL_ERROR "MGB_VO not in list!")
endif()

if (NOT MGB_AO IN_LIST _audio_backends)
    message(FATAL_ERROR "MGB_AO not in list!")
endif()

# only support sdl2_gl backend for android
if (ANDROID)
    set(MGB_VO sdl2_gl)
    set(MGB_AO sdl2)
endif()

# when building for android, we need to build as a shared lib.
if (ANDROID)
    set(MGB_SHARED ON CACHE BOOL "Build as shared lib")
else()
    set(MGB_SHARED OFF CACHE BOOL "Build as exe")
endif()

# if minizip support is disabled, disable each zip option
if (NOT MGB_MINIZIP)
    set(MGB_ZIP OFF)
    set(MGB_7Z OFF)
endif()

add_subdirectory(src)
add_subdirectory(libs)
