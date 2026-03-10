project('lena_compiler', 'c', 'cpp', version : '0.1')


# Meson сначала ищет системную либу, если не находит — идет в subprojects/libffi
llvm_dep = dependency('llvm', version : '>=15.0', modules : ['core', 'executionengine', 'instcombine', 'scalaropts', 'support'])
incdir = include_directories('include')

executable('lena-c',
  'src/lena-util.c',
  'src/lena-tokenizer.c',
  'src/lena-parser.c',
  'src/lena-codegen.c',
  'src/lena-compiler.c',
  dependencies : llvm_dep,
  include_directories : incdir
)
