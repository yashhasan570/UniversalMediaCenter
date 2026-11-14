/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

namespace KODI
{
namespace GAME
{

class CGameClientDiscModel;

class CGameClientDiscM3U
{
public:
  /*!
   * \brief Load disc entries from an existing playlist file path
   */
  static bool Load(const std::string& m3uPath, CGameClientDiscModel& model);
};

} // namespace GAME
} // namespace KODI
