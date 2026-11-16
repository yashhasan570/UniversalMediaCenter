/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RPProcessInfoOSX.h"

#include <dlfcn.h>

using namespace UNIVERSAL MEDIA CENTER;
using namespace RETRO;

CRPProcessInfoOSX::CRPProcessInfoOSX() : CRPProcessInfo("macOS")
{
}

std::unique_ptr<CRPProcessInfo> CRPProcessInfoOSX::Create()
{
  return std::make_unique<CRPProcessInfoOSX>();
}

void CRPProcessInfoOSX::Register()
{
  CRPProcessInfo::RegisterProcessControl(CRPProcessInfoOSX::Create);
}

HwProcedureAddress CRPProcessInfoOSX::GetHwProcedureAddress(const char* symbol)
{
  return symbol ? reinterpret_cast<HwProcedureAddress>(dlsym(RTLD_DEFAULT, symbol)) : nullptr;
}
