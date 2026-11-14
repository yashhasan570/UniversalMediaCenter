/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "games/addons/disc/GameClientDiscModel.h"

#include <cstdint>
#include <vector>

namespace KODI
{
namespace RETRO
{
class CDiscStateHistory
{
public:
  uint32_t Intern(const GAME::CGameClientDiscModel& model);
  const GAME::CGameClientDiscModel* Get(uint32_t id) const;
  void Clear();

private:
  std::vector<GAME::CGameClientDiscModel> m_states;
};
} // namespace RETRO
} // namespace KODI
