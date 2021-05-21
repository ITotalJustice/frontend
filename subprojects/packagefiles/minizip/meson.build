project('minizip', 'c',
    version: '1.2',
    license: 'zlib',
    default_options : [
    'optimization=3',
    'strip=true',
    'c_std=c99',
  ]
)

include_dirs = include_directories(
    '.',
)

sources = [
    'unzip.c',
    'zip.c',
    'ioapi.c',
    'ioapi_mem.c',
]

dependencies = [
    dependency('zlib')
]

add_project_arguments('-DNOUNCRYPT', language: 'c')
add_project_arguments('-DNOCRYPT', language: 'c')
add_project_arguments('-D_POSIX_C_SOURCE=200808L', language: 'c')
add_project_arguments('-Wno-unused-parameter', language: 'c')

minizip = library('minizip',
    sources,
    dependencies: dependencies,
    include_directories: include_dirs,
)

minizip_dep = declare_dependency(
    include_directories: include_dirs,
    link_with: minizip
)
