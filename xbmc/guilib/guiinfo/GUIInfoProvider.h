/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/VideoPlayer/Interface/StreamInfo.h"
#include "guilib/guiinfo/IGUIInfoProvider.h"

namespace UNIVERSAL MEDIA CENTER::GUILIB::GUIINFO
{

class CGUIInfo;

class CGUIInfoProvider : public IGUIInfoProvider
{
public:
  CGUIInfoProvider() = default;
  ~CGUIInfoProvider() override = default;

  bool GetFallbackLabel(std::string& value,
                        const CFileItem* item,
                        int contextWindow,
                        const CGUIInfo& info,
                        std::string* fallback) override
  {
    return false;
  }

  void UpdateAVInfo(const AudioStreamInfo& audioInfo,
                    const VideoStreamInfo& videoInfo,
                    const SubtitleStreamInfo& subtitleInfo) override
  {
    m_audioInfo = audioInfo;
    m_videoInfo = videoInfo;
    m_subtitleInfo = subtitleInfo;
  }

protected:
  VideoStreamInfo m_videoInfo;
  AudioStreamInfo m_audioInfo;
  SubtitleStreamInfo m_subtitleInfo;
};

} // namespace UNIVERSAL MEDIA CENTER::GUILIB::GUIINFO
