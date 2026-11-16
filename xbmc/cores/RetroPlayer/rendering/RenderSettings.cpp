/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RenderSettings.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace RETRO;

void CRenderSettings::Reset()
{
  m_videoSettings.Reset();
}

bool CRenderSettings::operator==(const CRenderSettings& rhs) const
{
  return m_videoSettings == rhs.m_videoSettings;
}

bool CRenderSettings::operator<(const CRenderSettings& rhs) const
{
  if (m_videoSettings < rhs.m_videoSettings)
    return true;
  if (m_videoSettings > rhs.m_videoSettings)
    return false;

  return false;
}
