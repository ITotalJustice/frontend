project('TotalGB', 'c',
  version : '0.0.1',
  license : 'MIT',
  default_options : [
    'warning_level=3',
    'optimization=3',
    'strip=true',
    'c_std=c99',
  ]
)

include_dirs = include_directories(
    'src',
)

sources = [
    'src/gb.c',
    'src/cpu.c',
    'src/bus.c',
    'src/joypad.c',
    'src/ppu/ppu.c',
    'src/ppu/dmg_renderer.c',
    'src/ppu/gbc_renderer.c',
    'src/ppu/sgb_renderer.c',
    'src/apu/apu.c',
    'src/apu/io.c',
    'src/apu/square1.c',
    'src/apu/square2.c',
    'src/apu/wave.c',
    'src/apu/noise.c',
    'src/mbc/mbc.c',
    'src/mbc/mbc_0.c',
    'src/mbc/mbc_1.c',
    'src/mbc/mbc_2.c',
    'src/mbc/mbc_3.c',
    'src/mbc/mbc_5.c',
    'src/timers.c',
    'src/serial.c',
    'src/sgb.c',
    'src/accessories/printer.c',
    'src/tables/palette_table.c',
]

if get_option('pixel-stride') == '8'
  c_flags += '-DGB_PIXEL_STRIDE=8'
elif get_option('pixel-stride') == '16'
  c_flags += '-DGB_PIXEL_STRIDE=16'
elif get_option('pixel-stride') == '32'
  c_flags += '-DGB_PIXEL_STRIDE=32'
endif

# todo: setup the endianness
if host_machine.endian() == 'little'
elif
endif

if get_option('debug') == true
    c_flags += '-DGB_DEBUG=1'
endif

if get_option('builtin-palette') == false
    c_flags += '-DGB_NO_BUILTIN_PALETTE=1'
endif

if get_option('sram-size') == 0
    c_flags += '-DGB_MAX_SRAM_SIZE=0'
elif get_option('sram-size') == 1
    c_flags += '-DGB_MAX_SRAM_SIZE=1'
elif get_option('sram-size') == 2
    c_flags += '-DGB_MAX_SRAM_SIZE=2'
elif get_option('sram-size') == 3
    c_flags += '-DGB_MAX_SRAM_SIZE=3'
elif get_option('sram-size') == 4
    c_flags += '-DGB_MAX_SRAM_SIZE=4'
elif get_option('sram-size') == 5
    c_flags += '-DGB_MAX_SRAM_SIZE=5'
endif


TotalGB = library(
    'TotalGB',
    sources,
    dependencies: dependencies,
    include_directories: include_dirs,
)

TotalGB_dep = declare_dependency(
    include_directories: include_dirs,
    link_with: TotalGB
)
