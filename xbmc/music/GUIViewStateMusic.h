/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/SortUtils.h"
#include "view/GUIViewState.h"

class CSettings;

class CGUIViewStateWindowMusic : public CGUIViewState
{
public:
  explicit CGUIViewStateWindowMusic(const CFileItemList& items) : CGUIViewState(items) {}
protected:
  std::vector<CMediaSource>& GetSources() override;
  UNIVERSAL MEDIA CENTER::PLAYLIST::Id GetPlaylist() const override;
  bool AutoPlayNextItem() override;
  std::optional<UNIVERSAL MEDIA CENTER::MEDIA::MediaSection> GetLockType() override;
  std::string GetExtensions() override;

  //! \brief Add the sort methods of a list of albums labelled with \p albumFormat.
  void AddAlbumSortMethods(const std::string& albumFormat,
                           SortAttribute sortAttribute,
                           const CSettings& settings);
};

class CGUIViewStateMusicSearch : public CGUIViewStateWindowMusic
{
public:
  explicit CGUIViewStateMusicSearch(const CFileItemList& items);

protected:
  void SaveViewState() override;
};

class CGUIViewStateMusicDatabase : public CGUIViewStateWindowMusic
{
public:
  explicit CGUIViewStateMusicDatabase(const CFileItemList& items);

protected:
  void SaveViewState() override;
};

class CGUIViewStateMusicSmartPlaylist : public CGUIViewStateWindowMusic
{
public:
  explicit CGUIViewStateMusicSmartPlaylist(const CFileItemList& items);

protected:
  void SaveViewState() override;
};

class CGUIViewStateMusicPlaylist : public CGUIViewStateWindowMusic
{
public:
  explicit CGUIViewStateMusicPlaylist(const CFileItemList& items);

protected:
  void SaveViewState() override;
};

class CGUIViewStateWindowMusicNav : public CGUIViewStateWindowMusic
{
public:
  explicit CGUIViewStateWindowMusicNav(const CFileItemList& items);

protected:
  void SaveViewState() override;
  std::vector<CMediaSource>& GetSources() override;
};

class CGUIViewStateWindowMusicPlaylist : public CGUIViewStateWindowMusic
{
public:
  explicit CGUIViewStateWindowMusicPlaylist(const CFileItemList& items);

protected:
  void SaveViewState() override;
  UNIVERSAL MEDIA CENTER::PLAYLIST::Id GetPlaylist() const override;
  bool AutoPlayNextItem() override;
  bool HideParentDirItems() override;
  std::vector<CMediaSource>& GetSources() override;
};
