/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "view/GUIViewState.h"

class CGUIViewStateWindowPictures : public CGUIViewState
{
public:
  explicit CGUIViewStateWindowPictures(const CFileItemList& items);

  std::optional<UNIVERSAL MEDIA CENTER::MEDIA::MediaSection> GetLockType() override;
  std::string GetExtensions() override;
  std::vector<CMediaSource>& GetSources() override;

protected:
  void SaveViewState() override;
};

