/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DEFINITIONS_H
#define C_API_GUI_DEFINITIONS_H

#include "../addon_base.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* UNIVERSALMEDIA_GUI_HANDLE;
  typedef void* UNIVERSALMEDIA_GUI_CLIENT_HANDLE;
  typedef void* UNIVERSALMEDIA_GUI_CONTROL_HANDLE;
  typedef void* UNIVERSALMEDIA_GUI_LISTITEM_HANDLE;
  typedef void* UNIVERSALMEDIA_GUI_WINDOW_HANDLE;

  typedef struct AddonToUniversal Media CenterFuncTable_
  {
    struct AddonToUniversal Media CenterFuncTable__general* general;
    struct AddonToUniversal Media CenterFuncTable__control_button* control_button;
    struct AddonToUniversal Media CenterFuncTable__control_edit* control_edit;
    struct AddonToUniversal Media CenterFuncTable__control_fade_label* control_fade_label;
    struct AddonToUniversal Media CenterFuncTable__control_label* control_label;
    struct AddonToUniversal Media CenterFuncTable__control_image* control_image;
    struct AddonToUniversal Media CenterFuncTable__control_progress* control_progress;
    struct AddonToUniversal Media CenterFuncTable__control_radio_button* control_radio_button;
    struct AddonToUniversal Media CenterFuncTable__control_rendering* control_rendering;
    struct AddonToUniversal Media CenterFuncTable__control_settings_slider* control_settings_slider;
    struct AddonToUniversal Media CenterFuncTable__control_slider* control_slider;
    struct AddonToUniversal Media CenterFuncTable__control_spin* control_spin;
    struct AddonToUniversal Media CenterFuncTable__control_text_box* control_text_box;
    UNIVERSALMEDIA_HANDLE control_dummy1;
    UNIVERSALMEDIA_HANDLE control_dummy2;
    UNIVERSALMEDIA_HANDLE control_dummy3;
    UNIVERSALMEDIA_HANDLE control_dummy4;
    UNIVERSALMEDIA_HANDLE control_dummy5;
    UNIVERSALMEDIA_HANDLE control_dummy6;
    UNIVERSALMEDIA_HANDLE control_dummy7;
    UNIVERSALMEDIA_HANDLE control_dummy8;
    UNIVERSALMEDIA_HANDLE control_dummy9;
    UNIVERSALMEDIA_HANDLE control_dummy10; /* This and above used to add new controls */
    struct AddonToUniversal Media CenterFuncTable__dialogContextMenu* dialogContextMenu;
    struct AddonToUniversal Media CenterFuncTable__dialogExtendedProgress* dialogExtendedProgress;
    struct AddonToUniversal Media CenterFuncTable__dialogFileBrowser* dialogFileBrowser;
    struct AddonToUniversal Media CenterFuncTable__dialogKeyboard* dialogKeyboard;
    struct AddonToUniversal Media CenterFuncTable__dialogNumeric* dialogNumeric;
    struct AddonToUniversal Media CenterFuncTable__dialogOK* dialogOK;
    struct AddonToUniversal Media CenterFuncTable__dialogProgress* dialogProgress;
    struct AddonToUniversal Media CenterFuncTable__dialogSelect* dialogSelect;
    struct AddonToUniversal Media CenterFuncTable__dialogTextViewer* dialogTextViewer;
    struct AddonToUniversal Media CenterFuncTable__dialogYesNo* dialogYesNo;
    UNIVERSALMEDIA_HANDLE dialog_dummy1;
    UNIVERSALMEDIA_HANDLE dialog_dummy2;
    UNIVERSALMEDIA_HANDLE dialog_dummy3;
    UNIVERSALMEDIA_HANDLE dialog_dummy4;
    UNIVERSALMEDIA_HANDLE dialog_dummy5;
    UNIVERSALMEDIA_HANDLE dialog_dummy6;
    UNIVERSALMEDIA_HANDLE dialog_dummy7;
    UNIVERSALMEDIA_HANDLE dialog_dummy8;
    UNIVERSALMEDIA_HANDLE dialog_dummy9;
    UNIVERSALMEDIA_HANDLE dialog_dummy10; /* This and above used to add new dialogs */
    struct AddonToUniversal Media CenterFuncTable__listItem* listItem;
    struct AddonToUniversal Media CenterFuncTable__window* window;
  } AddonToUniversal Media CenterFuncTable_;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DEFINITIONS_H */
