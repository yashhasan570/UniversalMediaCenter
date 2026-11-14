/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_EXTENDED_PROGRESS_H
#define C_API_GUI_DIALOGS_EXTENDED_PROGRESS_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable__dialogExtendedProgress
  {
    UNIVERSALMEDIA_GUI_HANDLE (*new_dialog)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, const char* title);
    void (*delete_dialog)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    char* (*get_title)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*set_title)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, const char* title);
    char* (*get_text)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*set_text)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, const char* text);
    bool (*is_finished)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*mark_finished)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    float (*get_percentage)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*set_percentage)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, float percentage);
    void (*set_progress)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                         UNIVERSALMEDIA_GUI_HANDLE handle,
                         int currentItem,
                         int itemCount);
  } AddonToUniversal Media CenterFuncTable__dialogExtendedProgress;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_EXTENDED_PROGRESS_H */
