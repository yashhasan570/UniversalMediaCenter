/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoAndroid.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace RETRO;

CRPProcessInfoAndroid::CRPProcessInfoAndroid() : CRPProcessInfoEGL("Android")
{
}

std::unique_ptr<CRPProcessInfo> CRPProcessInfoAndroid::Create()
{
  return std::make_unique<CRPProcessInfoAndroid>();
}

void CRPProcessInfoAndroid::Register()
{
  CRPProcessInfo::RegisterProcessControl(CRPProcessInfoAndroid::Create);
}
