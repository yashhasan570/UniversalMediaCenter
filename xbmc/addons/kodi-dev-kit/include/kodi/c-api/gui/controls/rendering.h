/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_CONTROLS_RENDERING_H
#define C_API_GUI_CONTROLS_RENDERING_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_rendering
  {
    void (*set_callbacks)(
        UNIVERSALMEDIA_HANDLE universalmediacenterBase,
        UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
        UNIVERSALMEDIA_GUI_CLIENT_HANDLE clienthandle,
        bool (*createCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int, int, int, int, ADDON_HARDWARE_CONTEXT),
        void (*renderCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
        void (*stopCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
        bool (*dirtyCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE));
    void (*destroy)(void* universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_rendering;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_CONTROLS_RENDERING_H */
