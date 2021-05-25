cmake_minimum_required(VERSION 3.13.4)

list(APPEND SOURCE
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

if (MGB_VO STREQUAL sdl1)
    find_package(SDL1 REQUIRED)
    target_include_directories(main PRIVATE ${SDL1_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${SDL1_LIBRARIES})

    target_compile_definitions(main PRIVATE MGB_VIDEO_BACKEND_SDL1=1)

elseif (MGB_VO STREQUAL sdl1_gl)
    find_package(SDL1 REQUIRED)
    target_include_directories(main PRIVATE ${SDL1_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${SDL1_LIBRARIES})

    find_package(OpenGL REQUIRED)
    target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES})

    target_compile_definitions(main PRIVATE MGB_VIDEO_BACKEND_SDL1_GL=1)

elseif (MGB_VO STREQUAL sdl2)
    find_package(SDL2 REQUIRED)
    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})

    target_compile_definitions(main PRIVATE MGB_VIDEO_BACKEND_SDL2=1)
    target_sources(main PRIVATE video/sdl2/base/base.c video/sdl2/sdl2.c)

elseif (MGB_VO STREQUAL sdl2_gl)
    find_package(SDL2 REQUIRED)
    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})

    find_package(OpenGL REQUIRED)
    target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(main PRIVATE ${OPENGL_LIBRARIES})

    target_compile_definitions(main PRIVATE MGB_VIDEO_BACKEND_SDL2_GL=1)
    target_sources(main PRIVATE video/sdl2/base/base.c video/sdl2/sdl2_opengl.c)

elseif (MGB_VO STREQUAL caca)
    find_package(CACA REQUIRED)
    target_include_directories(main PUBLIC ${CACA_INCLUDE_DIRS})
    target_link_libraries(main PUBLIC ${CACA_LIBRARIES})
    target_link_libraries(main PUBLIC -lcaca)

    target_compile_definitions(main PRIVATE MGB_VIDEO_BACKEND_CACA=1)
    target_sources(main PRIVATE video/caca/caca.c)

elseif (MGB_VO STREQUAL ncurses)
    find_package(Curses REQUIRED)
    target_include_directories(main PUBLIC ${CURSES_INCLUDE_DIRS})
    target_link_libraries(main PUBLIC ${CURSES_LIBRARIES})

    target_compile_definitions(main PRIVATE MGB_VIDEO_BACKEND_NCURSES=1)
    target_sources(main PRIVATE video/ncurses/ncurses.c)
else()
    message(FATAL_ERROR "oof")
endif()

if (MGB_ZIP)
    target_compile_definitions(main PUBLIC MGB_ZIP=1)
endif()

if (MGB_7Z)
    target_compile_definitions(main PUBLIC MGB_7Z=1)
endif()

if (MGB_GUI)
    if (ANDROID)
        target_compile_definitions(main PRIVATE IMGUI_GL3=1)
    endif()

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
