/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoX11.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace RETRO;

CRPProcessInfoX11::CRPProcessInfoX11() : CRPProcessInfo("X11")
{
}

std::unique_ptr<CRPProcessInfo> CRPProcessInfoX11::Create()
{
  return std::make_unique<CRPProcessInfoX11>();
}

void CRPProcessInfoX11::Register()
{
  CRPProcessInfo::RegisterProcessControl(CRPProcessInfoX11::Create);
}
