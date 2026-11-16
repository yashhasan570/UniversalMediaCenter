/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ContextMenu.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/ContextMenu.h"
#include "dialogs/GUIDialogContextMenu.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIDialogContextMenu::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogContextMenu =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogContextMenu();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogContextMenu->open = open;
}

void Interface_GUIDialogContextMenu::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogContextMenu;
}

int Interface_GUIDialogContextMenu::open(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         const char* heading,
                                         const char* entries[],
                                         unsigned int size)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return -1;
  }

  if (!heading || !entries)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (heading='{}', "
               "entries='{}') on addon '{}'",
               static_cast<const void*>(heading), static_cast<const void*>(entries), addon->ID());
    return -1;
  }

  CContextButtons choices;
  for (unsigned int i = 0; i < size; ++i)
    choices.Add(i, entries[i]);

  return CGUIDialogContextMenu::Show(choices);
}

} /* namespace ADDON */
