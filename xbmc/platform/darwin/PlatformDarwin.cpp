/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "PlatformDarwin.h"

#include "filesystem/SpecialProtocol.h"

#include <cstdlib>

bool CPlatformDarwin::InitStageOne()
{
  if (!CPlatformPosix::InitStageOne())
    return false;
  setenv("SSL_CERT_FILE", CSpecialProtocol::TranslatePath("special:///system/certs/cacert.pem").c_str(), 0);

  setenv("OS", "OS X", true); // for python scripts that check the OS

  return true;
}
