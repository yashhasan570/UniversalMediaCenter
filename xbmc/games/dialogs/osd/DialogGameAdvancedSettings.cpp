/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "DialogGameAdvancedSettings.h"

#include "ServiceBroker.h"
#include "addons/AddonManager.h"
#include "addons/addoninfo/AddonType.h"
#include "addons/gui/GUIDialogAddonSettings.h"
#include "cores/RetroPlayer/guibridge/GUIGameRenderManager.h"
#include "cores/RetroPlayer/guibridge/GUIGameSettingsHandle.h"
#include "guilib/GUIMessage.h"
#include "guilib/WindowIDs.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace GAME;

CDialogGameAdvancedSettings::CDialogGameAdvancedSettings()
  : CGUIDialog(WINDOW_DIALOG_GAME_ADVANCED_SETTINGS, "")
{
}

bool CDialogGameAdvancedSettings::OnMessage(CGUIMessage& message)
{
  switch (message.GetMessage())
  {
    case GUI_MSG_WINDOW_INIT:
    {
      auto gameSettingsHandle = CServiceBroker::GetGameRenderManager().RegisterGameSettingsDialog();
      if (gameSettingsHandle)
      {
        ADDON::AddonPtr addon;
        if (CServiceBroker::GetAddonMgr().GetAddon(gameSettingsHandle->GameClientID(), addon,
                                                   ADDON::AddonType::GAMEDLL,
                                                   ADDON::OnlyEnabled::CHOICE_YES))
        {
          gameSettingsHandle.reset();
          CGUIDialogAddonSettings::ShowForAddon(addon);
        }
      }

      return false;
    }
    default:
      break;
  }

  return CGUIDialog::OnMessage(message);
}
