/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ExtendedProgressBar.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/ExtendedProgress.h"
#include "dialogs/GUIDialogExtendedProgressBar.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIDialogExtendedProgress::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogExtendedProgress();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->new_dialog = new_dialog;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->delete_dialog = delete_dialog;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->get_title = get_title;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->set_title = set_title;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->get_text = get_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->set_text = set_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->is_finished = is_finished;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->mark_finished = mark_finished;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->get_percentage = get_percentage;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->set_percentage = set_percentage;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress->set_progress = set_progress;
}

void Interface_GUIDialogExtendedProgress::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogExtendedProgress;
}

UNIVERSALMEDIA_GUI_HANDLE Interface_GUIDialogExtendedProgress::new_dialog(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                                const char* title)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return nullptr;
  }

  // setup the progress dialog
  CGUIDialogExtendedProgressBar* dialog =
      CServiceBroker::GetGUI()->GetWindowManager().GetWindow<CGUIDialogExtendedProgressBar>(
          WINDOW_DIALOG_EXT_PROGRESS);
  if (!title || !dialog)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (title='{}', "
               "dialog='{}') on addon '{}'",
               static_cast<const void*>(title), static_cast<void*>(dialog), addon->ID());
    return nullptr;
  }

  CGUIDialogProgressBarHandle* dlgProgressHandle = dialog->GetHandle(title);
  return dlgProgressHandle;
}

void Interface_GUIDialogExtendedProgress::delete_dialog(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                        UNIVERSALMEDIA_GUI_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return;
  }

  static_cast<CGUIDialogProgressBarHandle*>(handle)->MarkFinished();
}

char* Interface_GUIDialogExtendedProgress::get_title(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return nullptr;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return nullptr;
  }

  return strdup(static_cast<CGUIDialogProgressBarHandle*>(handle)->Title().c_str());
}

void Interface_GUIDialogExtendedProgress::set_title(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                    UNIVERSALMEDIA_GUI_HANDLE handle,
                                                    const char* title)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return;
  }

  if (!handle || !title)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (handle='{}', "
               "title='{}') on addon '{}'",
               handle, static_cast<const void*>(title), addon->ID());
    return;
  }

  static_cast<CGUIDialogProgressBarHandle*>(handle)->SetTitle(title);
}

char* Interface_GUIDialogExtendedProgress::get_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return nullptr;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid add-on data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return nullptr;
  }

  return strdup(static_cast<CGUIDialogProgressBarHandle*>(handle)->Text().c_str());
}

void Interface_GUIDialogExtendedProgress::set_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   UNIVERSALMEDIA_GUI_HANDLE handle,
                                                   const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return;
  }

  if (!handle || !text)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (handle='{}', "
               "text='{}') on addon '{}'",
               handle, static_cast<const void*>(text), addon->ID());
    return;
  }

  static_cast<CGUIDialogProgressBarHandle*>(handle)->SetText(text);
}

bool Interface_GUIDialogExtendedProgress::is_finished(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return false;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid add-on data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return false;
  }

  return static_cast<CGUIDialogProgressBarHandle*>(handle)->IsFinished();
}

void Interface_GUIDialogExtendedProgress::mark_finished(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                        UNIVERSALMEDIA_GUI_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid add-on data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return;
  }

  static_cast<CGUIDialogProgressBarHandle*>(handle)->MarkFinished();
}

float Interface_GUIDialogExtendedProgress::get_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                          UNIVERSALMEDIA_GUI_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return 0.0f;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid add-on data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return 0.0f;
  }

  return static_cast<CGUIDialogProgressBarHandle*>(handle)->Percentage();
}

void Interface_GUIDialogExtendedProgress::set_percentage(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         UNIVERSALMEDIA_GUI_HANDLE handle,
                                                         float percentage)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid add-on data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return;
  }

  static_cast<CGUIDialogProgressBarHandle*>(handle)->SetPercentage(percentage);
}

void Interface_GUIDialogExtendedProgress::set_progress(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                       UNIVERSALMEDIA_GUI_HANDLE handle,
                                                       int currentItem,
                                                       int itemCount)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid universalmediacenter base data");
    return;
  }

  if (!handle)
  {
    CLog::LogF(LOGERROR,
               "Invalid add-on data (handle='{}') on "
               "addon '{}'",
               handle, addon->ID());
    return;
  }

  static_cast<CGUIDialogProgressBarHandle*>(handle)->SetProgress(currentItem, itemCount);
}

} /* namespace ADDON */
