/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Edit.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Edit.h"
#include "guilib/GUIEditControl.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIControlEdit::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit = new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_control_edit();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->set_visible = set_visible;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->set_enabled = set_enabled;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->set_input_type = set_input_type;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->set_label = set_label;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->get_label = get_label;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->set_text = set_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->get_text = get_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->set_cursor_position = set_cursor_position;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit->get_cursor_position = get_cursor_position;
}

void Interface_GUIControlEdit::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->control_edit;
}

void Interface_GUIControlEdit::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                           bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIEditControl*>(handle);
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

void Interface_GUIControlEdit::set_enabled(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                           bool enable)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIEditControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetEnabled(enable);
}

void Interface_GUIControlEdit::set_input_type(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                              UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                              int type,
                                              const char* heading)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIEditControl*>(handle);
  if (!addon || !control || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "heading='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(heading),
               addon ? addon->ID() : "unknown");
    return;
  }

  CGUIEditControl::INPUT_TYPE universalmediacenterType;
  switch (static_cast<AddonGUIInputType>(type))
  {
    case ADDON_INPUT_TYPE_TEXT:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_TEXT;
      break;
    case ADDON_INPUT_TYPE_NUMBER:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_NUMBER;
      break;
    case ADDON_INPUT_TYPE_SECONDS:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_SECONDS;
      break;
    case ADDON_INPUT_TYPE_TIME:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_TIME;
      break;
    case ADDON_INPUT_TYPE_DATE:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_DATE;
      break;
    case ADDON_INPUT_TYPE_IPADDRESS:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_IPADDRESS;
      break;
    case ADDON_INPUT_TYPE_PASSWORD:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_PASSWORD;
      break;
    case ADDON_INPUT_TYPE_PASSWORD_MD5:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_PASSWORD_MD5;
      break;
    case ADDON_INPUT_TYPE_SEARCH:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_SEARCH;
      break;
    case ADDON_INPUT_TYPE_FILTER:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_FILTER;
      break;
    case ADDON_INPUT_TYPE_READONLY:
    default:
      universalmediacenterType = CGUIEditControl::INPUT_TYPE_PASSWORD_NUMBER_VERIFY_NEW;
  }

  control->SetInputType(universalmediacenterType, heading);
}

void Interface_GUIControlEdit::set_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                         const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIEditControl*>(handle);
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

char* Interface_GUIControlEdit::get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIEditControl*>(handle);
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

void Interface_GUIControlEdit::set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                        UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                        const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIEditControl*>(handle);
  if (!addon || !control || !text)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "text='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(text), addon ? addon->ID() : "unknown");
    return;
  }

  control->SetLabel2(text);
}

char* Interface_GUIControlEdit::get_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIEditControl*>(handle);
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

void Interface_GUIControlEdit::set_cursor_position(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                   unsigned int position)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIEditControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetCursorPosition(position);
}

unsigned int Interface_GUIControlEdit::get_cursor_position(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                           UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* control = static_cast<const CGUIEditControl*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return 0;
  }

  return control->GetCursorPosition();
}

} /* namespace ADDON */
