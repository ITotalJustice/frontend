cmake_minimum_required(VERSION 3.13.4)

set(SOURCE
    main.c
    mgb.c
    util.c
    romloader.c
    filedialog.c

    ifile/ifile.c
    ifile/mem/mem.c
    ifile/cfile/cfile.c
    ifile/zip/zip.c
    
    video/interface.c
    audio/interface.c
    
    gui/gui.c
)

if(MGB_SHARED)
    add_library(main SHARED ${SOURCE})
else()
    add_executable(main ${SOURCE})
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

target_link_libraries(main PRIVATE TotalGB)

if (MGB_ZIP)
    target_compile_definitions(main PUBLIC MGB_ZIP=1)
endif()

if (MGB_7Z)
    target_compile_definitions(main PUBLIC MGB_7Z=1)
endif()

if (MGB_GUI)
    target_sources(main PRIVATE
        gui/dearimgui/dearimgui.cpp
        gui/dearimgui/menu/main.cpp
    )

    target_compile_definitions(main PUBLIC MGB_GUI=1)
    target_link_libraries(main PRIVATE imgui)
else()
    target_sources(main PRIVATE gui/nogui/nogui.c)
endif()

if (MGB_MINIZIP)
    target_link_libraries(main PRIVATE minizip)
endif()


# todo: these should be build options
target_sources(main PRIVATE
    video/sdl2/base/base.c
    video/sdl2/sdl2_opengl.c
)

if(ANDROID)
    find_library(SDL2 SDL2)
    target_link_libraries(main PRIVATE SDL2)

    target_compile_definitions(main PRIVATE
        MGB_VIDEO_BACKEND_SDL2_OPENGL=1
        IMGUI_GL3=1
        MGB_SDL=1
    )

else()
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
    target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
    target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES})

    target_compile_definitions(main PRIVATE
        MGB_VIDEO_BACKEND_SDL2_OPENGL=1
        IMGUI_GL2=1
        MGB_SDL=1
    )
endif()

