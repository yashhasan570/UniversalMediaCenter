/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "PlayListRAM.h"

#include "FileItem.h"
#include "PlayListFactory.h"
#include "filesystem/File.h"
#include "utils/log.h"

#include <iostream>
#include <string>

namespace UNIVERSAL MEDIA CENTER::PLAYLIST
{

bool CPlayListRAM::LoadData(std::istream& stream)
{
  CLog::Log(LOGINFO, "Parsing RAM");

  std::string strMMS;
  while (stream.peek() != '\n' && stream.peek() != '\r')
    strMMS += stream.get();

  CLog::Log(LOGINFO, "Adding element {}", strMMS);
  CFileItemPtr newItem(new CFileItem(strMMS));
  newItem->SetPath(strMMS);
  Add(newItem);
  return true;
}
} // namespace UNIVERSAL MEDIA CENTER::PLAYLIST
