/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "PrimitiveDetector.h"

#include "ButtonMapping.h"

using namespace KODI;
using namespace JOYSTICK;

CPrimitiveDetector::CPrimitiveDetector(CButtonMapping* buttonMapping)
  : m_buttonMapping(buttonMapping)
{
}

bool CPrimitiveDetector::MapPrimitive(const CDriverPrimitive& primitive)
{
  if (primitive.IsValid())
    return m_buttonMapping->MapPrimitive(primitive);

  return false;
}
