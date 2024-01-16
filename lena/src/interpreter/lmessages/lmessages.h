#ifndef __LENA_MESSAGES_H__
#define __LENA_MESSAGES_H__

/**************************************************************************//**
 * @file     lmessages.h
 * @brief    Project L - Lena programming language lmessages 
 * @version  V0.0.1
 * @date     7. Jan 2024
 ******************************************************************************/

/* for --version flag */

void lena_cout_version(void){
    lstdout_set_color(LENA_TEXT_COLOR);
    lstdout_str(LENA_LABEL_NAME, LENA_LABEL_NAME_L);
    lstdout_set_color(LENA_INFO_COLOR);
    lstdout_str(l("Info: No input files or flags.\n"), 31);

    lstdout_set_color(LENA_TEXT_COLOR);
    lstdout_str(LENA_LABEL_NAME, LENA_LABEL_NAME_L);
    lstdout_set_color(LENA_HELP_COLOR);
    lstdout_str(l("Help: You can run the file with construct:\n"), 44);

    lstdout_set_color(LENA_TEXT_COLOR);
    lstdout_str(l("|-> "), 5);

    lstdout_set_color(LENA_LABEL_COLOR);
    lstdout_str(l("lena "), 6);
    lstdout_set_color(LENA_WARNING_COLOR);
    lstdout_str(l("[main file path] "), 18);
    lstdout_set_color(LENA_TEXT_COLOR);
    lstdout_str(l("-[flags]"), 9);

    lstdout_str(l("\n"), 1);
}

#endif // __LENA_MESSAGES_H__