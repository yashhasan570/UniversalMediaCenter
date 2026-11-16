/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../ProcessInfo.h"

namespace VIDEOPLAYER
{

class CProcessInfoIOS : public CProcessInfo
{
public:
  static CProcessInfo* Create();
  static void Register();

  void SetSwDeinterlacingMethods() override;
};

}
