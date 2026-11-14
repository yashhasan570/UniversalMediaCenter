/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_OK_H
#define C_API_GUI_DIALOGS_OK_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable__dialogOK
  {
    void (*show_and_get_input_single_text)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           const char* heading,
                                           const char* text);
    void (*show_and_get_input_line_text)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         const char* heading,
                                         const char* line0,
                                         const char* line1,
                                         const char* line2);
  } AddonToUniversal Media CenterFuncTable__dialogOK;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_OK_H */
