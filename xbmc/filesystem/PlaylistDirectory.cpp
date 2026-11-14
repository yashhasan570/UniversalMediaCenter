/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "PlaylistDirectory.h"

#include "FileItem.h"
#include "FileItemList.h"
#include "PlayListPlayer.h"
#include "ServiceBroker.h"
#include "URL.h"
#include "playlists/PlayList.h"
#include "utils/ItemProperties.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace XFILE;

CPlaylistDirectory::CPlaylistDirectory() = default;

CPlaylistDirectory::~CPlaylistDirectory() = default;

bool CPlaylistDirectory::GetDirectory(const CURL& url, CFileItemList &items)
{
  PLAYLIST::Id playlistId = PLAYLIST::Id::TYPE_NONE;
  if (url.IsProtocol("playlistmusic"))
    playlistId = PLAYLIST::Id::TYPE_MUSIC;
  else if (url.IsProtocol("playlistvideo"))
    playlistId = PLAYLIST::Id::TYPE_VIDEO;

  if (playlistId == PLAYLIST::Id::TYPE_NONE)
    return false;

  const PLAYLIST::CPlayList& playlist = CServiceBroker::GetPlaylistPlayer().GetPlaylist(playlistId);
  items.Reserve(playlist.size());

  for (int i = 0; i < playlist.size(); ++i)
  {
    CFileItemPtr item = playlist[i];
    item->SetProperty(ITEM::PROPERTY::PLAYLIST_POSITION, i);
    item->SetProperty("playlisttype", static_cast<int>(playlistId));
    //item->SetProgramCount(i); // the programCount is set as items are added!
    items.Add(item);
  }

  return true;
}
