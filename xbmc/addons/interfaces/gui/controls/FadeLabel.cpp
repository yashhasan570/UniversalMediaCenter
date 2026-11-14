/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "FadeLabel.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/FadeLabel.h"
#include "guilib/GUIFadeLabelControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlFadeLabel::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->->control_fade_label =
      new AddonToUniversal Media CenterFuncTable__control_fade_label();

  addonInterface->toUniversal Media Center->->control_fade_label->set_visible = set_visible;
  addonInterface->toUniversal Media Center->->control_fade_label->add_label = add_label;
  addonInterface->toUniversal Media Center->->control_fade_label->get_label = get_label;
  addonInterface->toUniversal Media Center->->control_fade_label->set_scrolling = set_scrolling;
  addonInterface->toUniversal Media Center->->control_fade_label->reset = reset;
}

void Interface_GUIControlFadeLabel::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->->control_fade_label;
}

void Interface_GUIControlFadeLabel::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIFadeLabelControl*>(handle);
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

void Interface_GUIControlFadeLabel::add_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                              UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                              const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIFadeLabelControl*>(handle);
  if (!addon || !control || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}', label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_ADD, control->GetParentID(), control->GetID());
  msg.SetLabel(label);
  control->OnMessage(msg);
}

char* Interface_GUIControlFadeLabel::get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIFadeLabelControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  CGUIMessage msg(GUI_MSG_ITEM_SELECTED, control->GetParentID(), control->GetID());
  control->OnMessage(msg);
  return strdup(msg.GetLabel().c_str());
}

void Interface_GUIControlFadeLabel::set_scrolling(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  bool scroll)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIFadeLabelControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetScrolling(scroll);
}

void Interface_GUIControlFadeLabel::reset(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIFadeLabelControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  CGUIMessage msg(GUI_MSG_LABEL_RESET, control->GetParentID(), control->GetID());
  control->OnMessage(msg);
}

} /* namespace ADDON */
