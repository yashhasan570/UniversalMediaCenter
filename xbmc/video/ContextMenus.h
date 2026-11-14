/*
 *  Copyright (C) 2016-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "ContextMenuItem.h"
#include "VideoLibraryQueue.h"
#include "media/MediaType.h"

#include <memory>

namespace CONTEXTMENU
{

class CVideoInfoBase : public CStaticContextMenuAction
{
public:
  explicit CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE mediaType);
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;

private:
  const UNIVERSAL MEDIA CENTER::MEDIA::TYPE m_mediaType;
};

struct CVideoInfo : CVideoInfoBase
{
  CVideoInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO) {}
  bool IsVisible(const CFileItem& item) const override;
};

struct CTVShowInfo : CVideoInfoBase
{
  CTVShowInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW) {}
};

struct CSeasonInfo : CVideoInfoBase
{
  CSeasonInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SEASON) {}
};

struct CEpisodeInfo : CVideoInfoBase
{
  CEpisodeInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::EPISODE) {}
};

struct CMusicVideoInfo : CVideoInfoBase
{
  CMusicVideoInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC_VIDEO) {}
};

struct CMovieInfo : CVideoInfoBase
{
  CMovieInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE) {}
};

struct CMovieSetInfo : CVideoInfoBase
{
  CMovieSetInfo() : CVideoInfoBase(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION) {}
};

struct CVideoRemoveResumePoint : CStaticContextMenuAction
{
  CVideoRemoveResumePoint() : CStaticContextMenuAction(38209) {}
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoMarkWatched : CStaticContextMenuAction
{
  CVideoMarkWatched() : CStaticContextMenuAction(16103) {}
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoMarkUnWatched : CStaticContextMenuAction
{
  CVideoMarkUnWatched() : CStaticContextMenuAction(16104) {}
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoBrowse : CStaticContextMenuAction
{
  CVideoBrowse() : CStaticContextMenuAction(37015) {} // Browse into
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoResume : IContextMenuItem
{
  std::string GetLabel(const CFileItem& item) const override;
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& _item) const override;
};

struct CVideoPlay : IContextMenuItem
{
  std::string GetLabel(const CFileItem& item) const override;
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& _item) const override;
};

struct CVideoPlayUsing : CStaticContextMenuAction
{
  CVideoPlayUsing() : CStaticContextMenuAction(15213) {} // Play using...
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& _item) const override;
};

struct CVideoPlayStackPart : CStaticContextMenuAction
{
  CVideoPlayStackPart() : CStaticContextMenuAction(20324) {} // Play part
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& _item) const override;
};

struct CVideoQueue : CStaticContextMenuAction
{
  CVideoQueue() : CStaticContextMenuAction(13347) {} // Queue item
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoPlayNext : CStaticContextMenuAction
{
  CVideoPlayNext() : CStaticContextMenuAction(10008) {} // Play next
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoPlayAndQueue : IContextMenuItem
{
  std::string GetLabel(const CFileItem& item) const override;
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CTVShowScanForNewContent : CStaticContextMenuAction
{
  CTVShowScanForNewContent() : CStaticContextMenuAction(13349) {} // Scan for new content
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

struct CVideoShowExtras : CStaticContextMenuAction
{
  CVideoShowExtras() : CStaticContextMenuAction(40211) {} // Extras
  bool IsVisible(const CFileItem& item) const override;
  bool Execute(const std::shared_ptr<CFileItem>& item) const override;
};

} // namespace CONTEXTMENU
