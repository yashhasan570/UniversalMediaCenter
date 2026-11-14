/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DVDOverlayCodec.h"
#include "DVDStreamInfo.h"
#include "DVDSubtitles/SubtitlesAdapter.h"

extern "C"
{
#include <libavcodec/avcodec.h>
}

class CDVDOverlay;

class CDVDOverlayCodecText : public CDVDOverlayCodec, private CSubtitlesAdapter
{
public:
  CDVDOverlayCodecText();
  ~CDVDOverlayCodecText() override = default;
  bool Open(CDVDStreamInfo& hints, CDVDCodecOptions& options) override;
  OverlayMessage Decode(DemuxPacket* pPacket) override;
  void Reset() override;
  void Flush() override;
  std::shared_ptr<CDVDOverlay> GetOverlay() override;

  // Specialization of CSubtitlesAdapter
  void PostProcess(std::string& text) override;

private:
  std::shared_ptr<CDVDOverlay> m_pOverlay;
  CDVDStreamInfo m_hints;
  int m_prevSubId{-1};
  bool m_changePrevStopTime{false};
  AVCodecID m_codecId{AV_CODEC_ID_NONE};
};
