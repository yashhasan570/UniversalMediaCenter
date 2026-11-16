/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Rendering.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/interfaces/gui/General.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Rendering.h"
#include "guilib/GUIRenderingControl.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlAddonRendering::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_rendering =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_rendering();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_rendering->set_callbacks = set_callbacks;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_rendering->destroy = destroy;
}

void Interface_GUIControlAddonRendering::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_rendering;
}

void Interface_GUIControlAddonRendering::set_callbacks(
    UNIVERSALMEDIA_HANDLE universalmediacenterBase,
    UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
    UNIVERSALMEDIA_GUI_CLIENT_HANDLE clienthandle,
    bool (*createCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE, int, int, int, int, ADDON_HARDWARE_CONTEXT),
    void (*renderCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
    void (*stopCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE),
    bool (*dirtyCB)(UNIVERSALMEDIA_GUI_CLIENT_HANDLE))
{
  auto* addon = static_cast<CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIAddonRenderingControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  Interface_GUIGeneral::lock();
  control->m_clientHandle = clienthandle;
  control->CBCreate = createCB;
  control->CBRender = renderCB;
  control->CBStop = stopCB;
  control->CBDirty = dirtyCB;
  control->m_addon = addon;
  Interface_GUIGeneral::unlock();

  control->m_control->InitCallback(control);
}

void Interface_GUIControlAddonRendering::destroy(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                 UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIAddonRenderingControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  Interface_GUIGeneral::lock();
  control->Delete();
  Interface_GUIGeneral::unlock();
}

CGUIAddonRenderingControl::CGUIAddonRenderingControl(CGUIRenderingControl* control)
  : m_control{control}
{
}

bool CGUIAddonRenderingControl::Create(int x, int y, int w, int h, void* device)
{
  if (CBCreate && CBCreate(m_clientHandle, x, y, w, h, device))
  {
    ++m_refCount;
    return true;
  }
  return false;
}

void CGUIAddonRenderingControl::Render()
{
  if (CBRender)
  {
    CBRender(m_clientHandle);
  }
}

void CGUIAddonRenderingControl::Stop()
{
  if (CBStop)
  {
    CBStop(m_clientHandle);
  }

  --m_refCount;
  if (m_refCount <= 0)
    delete this;
}

void CGUIAddonRenderingControl::Delete()
{
  --m_refCount;
  if (m_refCount <= 0)
    delete this;
}

bool CGUIAddonRenderingControl::IsDirty()
{
  bool ret = true;
  if (CBDirty)
  {
    ret = CBDirty(m_clientHandle);
  }
  return ret;
}

} /* namespace ADDON */
