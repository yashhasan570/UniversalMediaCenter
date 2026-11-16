/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ButtonDetector.h"

#include "input/joysticks/DriverPrimitive.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace JOYSTICK;

CButtonDetector::CButtonDetector(CButtonMapping* buttonMapping, unsigned int buttonIndex)
  : CPrimitiveDetector(buttonMapping),
    m_buttonIndex(buttonIndex)
{
}

bool CButtonDetector::OnMotion(bool bPressed)
{
  if (bPressed)
    return MapPrimitive(CDriverPrimitive(PRIMITIVE_TYPE::BUTTON, m_buttonIndex));

  return false;
}
