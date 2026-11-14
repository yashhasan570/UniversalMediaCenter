/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "KeymapEnvironment.h"

#include "input/WindowTranslator.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace KEYMAP;

int CKeymapEnvironment::GetFallthrough(int windowId) const
{
  return CWindowTranslator::GetFallbackWindow(windowId);
}
