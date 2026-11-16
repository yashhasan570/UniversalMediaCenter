/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "CheatUtils.h"

#include "utils/URIUtils.h"

using namespace UNIVERSAL MEDIA CENTER::GAME;

std::string CCheatUtils::GetCheatFileName(const std::string& gamePath)
{
  return URIUtils::GetFileName(URIUtils::ReplaceExtension(gamePath, ".cht"));
}
