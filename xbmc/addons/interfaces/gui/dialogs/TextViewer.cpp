/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "TextViewer.h"

#include "ServiceBroker.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/TextViewer.h"
#include "dialogs/GUIDialogTextViewer.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIDialogTextViewer::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->->dialogTextViewer =
      new AddonToUniversal Media CenterFuncTable__dialogTextViewer();

  addonInterface->toUniversal Media Center->->dialogTextViewer->open = open;
}

void Interface_GUIDialogTextViewer::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->->dialogTextViewer;
}

void Interface_GUIDialogTextViewer::open(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         const char* heading,
                                         const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return;
  }

  CGUIDialogTextViewer* dialog =
      CServiceBroker::GetGUI()->GetWindowManager().GetWindow<CGUIDialogTextViewer>(
          WINDOW_DIALOG_TEXT_VIEWER);
  if (!heading || !text || !dialog)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (heading='{}', text='{}', "
               "dialog='{}') on addon '{}'",
               static_cast<const void*>(heading), static_cast<const void*>(text),
               static_cast<void*>(dialog), addon->ID());
    return;
  }

  dialog->SetHeading(heading);
  dialog->SetText(text);
  dialog->Open();
}

} /* namespace ADDON */
