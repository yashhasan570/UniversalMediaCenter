/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DRMUtils.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace GBM
{

class COffScreenModeSetting : public CDRMUtils
{
public:
  COffScreenModeSetting() = default;
  ~COffScreenModeSetting() override = default;
  void FlipPage(struct gbm_bo* bo, bool rendered, bool videoLayer, bool async) override {}
  bool SetVideoMode(const RESOLUTION_INFO& res, struct gbm_bo* bo) override { return false; }
  bool SetActive(bool active) override { return false; }
  bool InitDrm() override;
  void DestroyDrm() override {}

  RESOLUTION_INFO GetCurrentMode() override;
  std::vector<RESOLUTION_INFO> GetModes() override;
  bool SetMode(const RESOLUTION_INFO& res) override { return true; }
};

} // namespace GBM
} // namespace WINDOWING
} // namespace UNIVERSAL MEDIA CENTER
