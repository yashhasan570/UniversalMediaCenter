/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GameClientStreamVideo.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{

/*!
 * \ingroup games
 */
class CGameClientStreamSwFramebuffer : public CGameClientStreamVideo
{
public:
  CGameClientStreamSwFramebuffer() = default;
  ~CGameClientStreamSwFramebuffer() override = default;

  // Implementation of IGameClientStream via CGameClientStreamVideo
  bool GetBuffer(unsigned int width, unsigned int height, game_stream_buffer& buffer) override;
};

} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
