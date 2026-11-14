/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_CONTROLS_SPIN_H
#define C_API_GUI_CONTROLS_SPIN_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable__control_spin
  {
    void (*set_visible)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool visible);
    void (*set_enabled)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool enabled);
    void (*set_text)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, const char* text);
    void (*reset)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_type)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int type);
    void (*add_string_label)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                             const char* label,
                             const char* value);
    void (*set_string_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                             const char* value);
    char* (*get_string_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*add_int_label)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                          UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                          const char* label,
                          int value);
    void (*set_int_range)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int start, int end);
    void (*set_int_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int value);
    int (*get_int_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_float_range)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                            UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                            float start,
                            float end);
    void (*set_float_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, float value);
    float (*get_float_value)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    void (*set_float_interval)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                               UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                               float interval);
  } AddonToUniversal Media CenterFuncTable__control_spin;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_CONTROLS_SPIN_H */
