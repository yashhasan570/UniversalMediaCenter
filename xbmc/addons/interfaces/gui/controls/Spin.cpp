/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Spin.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Spin.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUISpinControlEx.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlSpin::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin = new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_spin();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_visible = set_visible;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_enabled = set_enabled;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_text = set_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->reset = reset;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_type = set_type;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->add_string_label = add_string_label;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_string_value = set_string_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->get_string_value = get_string_value;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->add_int_label = add_int_label;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_int_range = set_int_range;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_int_value = set_int_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->get_int_value = get_int_value;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_float_range = set_float_range;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_float_value = set_float_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->get_float_value = get_float_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin->set_float_interval = set_float_interval;
}

void Interface_GUIControlSpin::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_spin;
}

void Interface_GUIControlSpin::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                           bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
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

void Interface_GUIControlSpin::set_enabled(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                           bool enabled)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
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

void Interface_GUIControlSpin::set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                        UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                        const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISpinControlEx*>(handle);
  if (!addon || !control || !text)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "text='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(text), addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_SET, control->GetParentID(), control->GetID());
  msg.SetLabel(text);
  CServiceBroker::GetGUI()->GetWindowManager().SendThreadMessage(msg, control->GetParentID());
}

void Interface_GUIControlSpin::reset(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_RESET, control->GetParentID(), control->GetID());
  CServiceBroker::GetGUI()->GetWindowManager().SendThreadMessage(msg, control->GetParentID());
}

void Interface_GUIControlSpin::set_type(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                        UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                        int type)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetType(type);
}

void Interface_GUIControlSpin::add_string_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                const char* label,
                                                const char* value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control || !label || !value)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}', value='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), static_cast<const void*>(value),
               addon ? addon->ID() : "unknown");
    return;
  }

  control->AddLabel(std::string(label), std::string(value));
}

void Interface_GUIControlSpin::set_string_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                const char* value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control || !value)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "value='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(value), addon ? addon->ID() : "unknown");
    return;
  }

  control->SetStringValue(std::string(value));
}

char* Interface_GUIControlSpin::get_string_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                 UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  return strdup(control->GetStringValue().c_str());
}

void Interface_GUIControlSpin::add_int_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                             const char* label,
                                             int value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  control->AddLabel(std::string(label), value);
}

void Interface_GUIControlSpin::set_int_range(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                             int start,
                                             int end)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetRange(start, end);
}

void Interface_GUIControlSpin::set_int_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                             int value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetValue(value);
}

int Interface_GUIControlSpin::get_int_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return -1;
  }

  return control->GetValue();
}

void Interface_GUIControlSpin::set_float_range(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                               UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                               float start,
                                               float end)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetFloatRange(start, end);
}

void Interface_GUIControlSpin::set_float_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                               UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                               float value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetFloatValue(value);
}

float Interface_GUIControlSpin::get_float_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return 0.0f;
  }

  return control->GetFloatValue();
}

void Interface_GUIControlSpin::set_float_interval(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  float interval)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISpinControlEx*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetFloatInterval(interval);
}

} /* namespace ADDON */
