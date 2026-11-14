/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoGbm.h"

using namespace KODI;
using namespace RETRO;

CRPProcessInfoGbm::CRPProcessInfoGbm() : CRPProcessInfoEGL("GBM")
{
}

std::unique_ptr<CRPProcessInfo> CRPProcessInfoGbm::Create()
{
  return std::make_unique<CRPProcessInfoGbm>();
}

void CRPProcessInfoGbm::Register()
{
  CRPProcessInfo::RegisterProcessControl(CRPProcessInfoGbm::Create);
}
