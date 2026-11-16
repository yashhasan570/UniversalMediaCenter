/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */
#pragma once

#include "cores/RetroPlayer/process/RPProcessInfo.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRPProcessInfoEGL : public CRPProcessInfo
{
public:
  CRPProcessInfoEGL(std::string platformName);
  ~CRPProcessInfoEGL() override = default;

  // Implementation of CRPProcessInfo
  HwProcedureAddress GetHwProcedureAddress(const char* symbol) override;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
