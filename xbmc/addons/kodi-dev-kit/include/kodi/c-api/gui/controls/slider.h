/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_CONTROLS_SLIDER_H
#define C_API_GUI_CONTROLS_SLIDER_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_slider
  {
    void (*set_visible)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, bool visible);
    void (*set_enabled)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, bool enabled);
    void (*reset)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle);
    char* (*get_description)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle);
    void (*set_int_range)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, int start, int end);
    void (*set_int_value)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, int value);
    int (*get_int_value)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle);
    void (*set_int_interval)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, int interval);
    void (*set_percentage)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, float percent);
    float (*get_percentage)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle);
    void (*set_float_range)(KODI_HANDLE kodiBase,
                            KODI_GUI_CONTROL_HANDLE handle,
                            float start,
                            float end);
    void (*set_float_value)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle, float value);
    float (*get_float_value)(KODI_HANDLE kodiBase, KODI_GUI_CONTROL_HANDLE handle);
    void (*set_float_interval)(KODI_HANDLE kodiBase,
                               KODI_GUI_CONTROL_HANDLE handle,
                               float interval);
  } AddonToUniversal Media CenterFuncTable_kodi_gui_control_slider;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_CONTROLS_SLIDER_H */
