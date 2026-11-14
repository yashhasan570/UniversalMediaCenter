/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
/*!
 * \brief The playback client being controlled
 */
class IPlaybackCallback
{
public:
  virtual ~IPlaybackCallback() = default;

  /*!
   * \brief Set the playback speed
   *
   * \param speed The new speed
   */
  virtual void SetPlaybackSpeed(double speed) = 0;

  /*!
   * \brief Enable/disable game input
   *
   * \param bEnable True to enable input, false to disable input
   */
  virtual void EnableInput(bool bEnable) = 0;
};

/*!
 * \brief Class that can control playback and input
 */
class IPlaybackControl
{
public:
  virtual ~IPlaybackControl() = default;

  /*!
   * \brief Called every frame
   */
  virtual void FrameMove() = 0;
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
