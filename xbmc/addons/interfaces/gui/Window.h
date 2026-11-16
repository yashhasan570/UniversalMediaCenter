/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/window.h"
#include "threads/Event.h"
#include "windows/GUIMediaWindow.h"

extern "C"
{

  struct AddonGlobalInterface;
  struct gui_context_menu_pair;

  namespace ADDON
  {
  class CAddonDll;

  /*!
   * @brief Global gui Add-on to Universal Media Center callback functions
   *
   * To hold functions not related to a instance type and usable for
   * every add-on type.
   *
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/Window.h"
   */
  struct Interface_GUIWindow
  {
    static void Init(AddonGlobalInterface* addonInterface);
    static void DeInit(AddonGlobalInterface* addonInterface);

    /*!
     * @brief callback functions from add-on to universalmediacenter
     *
     * @note To add a new function use the "_" style to directly identify an
     * add-on callback function. Everything with CamelCase is only to be used
     * in Universal Media Center.
     *
     * The parameter `universalmediacenterBase` is used to become the pointer for a `CAddonDll`
     * class.
     */
    //@{
    /* Window creation functions */
    static UNIVERSALMEDIA_GUI_WINDOW_HANDLE create(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         const char* xml_filename,
                                         const char* default_skin,
                                         bool as_dialog,
                                         bool is_media);
    static void destroy(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static void set_callbacks(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                              UNIVERSALMEDIA_GUI_CLIENT_HANDLE clienthandle,
                              bool (*CBInit)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
                              bool (*CBFocus)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int),
                              bool (*CBClick)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int),
                              bool (*CBOnAction)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, ADDON_ACTION),
                              void (*CBGetContextButtons)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE,
                                                          int,
                                                          gui_context_menu_pair*,
                                                          unsigned int*),
                              bool (*CBOnContextButton)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int, unsigned int));
    static bool show(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static bool close(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static bool do_modal(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    /* Window control functions */
    static bool set_focus_id(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, int control_id);
    static int get_focus_id(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static void set_control_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                  int control_id,
                                  const char* label);
    static void set_control_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                    int control_id,
                                    bool visible);
    static void set_control_selected(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                     UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                     int control_id,
                                     bool selected);

    /* Window property functions */
    static void set_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                             UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                             const char* key,
                             const char* value);
    static void set_property_int(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                 UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                 const char* key,
                                 int value);
    static void set_property_bool(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                  const char* key,
                                  bool value);
    static void set_property_double(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                    const char* key,
                                    double value);
    static char* get_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle, const char* key);
    static int get_property_int(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                const char* key);
    static bool get_property_bool(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                  const char* key);
    static double get_property_double(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                      UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                      const char* key);
    static void clear_properties(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static void clear_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                               UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                               const char* key);

    /* List item functions */
    static void clear_item_list(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static void add_list_item(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                              UNIVERSALMEDIA_GUI_LISTITEM_HANDLE item,
                              int list_position);
    static void remove_list_item_from_position(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                               UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                               int list_position);
    static void remove_list_item(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                 UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                 UNIVERSALMEDIA_GUI_LISTITEM_HANDLE item);
    static UNIVERSALMEDIA_GUI_LISTITEM_HANDLE get_list_item(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                  int list_position);
    static void set_current_list_position(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                          UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                          int list_position);
    static int get_current_list_position(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static int get_list_size(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);
    static void set_container_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                       UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                       const char* key,
                                       const char* value);
    static void set_container_content(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                      UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                      const char* value);
    static int get_current_container_id(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    /* Various functions */
    static void mark_dirty_region(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle);

    /* GUI control access functions */
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_button(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                      UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                      int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_edit(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                    UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                    int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_fade_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                          UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                          int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_image(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                     UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                     int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                     UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                     int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_radio_button(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                            UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                            int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_progress(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                        UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                        int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_render_addon(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                            UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                            int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_settings_slider(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                               UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                               int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_slider(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                      UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                      int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_spin(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                    UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                    int control_id);
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE get_control_text_box(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                        UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                                        int control_id);
    //@}

  private:
    static UNIVERSALMEDIA_GUI_CONTROL_HANDLE GetControl(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                              UNIVERSALMEDIA_GUI_WINDOW_HANDLE handle,
                                              int control_id,
                                              const char* function,
                                              CGUIControl::GUICONTROLTYPES type,
                                              const std::string& typeName);
    static int GetNextAvailableWindowId();
  };

  class CGUIAddonWindow : public CGUIMediaWindow
  {
    friend struct Interface_GUIWindow;

  public:
    CGUIAddonWindow(int id, const std::string& strXML, ADDON::CAddonDll* addon, bool isMedia);
    ~CGUIAddonWindow() override = default;

    bool OnMessage(CGUIMessage& message) override;
    bool OnAction(const CAction& action) override;
    void AllocResources(bool forceLoad = false) override;
    void Render() override;
    bool IsMediaWindow() const override { return m_isMedia; }

    /* Addon to Universal Media Center call functions */
    void PulseActionEvent();
    void AddItem(CFileItemPtr* fileItem, int itemPosition);
    void RemoveItem(int itemPosition);
    void RemoveItem(CFileItemPtr* fileItem);
    void ClearList();
    CFileItemPtr* GetListItem(int position);
    int GetListSize() const;
    int GetCurrentListPosition() const;
    void SetCurrentListPosition(int item);
    void SetContainerProperty(const std::string& key, const std::string& value);
    void SetContainerContent(const std::string& value);
    int GetCurrentContainerControlId();
    CGUIControl* GetAddonControl(int controlId,
                                 CGUIControl::GUICONTROLTYPES type,
                                 const std::string& typeName);

  protected:
    void GetContextButtons(int itemNumber, CContextButtons& buttons) override;
    bool OnContextButton(int itemNumber, CONTEXT_BUTTON button) override;
    void SetupShares() override;

    /* universalmediacenter to addon callback function addresses */
    UNIVERSALMEDIA_GUI_CLIENT_HANDLE m_clientHandle = nullptr;
    bool (*CBOnInit)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl) = nullptr;
    bool (*CBOnFocus)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl, int controlId) = nullptr;
    bool (*CBOnClick)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl, int controlId) = nullptr;
    bool (*CBOnAction)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl, ADDON_ACTION actionId) = nullptr;
    void (*CBGetContextButtons)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl,
                                int itemNumber,
                                gui_context_menu_pair* buttons,
                                unsigned int* size) = nullptr;
    bool (*CBOnContextButton)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl,
                              int itemNumber,
                              unsigned int button) = nullptr;

    const int m_windowId{0};
    int m_oldWindowId{0};

  private:
    void WaitForActionEvent(unsigned int timeout);

    CEvent m_actionEvent{true};
    ADDON::CAddonDll* m_addon{nullptr};
    std::string m_mediaDir;
    bool m_isMedia{false};
  };

  class CGUIAddonWindowDialog : public CGUIAddonWindow
  {
  public:
    CGUIAddonWindowDialog(int id, const std::string& strXML, ADDON::CAddonDll* addon);

    bool IsDialogRunning() const override { return m_bRunning; }
    bool IsDialog() const override { return true; }
    bool IsModalDialog() const override { return true; }

    void Show(bool show = true, bool modal = true);
    void Show_Internal(bool show = true);

  private:
    bool m_bRunning = false;
  };

  } /* namespace ADDON */
} /* extern "C" */
