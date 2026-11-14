/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ModuleXbmcgui.h"

#include "LanguageHook.h"
#include "ServiceBroker.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "windowing/GraphicContext.h"
#include "windowing/WinSystem.h"

#include <mutex>

#define NOTIFICATION_INFO     "info"
#define NOTIFICATION_WARNING  "warning"
#define NOTIFICATION_ERROR    "error"

namespace Addon
{
  namespace gui
  {
    long getCurrentWindowId()
    {
      DelayedCallGuard dg;
      std::unique_lock gl(CServiceBroker::GetWinSystem()->GetGfxContext());
      return CServiceBroker::GetGUI()->GetWindowManager().GetActiveWindow();
    }

    long getCurrentWindowDialogId()
    {
      DelayedCallGuard dg;
      std::unique_lock gl(CServiceBroker::GetWinSystem()->GetGfxContext());
      return CServiceBroker::GetGUI()->GetWindowManager().GetTopmostModalDialog();
    }

    long getScreenHeight()
    {
      _TRACE;
      return CServiceBroker::GetWinSystem()->GetGfxContext().GetHeight();
    }

    long getScreenWidth()
    {
      _TRACE;
      return CServiceBroker::GetWinSystem()->GetGfxContext().GetWidth();
    }

    const char* getNOTIFICATION_INFO()    { return NOTIFICATION_INFO; }
    const char* getNOTIFICATION_WARNING() { return NOTIFICATION_WARNING; }
    const char* getNOTIFICATION_ERROR()   { return NOTIFICATION_ERROR; }

  }
}
