/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "emu_dummy.h"

#include "utils/log.h"

extern "C" void not_implement( const char* debuginfo)
{
  if (debuginfo)
  {
    CLog::Log(LOGDEBUG, "{}", debuginfo);
  }
}

