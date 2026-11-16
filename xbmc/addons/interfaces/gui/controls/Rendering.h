/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/controls/rendering.h"
#include "guilib/IRenderingCallback.h"

class CGUIRenderingControl;

extern "C"
{

  struct AddonGlobalInterface;

  namespace ADDON
  {

  class CAddonDll;

  /*!
   * @brief Global gui Add-on to Universal Media Center callback functions
   *
   * To hold general gui functions and initialize also all other gui related types not
   * related to a instance type and usable for every add-on type.
   *
   * Related add-on header is "./xbmc/addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Rendering.h"
   */
  struct Interface_GUIControlAddonRendering
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
    static void set_callbacks(
        UNIVERSALMEDIA_HANDLE universalmediacenterBase,
        UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
        UNIVERSALMEDIA_GUI_CLIENT_HANDLE clienthandle,
        bool (*createCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int, int, int, int, ADDON_HARDWARE_CONTEXT),
        void (*renderCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
        void (*stopCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
        bool (*dirtyCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE));
    static void destroy(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle);
    //@}
  };

  class CGUIAddonRenderingControl : public IRenderingCallback
  {
    friend struct Interface_GUIControlAddonRendering;

  public:
    explicit CGUIAddonRenderingControl(CGUIRenderingControl* pControl);
    ~CGUIAddonRenderingControl() override = default;

    bool Create(int x, int y, int w, int h, void* device) override;
    void Render() override;
    void Stop() override;
    bool IsDirty() override;
    virtual void Delete();

  private:
    bool (*CBCreate)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl, int x, int y, int w, int h, void* device) =
        nullptr;
    void (*CBRender)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl) = nullptr;
    void (*CBStop)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl) = nullptr;
    bool (*CBDirty)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE cbhdl) = nullptr;

    UNIVERSALMEDIA_GUI_CLIENT_HANDLE m_clientHandle{nullptr};
    CAddonDll* m_addon{nullptr};
    CGUIRenderingControl* m_control{nullptr};
    int m_refCount{1};
  };

  } /* namespace ADDON */
} /* extern "C" */
