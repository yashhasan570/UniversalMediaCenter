/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlayList.h"

namespace UNIVERSAL MEDIA CENTER::PLAYLIST
{

class CPlayListWPL : public CPlayList
{
public:
  CPlayListWPL(void);
  ~CPlayListWPL(void) override;
  bool LoadData(std::istream& stream) override;
  void Save(const std::string& strFileName) const override;
};
}
