/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "platform/Platform.h"

class CPlatformWin32 : public CPlatform
{
public:
  CPlatformWin32() = default;

  ~CPlatformWin32() = default;

  bool InitStageOne() override;
  void PlatformSyslog() override;
};
