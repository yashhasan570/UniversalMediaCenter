/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_PROGRESS_H
#define C_API_GUI_DIALOGS_PROGRESS_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogProgress
  {
    UNIVERSALMEDIA_GUI_HANDLE (*new_dialog)(UNIVERSALMEDIA_HANDLE universalmediacenterBase);
    void (*delete_dialog)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*open)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*set_heading)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, const char* heading);
    void (*set_line)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                     UNIVERSALMEDIA_GUI_HANDLE handle,
                     unsigned int lineNo,
                     const char* line);
    void (*set_can_cancel)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, bool canCancel);
    bool (*is_canceled)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*set_percentage)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, int percentage);
    int (*get_percentage)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
    void (*show_progress_bar)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, bool pnOff);
    void (*set_progress_max)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, int max);
    void (*set_progress_advance)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle, int nSteps);
    bool (*abort)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogProgress;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_PROGRESS_H */
