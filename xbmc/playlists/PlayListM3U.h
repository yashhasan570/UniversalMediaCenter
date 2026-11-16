/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlayList.h"

#include <map>
#include <string>

namespace UNIVERSAL MEDIA CENTER::PLAYLIST
{
class CPlayListM3U : public CPlayList
{
public:
  static const char *StartMarker;
  static const char *InfoMarker;
  static const char *ArtistMarker;
  static const char *AlbumMarker;
  static const char *PropertyMarker;
  static const char *VLCOptMarker;
  static const char *StreamMarker;
  static const char *BandwidthMarker;
  static const char *OffsetMarker;

public:
  CPlayListM3U(void);
  ~CPlayListM3U(void) override;
  bool Load(const std::string& strFileName) override;
  void Save(const std::string& strFileName) const override;

  static std::map<std::string,std::string> ParseStreamLine(const std::string &streamLine);
};
}
