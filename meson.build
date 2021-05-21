project('frontend', ['c', 'cpp'],
    version: '0.0.1',
    meson_version : '>= 0.55.0',
    license : 'MIT',
    default_options: [
        'b_ndebug=if-release',
        'c_std=c99',
    ],
)

dependencies = [
    dependency('TotalGB'),
    dependency('imgui', version : '>=1.82'),
    dependency('zlib'),
    dependency('minizip', version : '1.2'),
    #dependency('nativefiledialog'),
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
    'src/gui/imgui_wrapper.cpp',
    'src/gui/menu/main.cpp',
])


sdl1_video_backend_source = [
    'src/video/sdl1/base/base.c',
    'src/video/sdl1/sdl1.c',
]

sdl1_opengl_video_backend_source = [
    'src/video/sdl1/base/base.c',
    'src/video/sdl1/sdl1_opengl.c',
]

sdl2_video_backend_source = [
    'src/video/sdl2/base/base.c',
    'src/video/sdl2/sdl1.c',
]

sdl2_opengl_video_backend_source = [
    'src/video/sdl2/base/base.c',
    'src/video/sdl2/sdl2_opengl.c',
]

sdl2_vulkan_video_backend_source = [
    'src/video/sdl2/base/base.c',
    'src/video/sdl2/sdl2_vulkan.c',
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

includes = include_directories([
    'src',
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
    cppflags += '-DIMGUI_GL2'

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
elif host_machine.system() == 'darwin'
elif host_machine.system() == 'dragonfly'
elif host_machine.system() == 'emscripten'
elif host_machine.system() == 'freebsd'
elif host_machine.system() == 'gnu'
elif host_machine.system() == 'haiku'
elif host_machine.system() == 'linux'
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
