/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/GameSettings.h"
#include "utils/Observer.h"

#include <string>
#include <string_view>

class CGameSettings : public Observable
{
public:
  CGameSettings() { Reset(); }
  CGameSettings(const CGameSettings &other) { *this = other; }

  CGameSettings &operator=(const CGameSettings &rhs);

  // Restore game settings to default
  void Reset();

  bool operator==(const CGameSettings& rhs) const;

  const std::string &VideoFilter() const { return m_videoFilter; }
  void SetVideoFilter(std::string_view videoFilter);

  UNIVERSAL MEDIA CENTER::RETRO::STRETCHMODE StretchMode() const { return m_stretchMode; }
  void SetStretchMode(UNIVERSAL MEDIA CENTER::RETRO::STRETCHMODE stretchMode);

  unsigned int RotationDegCCW() const { return m_rotationDegCCW; }
  void SetRotationDegCCW(unsigned int rotation);

private:
  // Video settings
  std::string m_videoFilter;
  UNIVERSAL MEDIA CENTER::RETRO::STRETCHMODE m_stretchMode;
  unsigned int m_rotationDegCCW;
};
