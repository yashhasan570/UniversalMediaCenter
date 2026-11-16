/*
 *  Copyright (C) 2015-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "MediaLibraryEvent.h"

#include "ServiceBroker.h"
#include "filesystem/SourcesDirectory.h"
#include "guilib/GUIComponent.h"
#include "guilib/GUIWindowManager.h"
#include "guilib/WindowIDs.h"
#include "music/MusicDbPaths.h"
#include "resources/LocalizeStrings.h"
#include "resources/ResourcesComponent.h"
#include "utils/URIUtils.h"
#include "video/VideoDbPaths.h"

CMediaLibraryEvent::CMediaLibraryEvent(UNIVERSAL MEDIA CENTER::MEDIA::TYPE mediaType, const std::string& mediaPath, const CVariant& label, const CVariant& description, EventLevel level /* = EventLevel::Information */)
  : CUniqueEvent(label, description, level),
    m_mediaType(mediaType),
    m_mediaPath(mediaPath)
{ }

CMediaLibraryEvent::CMediaLibraryEvent(UNIVERSAL MEDIA CENTER::MEDIA::TYPE mediaType, const std::string& mediaPath, const CVariant& label, const CVariant& description, const std::string& icon, const CVariant& details, EventLevel level /* = EventLevel::Information */)
  : CUniqueEvent(label, description, icon, details, level),
    m_mediaType(mediaType),
    m_mediaPath(mediaPath)
{ }

std::string CMediaLibraryEvent::GetExecutionLabel() const
{
  std::string executionLabel = CUniqueEvent::GetExecutionLabel();
  if (!executionLabel.empty())
    return executionLabel;

  return CServiceBroker::GetResourcesComponent().GetLocalizeStrings().Get(24140);
}

bool CMediaLibraryEvent::Execute() const
{
  if (!CanExecute())
    return false;

  int windowId = -1;
  std::string path = m_mediaPath;
  if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION ||
      m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SEASON || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::EPISODE ||
      m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC_VIDEO)
  {
    if (path.empty())
    {
      if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO)
        path = XFILE::CSourcesDirectory::PathOf(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection::VIDEO);
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE)
        path = UNIVERSAL MEDIA CENTER::VIDEO::DB_PATH::MOVIE_TITLES;
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION)
        path = UNIVERSAL MEDIA CENTER::VIDEO::DB_PATH::MOVIE_SETS;
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC_VIDEO)
        path = UNIVERSAL MEDIA CENTER::VIDEO::DB_PATH::MUSICVIDEO_TITLES;
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SEASON || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::EPISODE)
        path = UNIVERSAL MEDIA CENTER::VIDEO::DB_PATH::TVSHOW_TITLES;
    }
    else
    {
      //! @todo remove the filename for now as CGUIMediaWindow::GetDirectory() can't handle it
      if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC_VIDEO || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::EPISODE)
        path = URIUtils::GetDirectory(path);
    }

    windowId = WINDOW_VIDEO_NAV;
  }
  else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::ARTIST ||
           m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::ALBUM || m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SONG)
  {
    if (path.empty())
    {
      if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC)
        path = XFILE::CSourcesDirectory::PathOf(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection::MUSIC);
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::ARTIST)
        path = UNIVERSAL MEDIA CENTER::MUSIC::DB_PATH::ARTISTS;
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::ALBUM)
        path = UNIVERSAL MEDIA CENTER::MUSIC::DB_PATH::ALBUMS;
      else if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SONG)
        path = UNIVERSAL MEDIA CENTER::MUSIC::DB_PATH::SONGS;
    }
    else
    {
      //! @todo remove the filename for now as CGUIMediaWindow::GetDirectory() can't handle it
      if (m_mediaType == UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SONG)
        path = URIUtils::GetDirectory(path);
    }

    windowId = WINDOW_MUSIC_NAV;
  }

  if (windowId < 0)
    return false;

  std::vector<std::string> params;
  params.push_back(path);
  params.emplace_back("return");
  CServiceBroker::GetGUI()->GetWindowManager().ActivateWindow(windowId, params);
  return true;
}
