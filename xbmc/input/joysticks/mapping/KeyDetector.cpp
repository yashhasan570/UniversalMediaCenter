/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "KeyDetector.h"

#include "input/joysticks/DriverPrimitive.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace JOYSTICK;

CKeyDetector::CKeyDetector(CButtonMapping* buttonMapping, Key keycode)
  : CPrimitiveDetector(buttonMapping),
    m_keycode(keycode)
{
}

bool CKeyDetector::OnMotion(bool bPressed)
{
  if (bPressed)
    return MapPrimitive(CDriverPrimitive(m_keycode));

  return false;
}
