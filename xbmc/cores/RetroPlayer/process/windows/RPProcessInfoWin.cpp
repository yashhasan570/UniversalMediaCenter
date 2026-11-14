/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoWin.h"

#include "cores/RetroPlayer/rendering/VideoRenderers/RPWinRenderer.h"

using namespace KODI;
using namespace RETRO;

CRPProcessInfoWin::CRPProcessInfoWin() : CRPProcessInfo("Windows")
{
}

std::unique_ptr<CRPProcessInfo> CRPProcessInfoWin::Create()
{
  return std::make_unique<CRPProcessInfoWin>();
}

void CRPProcessInfoWin::Register()
{
  CRPProcessInfo::RegisterProcessControl(CRPProcessInfoWin::Create);
}
