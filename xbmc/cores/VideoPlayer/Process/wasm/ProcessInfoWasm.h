/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/VideoPlayer/Process/ProcessInfo.h"

class CProcessInfoWasm : public CProcessInfo
{
public:
  static CProcessInfo* Create();
  static void Register();

  EINTERLACEMETHOD GetFallbackDeintMethod() override;
};
