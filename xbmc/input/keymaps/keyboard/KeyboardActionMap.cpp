/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "KeyboardActionMap.h"

#include "ServiceBroker.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "input/InputManager.h"
#include "input/actions/Action.h"
#include "input/keyboard/Key.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace KEYMAP;

unsigned int CKeyboardActionMap::GetActionID(const CKey& key)
{
  CAction action = CServiceBroker::GetInputManager().GetAction(
      CServiceBroker::GetGUI()->GetWindowManager().GetActiveWindowOrDialog(), key);
  return action.GetID();
}
