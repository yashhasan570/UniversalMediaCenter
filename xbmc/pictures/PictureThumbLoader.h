/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "ThumbLoader.h"

class CPictureThumbLoader : public CThumbLoader
{
public:
  CPictureThumbLoader();
  ~CPictureThumbLoader() override;

  bool LoadItem(CFileItem* pItem) override;
  bool LoadItemCached(CFileItem* pItem) override;
  bool LoadItemLookup(CFileItem* pItem) override;
  void SetRegenerateThumbs(bool regenerate) { m_regenerateThumbs = regenerate; }
  static void ProcessFoldersAndArchives(CFileItem *pItem);

protected:
  void OnLoaderFinish() override;

private:
  bool m_regenerateThumbs;
};
