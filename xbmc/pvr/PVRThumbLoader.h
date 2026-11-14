/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "ThumbLoader.h"

#include <string>

namespace PVR
{
class CPVRThumbLoader : public CThumbLoader
{
public:
  CPVRThumbLoader() = default;
  ~CPVRThumbLoader() override = default;

  bool LoadItem(CFileItem* item) override;
  bool LoadItemCached(CFileItem* item) override;
  bool LoadItemLookup(CFileItem* item) override;

  void ClearCachedImage(CFileItem& item);
  void ClearCachedImages(const CFileItemList& items);

protected:
  void OnLoaderFinish() override;

private:
  bool FillThumb(CFileItem& item);
  std::string GetChannelGroupThumbURL(const CFileItem& channelGroupItem) const;

  bool m_bInvalidated = false;
};

} // namespace PVR
