/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

class CFileItem;
class CURL;

namespace UNIVERSAL MEDIA CENTER::PLAYLIST
{
  class CPlayList;

  class CPlayListFactory
  {
  public:
    static CPlayList* Create(const CURL& url);
    static CPlayList* Create(const std::string& filename);
    static CPlayList* Create(const CFileItem& item);
    static bool IsPlaylist(const CURL& url);
    static bool IsPlaylist(const std::string& filename);
    static bool IsPlaylist(const CFileItem& item);
  };
}
