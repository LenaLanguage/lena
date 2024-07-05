/* Include general file Llibs framework */
#include <llibs.h>

/* Include main Lena compiler header file*/
#include <lena.h>

/* Include specific libraries */
#include <compiler/flags/flags.h>
#include <compiler/compiler.h>

/* For information messages */
#include <compiler/errors/errors.h>
#include <compiler/info/info.h>
#include <compiler/info/config.h>

lm compile(lu32 argc, lc* argv[]) {
    if (llibs_init() != L_OK) {
        return L_EXIT_FAILURE;
    }
    lu32 file_index = 1;
    if (argc > 1) {
        /* We should recognize all flags here ->*/
        if (argc >= 4) {
            /* at least 3 flags: "lena main.le -o app.e" */
            /* It must be flags for compilation here -> */
            lc* target = NULL;
            compiler_flag_t flag;
            lbool is_target = false;

            lc* source_code_files[LENA_COMPILER_INPUT_MAX_SOURCE_FILES];
            lu8 source_code_file_index = 0;

            lbool is_non_abstract = false;

            for (lu32 i = 1; i < argc; ++i) {
                flag = flags_recognize(argv[i]);
                if (!is_compilation_flag(flag)) {
                    /* In this case just recognize first one */
                    file_index = i;
                    goto read_first_flag;
                } else {
                    switch(flag) {
                    /* it's '-o' flag, the next flag must be a target file */
                    case COMPILER_FLAG_D_OUT:
                        is_target = true;
                        break;

                    /* Target filename flag */
                    case COMPILER_FLAG_FILENAME_E:
                    case COMPILER_FLAG_FILENAME_EXE:
                    /* Unrecognized flag, it must be a target file */
                    case COMPILER_FLAG_FILENAME:
                        if (is_target) {
                            target = argv[i];
                        } else {
                            /* It's an error! */
                            greeting();
                            lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
                            lcout(X("Output file: "));
                            lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
                            lcout(argv[i]);
                            lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
                            lcout(X(" must be provided after "));
                            lccol(LC_COLOR_GREEN, LC_COLOR_BLACK);
                            lcout(X("-o "));
                            lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
                            lcout(X("flag.\n\n"));

                            help_formats();
                        }
                        break;

                    /* .le filename, source code file */
                    case COMPILER_FLAG_FILENAME_LE:
                        source_code_files[source_code_file_index] = argv[i];
                        ++source_code_file_index;
                        break;

                    /* .le filename, source code file */
                    case COMPILER_FLAG_DD_NON_ABSTRACT:
                        is_non_abstract = true;
                        break;

                    /* other file format */
                    case COMPILER_FLAG_FILENAME_OTHER:
                        /* It must be an error. Invalid format file */
                        greeting();
                        lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
                        lcout(X("File: "));
                        lccol(LC_COLOR_CYAN, LC_COLOR_BLACK);
                        lcout(argv[i]);
                        lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
                        lcout(X(" cannot be an output file format or a source code file.\n\n"));

                        help_formats();
                        break;

                    default:
                        file_index = i;
                        goto read_first_flag;
                    }
                }
            }
            compile_files  (
                            source_code_file_index, 
                            source_code_files, 
                            is_non_abstract, 
                            target, 
                            0, NULL); // temporary solution

            
        } else {
            read_first_flag:
            /* Just read first flag */
            compiler_flag_t flag = flags_recognize(argv[file_index]);
            if (is_compilation_flag(flag)) {
                /* Error */
                greeting();
                lcout(X("Too few flags to compile.\n\n"));
                help_usage();
            } else {
                /* Execute the certain instruction */
                switch (flag) {
                /* Short version information */
                case COMPILER_FLAG_DD_VERSION:
                    version();
                    break;
                    
                /* Full version information */
                case COMPILER_FLAG_D_VERSION:
                    version_extented();
                    break;

                /* Help information */
                case COMPILER_FLAG_DD_HELP:
                    help();
                    break;

                /* Help information */
                case COMPILER_FLAG_DD_LICENSE:
                    license();
                    break;

                default:
                    // let's try to find out similar flag....
                    greeting();
                    lcout(X("Unrecognized flag, it will be useful for you to read:\n\n"));
                    help_flags();
                    break;
                }
            }
        }
    } else {
        greeting();
        lcout(X("No flags provided. Please specify flags to compile your program.\n"));
        // continue
    }
    /* Deinitialization */
    lccol(LC_COLOR_WHITE, LC_COLOR_BLACK);
    lcout(X("\n"));
    return L_EXIT_SUCCESS;
}