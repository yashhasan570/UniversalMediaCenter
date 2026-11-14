/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RadioButton.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/RadioButton.h"
#include "guilib/GUIRadioButtonControl.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlRadioButton::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->->control_radio_button =
      new AddonToUniversal Media CenterFuncTable__control_radio_button();

  addonInterface->toUniversal Media Center->->control_radio_button->set_visible = set_visible;
  addonInterface->toUniversal Media Center->->control_radio_button->set_enabled = set_enabled;

  addonInterface->toUniversal Media Center->->control_radio_button->set_label = set_label;
  addonInterface->toUniversal Media Center->->control_radio_button->get_label = get_label;

  addonInterface->toUniversal Media Center->->control_radio_button->set_selected = set_selected;
  addonInterface->toUniversal Media Center->->control_radio_button->is_selected = is_selected;
}

void Interface_GUIControlRadioButton::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->->control_radio_button;
}

void Interface_GUIControlRadioButton::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIRadioButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetVisible(visible);
}

void Interface_GUIControlRadioButton::set_enabled(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  bool enabled)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIRadioButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetEnabled(enabled);
}

void Interface_GUIControlRadioButton::set_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIRadioButtonControl*>(handle);
  if (!addon || !control || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}', label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  control->SetLabel(label);
}

char* Interface_GUIControlRadioButton::get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                 UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIRadioButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  return strdup(control->GetLabel().c_str());
}

void Interface_GUIControlRadioButton::set_selected(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                   bool selected)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIRadioButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetSelected(selected);
}

bool Interface_GUIControlRadioButton::is_selected(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIRadioButtonControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return false;
  }

  return control->IsSelected();
}

} /* namespace ADDON */
