/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoIOS.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace RETRO;

CRPProcessInfoIOS::CRPProcessInfoIOS() : CRPProcessInfo("iOS")
{
}

std::unique_ptr<CRPProcessInfo> CRPProcessInfoIOS::Create()
{
  return std::make_unique<CRPProcessInfoIOS>();
}

void CRPProcessInfoIOS::Register()
{
  CRPProcessInfo::RegisterProcessControl(CRPProcessInfoIOS::Create);
}
