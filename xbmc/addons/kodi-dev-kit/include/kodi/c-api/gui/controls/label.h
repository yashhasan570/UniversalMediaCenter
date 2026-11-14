/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_CONTROLS_LABEL_H
#define C_API_GUI_CONTROLS_LABEL_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_label
  {
    void (*set_visible)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, bool visible);
    void (*set_label)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, const char* text);
    char* (*get_label)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle);
  } AddonToUniversal Media CenterFuncTable_kodi_gui_control_label;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_CONTROLS_LABEL_H */
