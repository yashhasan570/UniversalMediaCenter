/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlayList.h"

namespace UNIVERSAL MEDIA CENTER::PLAYLIST
{

class CPlayListB4S : public CPlayList
{
public:
  CPlayListB4S(void);
  ~CPlayListB4S(void) override;
  bool LoadData(std::istream& stream) override;
  void Save(const std::string& strFileName) const override;
};
} // namespace UNIVERSAL MEDIA CENTER::PLAYLIST
