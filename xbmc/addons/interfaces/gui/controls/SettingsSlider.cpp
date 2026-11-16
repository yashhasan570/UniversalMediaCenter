/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "SettingsSlider.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/SettingsSlider.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUISettingsSliderControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlSettingsSlider::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_settings_slider();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_visible = set_visible;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_enabled = set_enabled;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_text = set_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->reset = reset;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_int_range = set_int_range;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_int_value = set_int_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->get_int_value = get_int_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_int_interval = set_int_interval;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_percentage = set_percentage;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->get_percentage = get_percentage;

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_float_range = set_float_range;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_float_value = set_float_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->get_float_value = get_float_value;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider->set_float_interval =
      set_float_interval;
}

void Interface_GUIControlSettingsSlider::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_settings_slider;
}

void Interface_GUIControlSettingsSlider::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                     UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                     bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
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

void Interface_GUIControlSettingsSlider::set_enabled(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                     UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                     bool enabled)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
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

void Interface_GUIControlSettingsSlider::set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISettingsSliderControl*>(handle);
  if (!addon || !control || !text)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}', text='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(text), addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_SET, control->GetParentID(), control->GetID());
  msg.SetLabel(text);
  CServiceBroker::GetGUI()->GetWindowManager().SendThreadMessage(msg, control->GetParentID());
}

void Interface_GUIControlSettingsSlider::reset(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_RESET, control->GetParentID(), control->GetID());
  CServiceBroker::GetGUI()->GetWindowManager().SendThreadMessage(msg, control->GetParentID());
}

void Interface_GUIControlSettingsSlider::set_int_range(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                       UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                       int start,
                                                       int end)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetType(SLIDER_CONTROL_TYPE_INT);
  control->SetRange(start, end);
}

void Interface_GUIControlSettingsSlider::set_int_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                       UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                       int value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetType(SLIDER_CONTROL_TYPE_INT);
  control->SetIntValue(value);
}

int Interface_GUIControlSettingsSlider::get_int_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                      UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return -1;
  }

  return control->GetIntValue();
}

void Interface_GUIControlSettingsSlider::set_int_interval(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                          UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                          int interval)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetIntInterval(interval);
}

void Interface_GUIControlSettingsSlider::set_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                        UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                        float percent)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetType(SLIDER_CONTROL_TYPE_PERCENTAGE);
  control->SetPercentage(percent);
}

float Interface_GUIControlSettingsSlider::get_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return 0.0f;
  }

  return control->GetPercentage();
}

void Interface_GUIControlSettingsSlider::set_float_range(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                         float start,
                                                         float end)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetType(SLIDER_CONTROL_TYPE_FLOAT);
  control->SetFloatRange(start, end);
}

void Interface_GUIControlSettingsSlider::set_float_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                         float value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetType(SLIDER_CONTROL_TYPE_FLOAT);
  control->SetFloatValue(value);
}

float Interface_GUIControlSettingsSlider::get_float_value(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                          UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return 0.0f;
  }

  return control->GetFloatValue();
}

void Interface_GUIControlSettingsSlider::set_float_interval(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                            UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                            float interval)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUISettingsSliderControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetFloatInterval(interval);
}

} /* namespace ADDON */
