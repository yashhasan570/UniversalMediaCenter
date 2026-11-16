/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_WINDOW_H
#define C_API_GUI_WINDOW_H

#include "definitions.h"
#include "input/action_ids.h"

#include <stddef.h>

#define ADDON_MAX_CONTEXT_ENTRIES 20
#define ADDON_MAX_CONTEXT_ENTRY_NAME_LENGTH 80

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct gui_context_menu_pair
  {
    unsigned int id;
    char name[ADDON_MAX_CONTEXT_ENTRY_NAME_LENGTH];
  } gui_context_menu_pair;

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_window
  {
    /* Window creation functions */
    UNIVERSALMEDIA_GUI_WINDOW_HANDLE(*create)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase,
     const char* xml_filename,
     const char* default_skin,
     bool as_dialog,
     bool is_media);
    void (*destroy)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    void (*set_callbacks)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                          UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                          UNIVERSALMEDIA_GUI_CLIENT_HANDLE clienthandle,
                          bool (*CBInit)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
                          bool (*CBFocus)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int),
                          bool (*CBClick)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int),
                          bool (*CBOnAction)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, enum ADDON_ACTION),
                          void (*CBGetContextButtons)(
                              UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int, gui_context_menu_pair*, unsigned int*),
                          bool (*CBOnContextButton)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int, unsigned int));
    bool (*show)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    bool (*close)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    bool (*do_modal)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    /* Window control functions */
    bool (*set_focus_id)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    int (*get_focus_id)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    void (*set_control_label)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                              int control_id,
                              const char* label);
    void (*set_control_visible)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                int control_id,
                                bool visible);
    void (*set_control_selected)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                 UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                 int control_id,
                                 bool selected);

    /* Window property functions */
    void (*set_property)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                         UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                         const char* key,
                         const char* value);
    void (*set_property_int)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                             UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                             const char* key,
                             int value);
    void (*set_property_bool)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                              const char* key,
                              bool value);
    void (*set_property_double)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                const char* key,
                                double value);
    char* (*get_property)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, const char* key);
    int (*get_property_int)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, const char* key);
    bool (*get_property_bool)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, const char* key);
    double (*get_property_double)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                  const char* key);
    void (*clear_properties)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    void (*clear_property)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, const char* key);

    /* List item functions */
    void (*clear_item_list)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    void (*add_list_item)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                          UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                          UNIVERSALMEDIA_GUI_LISTITEM_HANDLE item,
                          int list_position);
    void (*remove_list_item_from_position)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                           int list_position);
    void (*remove_list_item)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                             UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                             UNIVERSALMEDIA_GUI_LISTITEM_HANDLE item);
    UNIVERSALMEDIA_GUI_LISTITEM_HANDLE(*get_list_item)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int list_position);
    void (*set_current_list_position)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                      UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                      int list_position);
    int (*get_current_list_position)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    int (*get_list_size)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    void (*set_container_property)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                   UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                   const char* key,
                                   const char* value);
    void (*set_container_content)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                  const char* value);
    int (*get_current_container_id)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    /* Various functions */
    void (*mark_dirty_region)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    /* GUI control access functions */
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_button)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_edit)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_fade_label)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_image)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_label)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_progress)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_radio_button)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_render_addon)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_settings_slider)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_slider)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_spin)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_text_box)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy1)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy2)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy3)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy4)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy5)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy6)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy7)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy8)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy9)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE(*get_control_dummy10)
    (UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    /* This above used to add new get_control_* functions */
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_window;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_WINDOW_H */
