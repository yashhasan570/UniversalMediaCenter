/*
 *  Copyright (C) 2005-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CFileItem;

namespace KODI::PLAYLIST
{

//! \brief Check whether an item is a playlist.
bool IsPlayList(const CFileItem& item);

//! \brief Check whether an item is a smart playlist.
bool IsSmartPlayList(const CFileItem& item);

} // namespace KODI::PLAYLIST
