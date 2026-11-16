/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "RenderVideoSettings.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRenderSettings
{
public:
  CRenderSettings() { Reset(); }

  void Reset();

  bool operator==(const CRenderSettings& rhs) const;
  bool operator<(const CRenderSettings& rhs) const;

  CRenderVideoSettings& VideoSettings() { return m_videoSettings; }
  const CRenderVideoSettings& VideoSettings() const { return m_videoSettings; }

private:
  CRenderVideoSettings m_videoSettings;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
