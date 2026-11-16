/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "TextBox.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/TextBox.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUITextBox.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlTextBox::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_text_box();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box->set_visible = set_visible;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box->reset = reset;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box->set_text = set_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box->get_text = get_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box->scroll = scroll;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box->set_auto_scrolling = set_auto_scrolling;
}

void Interface_GUIControlTextBox::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_text_box;
}

void Interface_GUIControlTextBox::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                              UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                              bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUITextBox*>(handle);
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

void Interface_GUIControlTextBox::reset(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUITextBox*>(handle);
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

void Interface_GUIControlTextBox::set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                           const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUITextBox*>(handle);
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

char* Interface_GUIControlTextBox::get_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUITextBox*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  return strdup(control->GetDescription().c_str());
}

void Interface_GUIControlTextBox::scroll(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                         unsigned int position)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUITextBox*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->Scroll(position);
}

void Interface_GUIControlTextBox::set_auto_scrolling(
    UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle, int delay, int time, int repeat)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUITextBox*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetAutoScrolling(delay, time, repeat);
}

} /* namespace ADDON */
