/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER::MEDIA
{

//! \brief The kinds of stream a piece of media carries.
enum class Streams
{
  Audio,
  Video,
  VideoAndAudio
};

constexpr bool HasVideo(Streams streams)
{
  return streams != Streams::Audio;
}

constexpr bool HasAudio(Streams streams)
{
  return streams != Streams::Video;
}

} // namespace UNIVERSAL MEDIA CENTER::MEDIA
