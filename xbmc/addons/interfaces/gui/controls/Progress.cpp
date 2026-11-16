/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Progress.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Progress.h"
#include "guilib/GUIProgressControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlProgress::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_progress =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_progress();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_progress->set_visible = set_visible;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_progress->set_percentage = set_percentage;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_progress->get_percentage = get_percentage;
}

void Interface_GUIControlProgress::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_progress;
}

void Interface_GUIControlProgress::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                               UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                               bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIProgressControl*>(handle);
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

void Interface_GUIControlProgress::set_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  float percent)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIProgressControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetPercentage(percent);
}

float Interface_GUIControlProgress::get_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIProgressControl*>(handle);
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

} /* namespace ADDON */
