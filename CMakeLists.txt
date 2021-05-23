cmake_minimum_required(VERSION 3.13.4)
project(frontend)

option(MGB_ZIP "enable zip support, uses minizip" ON)
option(MGB_7Z "enable 7zip support, uses minizip" ON)
option(MGB_MINIZIP "enable minizip, needed for zip,7z support" ON)
option(MGB_GUI "enable the gui, depends on the backend" ON)

if (ANDROID)
    set(MGB_SHARED ON CACHE BOOL "Build as shared lib")
else()
    set(MGB_SHARED OFF CACHE BOOL "Build as exe")
endif()

# list(video-backends
#     "sdl1"
#     "sdl1-gl"
#     "sdl2"
#     "sdl2-gl"
#     "ncurses"
# )

# list(audio-backends
#     "sdl1"
#     "sdl2"
# )

if (NOT MGB_MINIZIP)
    set(MGB_ZIP OFF)
    set(MGB_7Z OFF)
endif()

add_subdirectory(src)
add_subdirectory(libs)
