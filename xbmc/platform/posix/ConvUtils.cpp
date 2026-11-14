/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>

#include "PlatformDefs.h"

DWORD GetLastError()
{
  return errno;
}

void SetLastError(DWORD dwErrCode)
{
  errno = dwErrCode;
}
