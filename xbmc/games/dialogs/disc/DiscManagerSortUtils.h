/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <optional>
#include <string>
#include <utility>

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
/*!
 * \brief Extract a normalized stem plus disc number for conservative display-only sorting
 */
std::optional<std::pair<std::string, int>> GetNormalizedStemAndTrailingNumber(
    const std::string& label);
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
