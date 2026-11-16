/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_KEYBOARD_H
#define C_API_GUI_DIALOGS_KEYBOARD_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogKeyboard
  {
    bool (*show_and_get_input_with_head)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         const char* text_in,
                                         char** text_out,
                                         const char* heading,
                                         bool allow_empty_result,
                                         bool hiddenInput,
                                         unsigned int auto_close_ms);
    bool (*show_and_get_input)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                               const char* text_in,
                               char** text_out,
                               bool allow_empty_result,
                               unsigned int auto_close_ms);
    bool (*show_and_get_new_password_with_head)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                const char* password_in,
                                                char** password_out,
                                                const char* heading,
                                                bool allow_empty_result,
                                                unsigned int auto_close_ms);
    bool (*show_and_get_new_password)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                      const char* password_in,
                                      char** password_out,
                                      unsigned int auto_close_ms);
    bool (*show_and_verify_new_password_with_head)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   char** password_out,
                                                   const char* heading,
                                                   bool allow_empty_result,
                                                   unsigned int auto_close_ms);
    bool (*show_and_verify_new_password)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         char** password_out,
                                         unsigned int auto_close_ms);
    int (*show_and_verify_password)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    const char* password_in,
                                    char** password_out,
                                    const char* heading,
                                    int retries,
                                    unsigned int auto_close_ms);
    bool (*show_and_get_filter)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                const char* text_in,
                                char** text_out,
                                bool searching,
                                unsigned int auto_close_ms);
    bool (*send_text_to_active_keyboard)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         const char* text,
                                         bool close_keyboard);
    bool (*is_keyboard_activated)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogKeyboard;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_KEYBOARD_H */
