/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Label.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Label.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUILabelControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlLabel::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_label =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_label();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_label->set_visible = set_visible;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_label->set_label = set_label;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_label->get_label = get_label;
}

void Interface_GUIControlLabel::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_label;
}

void Interface_GUIControlLabel::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                            UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                            bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUILabelControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetVisible(visible);
}

void Interface_GUIControlLabel::set_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                          UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                          const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUILabelControl*>(handle);
  if (!addon || !control || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_SET, control->GetParentID(), control->GetID());
  msg.SetLabel(label);
  CServiceBroker::GetGUI()->GetWindowManager().SendThreadMessage(msg, control->GetParentID());
}

char* Interface_GUIControlLabel::get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUILabelControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  return strdup(control->GetDescription().c_str());
}

} /* namespace ADDON */
