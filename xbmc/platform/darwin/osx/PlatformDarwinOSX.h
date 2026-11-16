/*
 *  Copyright (C) 2005-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "platform/darwin/PlatformDarwin.h"
#include "platform/darwin/osx/HotKeyController.h"

class CPlatformDarwinOSX : public CPlatformDarwin
{
public:
  CPlatformDarwinOSX() = default;

  ~CPlatformDarwinOSX() override = default;

  bool InitStageOne() override;
  bool InitStageTwo() override;

private:
  CHotKeyController m_hotkeyController;
};
