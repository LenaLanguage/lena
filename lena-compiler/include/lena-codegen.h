#ifndef LENA_CODEGEN_H
#define LENA_CODEGEN_H

#include <stdlib.h>
#include "lena-ast.h"

/* Emit module to an LLVM IR file. Returns 0 on success, -1 on error. */
int codegen_emit_module(ast_node_t *root, const char *out_path);

#endif /* LENA_CODEGEN_H */
