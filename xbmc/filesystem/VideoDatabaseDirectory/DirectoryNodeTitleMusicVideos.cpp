/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "DirectoryNodeTitleMusicVideos.h"

#include "FileItem.h"
#include "FileItemList.h"
#include "QueryParams.h"
#include "utils/ItemProperties.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeTitleMusicVideos::CDirectoryNodeTitleMusicVideos(const std::string& strName,
                                                               CDirectoryNode* pParent)
  : CDirectoryNode(NodeType::TITLE_MUSICVIDEOS, strName, pParent)
{

}

bool CDirectoryNodeTitleMusicVideos::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  const int details =
      items.GetProperty(UNIVERSAL MEDIA CENTER::ITEM::PROPERTY::SET_VIDEODB_DETAILS).asInteger32(VideoDbDetailsNone);
  bool bSuccess = videodatabase.GetMusicVideosNav(
      BuildPath(), items, params.GetGenreId(), params.GetYear(), params.GetActorId(),
      params.GetDirectorId(), params.GetStudioId(), params.GetAlbumId(), params.GetTagId(),
      SortDescription(), details);

  videodatabase.Close();

  return bSuccess;
}
