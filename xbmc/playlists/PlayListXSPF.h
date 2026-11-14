/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlayList.h"

namespace KODI::PLAYLIST
{
class CPlayListXSPF : public CPlayList
{
public:
  CPlayListXSPF(void);
  ~CPlayListXSPF(void) override;

  // Implementation of CPlayList
  bool Load(const std::string& strFileName) override;
};
}
