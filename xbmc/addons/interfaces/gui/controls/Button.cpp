/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Button.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Button.h"
#include "guilib/GUIButtonControl.h"
#include "utils/StringUtils.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlButton::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->->control_button =
      new AddonToUniversal Media CenterFuncTable__control_button();

  addonInterface->toUniversal Media Center->->control_button->set_visible = set_visible;
  addonInterface->toUniversal Media Center->->control_button->set_enabled = set_enabled;

  addonInterface->toUniversal Media Center->->control_button->set_label = set_label;
  addonInterface->toUniversal Media Center->->control_button->get_label = get_label;

  addonInterface->toUniversal Media Center->->control_button->set_label2 = set_label2;
  addonInterface->toUniversal Media Center->->control_button->get_label2 = get_label2;
}

void Interface_GUIControlButton::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->->control_button;
}

void Interface_GUIControlButton::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                             bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIButtonControl*>(handle);
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

void Interface_GUIControlButton::set_enabled(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                             bool enabled)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetEnabled(enabled);
}

void Interface_GUIControlButton::set_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                           const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIButtonControl*>(handle);
  if (!addon || !control || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  control->SetLabel(label);
}

char* Interface_GUIControlButton::get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const CGUIButtonControl* control = static_cast<const CGUIButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  return strdup(control->GetLabel().c_str());
}

void Interface_GUIControlButton::set_label2(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                            UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                            const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIButtonControl*>(handle);
  if (!addon || !control || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  control->SetLabel2(label);
}

char* Interface_GUIControlButton::get_label2(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  return strdup(control->GetLabel2().c_str());
}

} /* namespace ADDON */
