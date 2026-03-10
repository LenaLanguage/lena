project('lena_abi', 'c', version : '0.1')

# Meson сначала ищет системную либу, если не находит — идет в subprojects/libffi
libffi_dep = dependency('libffi', fallback : ['libffi', 'ffi_dep'], default_options : ['tests=false', 'buildtype=release', 'default_library=static'])
incdir = include_directories('include')

shared_library('lena_abi', 
  'src/lena-abi.c', 
  dependencies : libffi_dep,
  include_directories : incdir
)
