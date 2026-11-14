/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Progress.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/kodi-dev-kit/include/kodi/gui/controls/Progress.h"
#include "guilib/GUIProgressControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlProgress::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->kodi_gui->control_progress =
      new AddonToUniversal Media CenterFuncTable_kodi_gui_control_progress();

  addonInterface->toUniversal Media Center->kodi_gui->control_progress->set_visible = set_visible;
  addonInterface->toUniversal Media Center->kodi_gui->control_progress->set_percentage = set_percentage;
  addonInterface->toUniversal Media Center->kodi_gui->control_progress->get_percentage = get_percentage;
}

void Interface_GUIControlProgress::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->kodi_gui->control_progress;
}

void Interface_GUIControlProgress::set_visible(KODI_HANDLE kodiBase,
                                               KODI_GUI_CONTROL_HANDLE handle,
                                               bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(kodiBase);
  auto* control = static_cast<CGUIProgressControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (kodiBase='{}', "
               "handle='{}') on addon '{}'",
               kodiBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetVisible(visible);
}

void Interface_GUIControlProgress::set_percentage(KODI_HANDLE kodiBase,
                                                  KODI_GUI_CONTROL_HANDLE handle,
                                                  float percent)
{
  const auto* addon = static_cast<const CAddonDll*>(kodiBase);
  auto* control = static_cast<CGUIProgressControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (kodiBase='{}', "
               "handle='{}') on addon '{}'",
               kodiBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetPercentage(percent);
}

float Interface_GUIControlProgress::get_percentage(KODI_HANDLE kodiBase,
                                                   KODI_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(kodiBase);
  const auto* control = static_cast<const CGUIProgressControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (kodiBase='{}', "
               "handle='{}') on addon '{}'",
               kodiBase, handle, addon ? addon->ID() : "unknown");
    return 0.0f;
  }

  return control->GetPercentage();
}

} /* namespace ADDON */
