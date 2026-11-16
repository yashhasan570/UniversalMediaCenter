/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_LIST_ITEM_H
#define C_API_GUI_LIST_ITEM_H

#include "definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_listItem
  {
    UNIVERSALMEDIA_GUI_LISTITEM_HANDLE(*create)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, const char* label, const char* label2, const char* path);
    void (*destroy)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);

    char* (*get_label)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    void (*set_label)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* label);
    char* (*get_label2)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    void (*set_label2)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* label);
    char* (*get_art)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* type);
    void (*set_art)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                    UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                    const char* type,
                    const char* image);
    char* (*get_path)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
    void (*set_path)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* path);
    char* (*get_property)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, const char* key);
    void (*set_property)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                         UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                         const char* key,
                         const char* value);
    void (*select)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle, bool select);
    bool (*is_selected)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_listItem;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_LIST_ITEM_H */
