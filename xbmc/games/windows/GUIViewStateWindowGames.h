/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "view/GUIViewState.h"

namespace KODI
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CGUIViewStateWindowGames : public CGUIViewState
{
public:
  explicit CGUIViewStateWindowGames(const CFileItemList& items);

  ~CGUIViewStateWindowGames() override = default;

  // implementation of CGUIViewState
  std::optional<KODI::MEDIA::MediaSection> GetLockType() override;
  std::string GetExtensions() override;
  std::vector<CMediaSource>& GetSources() override;

protected:
  // implementation of CGUIViewState
  void SaveViewState() override;
};
} // namespace GAME
} // namespace KODI
