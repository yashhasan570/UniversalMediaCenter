/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_CONTROLS_IMAGE_H
#define C_API_GUI_CONTROLS_IMAGE_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_image
  {
    void (*set_visible)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, bool visible);
    void (*set_filename)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                         UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                         const char* filename,
                         bool use_cache);
    void (*set_color_diffuse)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                              uint32_t color_diffuse);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_image;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_CONTROLS_IMAGE_H */
