/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "IFileDirectory.h"

#include <string>

namespace KODI::PLAYLIST
{
class CSmartPlaylist;
}

namespace XFILE
{
  class CSmartPlaylistDirectory : public IFileDirectory
  {
  public:
    CSmartPlaylistDirectory();
    ~CSmartPlaylistDirectory() override;
    bool GetDirectory(const CURL& url, CFileItemList& items) override;
    bool AllowAll() const override { return true; }
    bool ContainsFiles(const CURL& url) override;
    bool Remove(const CURL& url) override;

    static bool GetDirectory(const KODI::PLAYLIST::CSmartPlaylist& playlist,
                             CFileItemList& items,
                             const std::string& strBaseDir = "",
                             bool filter = false);

    static std::string GetPlaylistByName(const std::string& name, const std::string& playlistType);
  };
}
