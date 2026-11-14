/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Exception.h"

#include "utils/log.h"

namespace XbmcCommons
{
  Exception::~Exception() = default;

  void Exception::LogThrowMessage(const char* prefix) const
  {
    CLog::Log(LOGERROR, "EXCEPTION Thrown ({}) : {}", classname, message);
  }
}

