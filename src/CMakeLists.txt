add_library(main SHARED
    main.c
    mgb.c
    util.c
    romloader.c
    filedialog.c

    ifile/ifile.c
    ifile/mem/mem.c

    video/interface.c
    audio/interface.c

    gui/gui.cpp
    gui/imgui_wrapper.cpp
    gui/menu/main.cpp
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# todo: these should be build options
target_sources(main PRIVATE
    ifile/cfile/cfile.c
    ifile/zip/zip.c
)

# todo: these should be build options
target_sources(main PRIVATE
    video/sdl2/base/base.c
    video/sdl2/sdl2_opengl.c
)

if(ANDROID)
    find_library(SDL2 SDL2)
    target_link_libraries(main PRIVATE SDL2)

    add_definitions(
        -DMGB_VIDEO_BACKEND_SDL2_OPENGL
        -DIMGUI_GL3
        -DMGB_SDL
    )

else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})

    add_definitions(
        -DMGB_VIDEO_BACKEND_SDL2_OPENGL
        -DIMGUI_GL2
        -DMGB_SDL
    )
endif()

target_link_libraries(main PRIVATE minizip)
target_link_libraries(main PRIVATE imgui)
target_link_libraries(main PRIVATE TotalGB)
