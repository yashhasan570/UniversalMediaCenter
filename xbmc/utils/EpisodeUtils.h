/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/RegExp.h"
#include "video/Episode.h"

class CFileItem;

class CEpisodeUtils
{
public:
  static bool EnumerateEpisodeItem(const CFileItem* item,
                                   UNIVERSAL MEDIA CENTER::VIDEO::EPISODELIST& episodeList,
                                   UNIVERSAL MEDIA CENTER::REGEXP::RegExpCache* cache = nullptr);

  static std::string GetEpisodesLabel(const CFileItem& item);
};
