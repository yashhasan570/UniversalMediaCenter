/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlayList.h"

#include <iostream>

namespace KODI::PLAYLIST
{
class CPlayListRAM : public CPlayList
{
public:
  bool LoadData(std::istream& stream) override;
};
} // namespace KODI::PLAYLIST
