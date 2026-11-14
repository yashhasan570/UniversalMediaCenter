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

  typedef void* KODI_GUI_HANDLE;
  typedef void* KODI_GUI_CLIENT_HANDLE;
  typedef void* KODI_GUI_CONTROL_HANDLE;
  typedef void* KODI_GUI_LISTITEM_HANDLE;
  typedef void* KODI_GUI_WINDOW_HANDLE;

  typedef struct AddonToUniversal Media CenterFuncTable_kodi_gui
  {
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_general* general;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_button* control_button;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_edit* control_edit;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_fade_label* control_fade_label;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_label* control_label;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_image* control_image;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_progress* control_progress;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_radio_button* control_radio_button;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_rendering* control_rendering;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_settings_slider* control_settings_slider;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_slider* control_slider;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_spin* control_spin;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_control_text_box* control_text_box;
    KODI_HANDLE control_dummy1;
    KODI_HANDLE control_dummy2;
    KODI_HANDLE control_dummy3;
    KODI_HANDLE control_dummy4;
    KODI_HANDLE control_dummy5;
    KODI_HANDLE control_dummy6;
    KODI_HANDLE control_dummy7;
    KODI_HANDLE control_dummy8;
    KODI_HANDLE control_dummy9;
    KODI_HANDLE control_dummy10; /* This and above used to add new controls */
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogContextMenu* dialogContextMenu;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogExtendedProgress* dialogExtendedProgress;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogFileBrowser* dialogFileBrowser;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogKeyboard* dialogKeyboard;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogNumeric* dialogNumeric;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogOK* dialogOK;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogProgress* dialogProgress;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogSelect* dialogSelect;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogTextViewer* dialogTextViewer;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_dialogYesNo* dialogYesNo;
    KODI_HANDLE dialog_dummy1;
    KODI_HANDLE dialog_dummy2;
    KODI_HANDLE dialog_dummy3;
    KODI_HANDLE dialog_dummy4;
    KODI_HANDLE dialog_dummy5;
    KODI_HANDLE dialog_dummy6;
    KODI_HANDLE dialog_dummy7;
    KODI_HANDLE dialog_dummy8;
    KODI_HANDLE dialog_dummy9;
    KODI_HANDLE dialog_dummy10; /* This and above used to add new dialogs */
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_listItem* listItem;
    struct AddonToUniversal Media CenterFuncTable_kodi_gui_window* window;
  } AddonToUniversal Media CenterFuncTable_kodi_gui;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DEFINITIONS_H */
