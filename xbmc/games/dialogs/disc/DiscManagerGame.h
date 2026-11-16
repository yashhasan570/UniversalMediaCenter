/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "games/GameTypes.h"
#include "games/addons/disc/GameClientDiscModel.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CDiscManagerGame
{
public:
  CDiscManagerGame() = default;
  ~CDiscManagerGame() = default;

  // Lifecycle functions
  void Initialize(GameClientPtr gameClient);
  void Deinitialize();
  void NotifyDiscChange();
  void NotifyTrayChange();

  // Game interface
  bool IsEjected() const;
  void GetState(bool& ejected, std::string& selectedDisc) const;
  unsigned int GetSelectedIndex(std::optional<size_t> selectedIndex, bool allowSelectNoDisc) const;
  std::optional<std::string> GetDiscPathByIndex(std::optional<size_t> discIndex) const;

  // Static game interface
  static GameClientPtr GetGameClient();

private:
  // Game parameters
  GameClientPtr m_gameClient;
  std::optional<CGameClientDiscModel> m_pendingDiscModel;
  uint64_t m_pendingRestoreGeneration{0};
};
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
