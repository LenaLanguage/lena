
project('my_project', 'c', version : '0.1')

# Meson сначала ищет системную либу, если не находит — идет в subprojects/libffi
libffi_dep = dependency('libffi', fallback : ['libffi', 'ffi_dep'])
incdir = include_directories('include')

shared_library('shrdlena', 
  'src/shrd-abi.c', 
  dependencies : libffi_dep,
  include_directories : incdir
)