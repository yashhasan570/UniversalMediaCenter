/*
 *  Copyright (C) 2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace KODI::PLAYLIST
{

enum class Id : int
{
  TYPE_NONE = -1,
  TYPE_MUSIC = 0,
  TYPE_VIDEO = 1,
  TYPE_PICTURE = 2,
  TYPE_GAME = 3
};

/*!
 * \brief Manages playlist playing.
 */
enum class RepeatState
{
  NONE,
  ONE,
  ALL
};

enum class ExcludeUsedPlaylists : bool
{
  DONT_EXCLUDE_USED_PLAYLISTS,
  EXCLUDE_USED_PLAYLISTS
};

} // namespace KODI::PLAYLIST
