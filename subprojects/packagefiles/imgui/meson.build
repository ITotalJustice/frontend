project('imgui', 'cpp',
    version: '1.82',
    license: 'MIT',
    default_options : [
    'optimization=3',
    'strip=true',
    'cpp_std=c++98',
  ]
)

include_dirs = include_directories(
    '.',
    'backends'
)

sources = [
    'imgui_draw.cpp',
    'imgui_tables.cpp',
    'imgui_widgets.cpp',
    'imgui.cpp'
]

dependencies = []

# todo: find a way to automate this
sources += 'backends/imgui_impl_opengl2.cpp'
dependencies += dependency('gl')

imgui = library('imgui',
    sources,
    dependencies: dependencies,
    include_directories: include_dirs,
)

imgui_dep = declare_dependency(
    include_directories: include_dirs,
    link_with: imgui
)
