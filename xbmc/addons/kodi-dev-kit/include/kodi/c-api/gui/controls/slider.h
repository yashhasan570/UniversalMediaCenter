/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
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

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_slider
  {
    void (*set_visible)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool visible);
    void (*set_enabled)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool enabled);
    void (*reset)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    char* (*get_description)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_int_range)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int start, int end);
    void (*set_int_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int value);
    int (*get_int_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_int_interval)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int interval);
    void (*set_percentage)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, float percent);
    float (*get_percentage)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_float_range)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                            UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                            float start,
                            float end);
    void (*set_float_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, float value);
    float (*get_float_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_float_interval)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                               UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                               float interval);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_slider;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_CONTROLS_SLIDER_H */
