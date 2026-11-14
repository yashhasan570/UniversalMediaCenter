/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "input/keyboard/KeyboardEasterEgg.h"

#include "input/joysticks/JoystickEasterEgg.h"
#include "input/keyboard/Key.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace KEYBOARD;

std::vector<VKey> CKeyboardEasterEgg::m_sequence = {
    VK_UP,    VK_UP,   VK_DOWN,  VK_DOWN, VK_LEFT,
    VK_RIGHT, VK_LEFT, VK_RIGHT, VK_B,    VK_A,
};

bool CKeyboardEasterEgg::OnKeyPress(const CKey& key)
{
  bool bHandled = false;

  // Update state
  if (key.GetVKey() == m_sequence[m_state])
    m_state++;
  else
    m_state = 0;

  // Capture input when finished with arrows (2 x up/down/left/right)
  if (m_state > 8)
  {
    bHandled = true;

    if (m_state >= m_sequence.size())
    {
      JOYSTICK::CJoystickEasterEgg::OnFinish();
      m_state = 0;
    }
  }

  return bHandled;
}
