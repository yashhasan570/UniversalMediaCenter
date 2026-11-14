/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CFileItem;

namespace UNIVERSAL MEDIA CENTER::MUSIC
{

//! \brief Check whether an item is an audio item.
//! \details Note that this returns true for anything with a music info tag,
//!          so that may include eg. folders.
bool IsAudio(const CFileItem& item);

//! \brief Check whether an item is an audio book item.
bool IsAudioBook(const CFileItem& item);

//! \brief Check whether an item is an audio cd item.
bool IsCDDA(const CFileItem& item);

//! \brief Check whether an item is a cue sheet.
bool IsCUESheet(const CFileItem& item);

//! \brief Check whether an item is a lyrics file.
bool IsLyrics(const CFileItem& item);

//! \brief Check whether an item is a music database item.
bool IsMusicDb(const CFileItem& item);

} // namespace UNIVERSAL MEDIA CENTER::MUSIC
