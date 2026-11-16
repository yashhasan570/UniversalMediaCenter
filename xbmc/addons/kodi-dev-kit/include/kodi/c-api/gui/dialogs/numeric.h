/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_NUMERIC_H
#define C_API_GUI_DIALOGS_NUMERIC_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogNumeric
  {
    bool (*show_and_verify_new_password)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, char** password);
    int (*show_and_verify_password)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    const char* password,
                                    const char* heading,
                                    int retries);
    bool (*show_and_verify_input)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  const char* verify_in,
                                  char** verify_out,
                                  const char* heading,
                                  bool verify_input);
    bool (*show_and_get_time)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, struct tm* time, const char* heading);
    bool (*show_and_get_date)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, struct tm* date, const char* heading);
    bool (*show_and_get_ip_address)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    const char* ip_address_in,
                                    char** ip_address_out,
                                    const char* heading);
    bool (*show_and_get_number)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                const char* input_in,
                                char** input_out,
                                const char* heading,
                                unsigned int auto_close_ms);
    bool (*show_and_get_seconds)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                 const char* time_in,
                                 char** time_out,
                                 const char* heading);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogNumeric;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_NUMERIC_H */
