project('frontend', ['c', 'cpp'],
    version: '0.0.1',
    license : 'MIT',
    default_options: [
        # core options
        'buildtype=debug',
        'warning_level=3',
        'optimization=0',
        'strip=true',
        'werror=true',

        # base options
        'b_ndebug=if-release',

        'c_std=c99',
    ],
)

dependencies = [
    dependency('TotalGB')
]

dependencies_str = []

source = files([
    # frontend
    'src/main.c',
    'src/mgb.c',
    'src/util.c',
    'src/romloader.c',
    'src/filedialog.c',

    'src/ifile/ifile.c',
    'src/ifile/cfile/cfile.c',
    'src/ifile/mem/mem.c',
    'src/ifile/zip/zip.c',
    'src/ifile/gzip/gzip.c',

    'src/video/interface.c',
    'src/audio/interface.c',

    # gui
    'src/gui/gui.cpp',
    'src/gui/menu/main.cpp',

    # MINIZIP
    'libs/minizip/unzip.c',
    'libs/minizip/zip.c',
    'libs/minizip/ioapi.c',
    'libs/minizip/ioapi_mem.c',

    # ZLIB
    'libs/zlib/adler32.c',
    'libs/zlib/compress.c',
    'libs/zlib/crc32.c',
    'libs/zlib/deflate.c',
    'libs/zlib/gzclose.c',
    'libs/zlib/gzlib.c',
    'libs/zlib/gzread.c',
    'libs/zlib/gzwrite.c',
    'libs/zlib/infback.c',
    'libs/zlib/inffast.c',
    'libs/zlib/inflate.c',
    'libs/zlib/inftrees.c',
    'libs/zlib/trees.c',
    'libs/zlib/uncompr.c',
    'libs/zlib/zutil.c',

    # imgui
    'libs/imgui/imgui.cpp',
    #'libs/imgui/imgui_demo.cpp',
    'libs/imgui/imgui_draw.cpp',
    'libs/imgui/imgui_tables.cpp',
    'libs/imgui/imgui_widgets.cpp',
    'libs/imgui/backends/imgui_impl_opengl2.cpp',
    'libs/imgui/backends/imgui_impl_mgb.cpp',
])


sdl1_video_backend_source = [
    'src/video/sdl1/base/base.c',
    'src/video/sdl1/sdl1.c',
]

sdl1_opengl_video_backend_source = [
    'src/video/sdl1/base/base.c',
    'src/video/sdl1/sdl1_opengl.c',
]

sdl2_opengl_video_backend_source = [
    'src/video/sdl2/base/base.c',
    'src/video/sdl2/sdl2_opengl.c',
]

sdl2_vulkan_video_backend_source = [
    'src/video/sdl2/base/base.c',
    'src/video/sdl2/sdl2_vulkan.c',
]

Allegro5_video_backend_source = [
    'src/video/allegro5/base/base.c',
    'src/video/allegro5/allegro5.c',
    'src/video/allegro5/allegro5_opengl.c',
]

sdl1_video_backend_dependencies = [
    'sdl',
]

sdl1_opengl_video_backend_dependencies = [
    'sdl',
    'gl',
]

sdl2_video_backend_dependencies = [
    'sdl2',
]

sdl2_opengl_video_backend_dependencies = [
    'sdl2',
    'gl',
]

sdl2_vulkan_video_backend_dependencies = [
    'sdl2',
    'vulkan',
]

allegro4_video_backend_dependencies = [
    'allegro-4',
    'gl',
]

allegro5_video_backend_dependencies = [
    'allegro-5',
    'gl',
]

includes = include_directories([
    'src',
    'libs',
])

cflags = [
    # warns
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wfatal-errors',
    '-Wpedantic',
    '-Wshadow',
    '-Wdouble-promotion',
    '-Wformat=2',
    '-Wformat-overflow=2',
    '-Wformat-truncation=1',
    # '-Wundef',
    '-Wmissing-include-dirs',
    '-Wstrict-aliasing=2',
    '-Walloca',
    '-Wduplicated-branches',
    '-Wduplicated-cond',
    '-Wwrite-strings',
    '-Wdate-time',
    '-Wsizeof-pointer-memaccess',
    '-Wlogical-op',
    '-Wpacked',
    '-Wredundant-decls',
    '-Wnested-externs',
    '-Winline',

    '-ftrapv',
    '-freg-struct-return',
    '-fno-common',

    '-Wno-unused-function',

    # these also need to be added to the linker!
    #'-fsanitize=address',
    #'-fsanitize=leak',
    #'-fsanitize=undefined',
    #'-fsanitize=pointer-compare',
    #'-fsanitize=pointer-subtract',
    #'-fstack-protector-all',

    # minizip
    '-DNOUNCRYPT',
    '-DNOCRYPT',
]

cppflags = [
    # warns
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wfatal-errors',
    '-Wpedantic',
    '-Wshadow',
    # will add back later, lots of warns for imgui_widgets.cpp
    #'-Wdouble-promotion',
    '-Wformat=2',
    '-Wformat-overflow=1',
    '-Wformat-truncation=1',
    # '-Wundef',
    '-Wmissing-include-dirs',
    '-Wstrict-aliasing=2',
    '-Walloca',
    '-Wduplicated-branches',
    '-Wduplicated-cond',
    '-Wwrite-strings',
    '-Wdate-time',
    '-Wsizeof-pointer-memaccess',
    '-Wlogical-op',
    '-Wpacked',
    '-Wredundant-decls',
    '-Winline',

    '-ftrapv',
    '-freg-struct-return',
    '-fno-common',

    '-Wno-unused-function',

    # these also need to be added to the linker!
    #'-fsanitize=address',
    #'-fsanitize=leak',
    #'-fsanitize=undefined',
    #'-fsanitize=pointer-compare',
    #'-fsanitize=pointer-subtract',
    #'-fstack-protector-all',
]

linkflags = [
    '-lm',
    #'-fsanitize=address',
    #'-fsanitize=leak',
    #'-fsanitize=undefined',
    #'-fsanitize=pointer-compare',
    #'-fsanitize=pointer-subtract',
    #'-fstack-protector-all',
]

if get_option('video') == 'sdl1'
    source += sdl1_video_backend_source
    dependencies_str +=  sdl1_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_SDL1'

elif get_option('video') == 'sdl1_opengl'
    source += sdl1_opengl_video_backend_source
    dependencies_str +=  sdl1_opengl_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_SDL1_OPENGL'

elif get_option('video') == 'sdl2'
    source += sdl2_video_backend_source
    dependencies_str +=  sdl2_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_SDL2'

elif get_option('video') == 'sdl2_opengl'
    source += sdl2_opengl_video_backend_source
    dependencies_str +=  sdl2_opengl_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_SDL2_OPENGL'

elif get_option('video') == 'allegro4'
    source += allegro4_video_backend_source
    dependencies_str +=  allegro4_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_ALLEGRO4'

elif get_option('video') == 'allegro5'
    source += allegro5_video_backend_source
    dependencies_str +=  allegro5_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_ALLEGRO5'

elif get_option('video') == 'glfw'
    source += glfw_video_backend_source
    dependencies_str +=  glfw_video_backend_dependencies
    cflags += '-DMGB_VIDEO_BACKEND_GLFW'
endif


# detect the compiler (will be used for compiler flags)
if meson.get_compiler('c').get_id() == 'arm'
elif meson.get_compiler('c').get_id() == 'armclang'
elif meson.get_compiler('c').get_id() == 'c2000'
elif meson.get_compiler('c').get_id() == 'ccomp'
elif meson.get_compiler('c').get_id() == 'ccrx'
elif meson.get_compiler('c').get_id() == 'clang'
elif meson.get_compiler('c').get_id() == 'clang-cl'
elif meson.get_compiler('c').get_id() == 'emscripten'
elif meson.get_compiler('c').get_id() == 'gcc'
elif meson.get_compiler('c').get_id() == 'intel'
elif meson.get_compiler('c').get_id() == 'intel-cl'
elif meson.get_compiler('c').get_id() == 'lcc'
elif meson.get_compiler('c').get_id() == 'llvm'
elif meson.get_compiler('c').get_id() == 'msvc'
elif meson.get_compiler('c').get_id() == 'pgi'
elif meson.get_compiler('c').get_id() == 'xc16'
endif

# detect the OS
if host_machine.system() == 'android'
elif host_machine.system() == 'windows' or host_machine.system() == 'cygwin'
    # nativefiledialog
    cflags += '-DHAS_NFD=1'
    source += 'libs/nativefiledialog/nfd_win.c'
elif host_machine.system() == 'darwin'
elif host_machine.system() == 'dragonfly'
elif host_machine.system() == 'emscripten'
elif host_machine.system() == 'freebsd'
elif host_machine.system() == 'gnu'
elif host_machine.system() == 'haiku'
elif host_machine.system() == 'linux'
    # nativefiledialog
    cflags += '-DHAS_NFD=1'

    # check if we have gtk, if not, use zenity
    if dependency('gtk+-3.0', required : false).found()
        source += 'libs/nativefiledialog/nfd_gtk.c'
        dependencies_str += 'gtk+-3.0'
    elif dependency('gtk+-2.0', required : false).found()
        source += 'libs/nativefiledialog/nfd_gtk.c'
        dependencies_str += 'gtk+-2.0'
    else
        source += 'libs/nativefiledialog/nfd_zenity.c'
    endif
elif host_machine.system() == 'netbsd'
elif host_machine.system() == 'openbsd'
elif host_machine.system() == 'sunos'
endif


# add all dependencies
foreach d : dependencies_str
    dependencies += dependency(d)
endforeach


exe = executable(
    'frontend',
    [ source ],
    dependencies : [ dependencies ],
    install: true,
    include_directories: [ includes ],
    c_args: [ cflags ],
    cpp_args: [ cppflags ],
    link_args: [ linkflags ],
)


# scripts
run_target('cppcheck',
  command : 'scripts/cppcheck.sh')
