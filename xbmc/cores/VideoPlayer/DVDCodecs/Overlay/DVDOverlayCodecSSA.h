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
#include "DVDSubtitles/DVDSubtitlesLibass.h"

class CDVDOverlaySSA;

class CDVDOverlayCodecSSA : public CDVDOverlayCodec
{
public:
  CDVDOverlayCodecSSA();
  ~CDVDOverlayCodecSSA() override = default;
  bool Open(CDVDStreamInfo& hints, CDVDCodecOptions& options) override;
  OverlayMessage Decode(DemuxPacket* pPacket) override;
  void Reset() override;
  void Flush() override;
  std::shared_ptr<CDVDOverlay> GetOverlay() override;

private:
  std::shared_ptr<CDVDSubtitlesLibass> m_libass;
  std::shared_ptr<CDVDOverlaySSA> m_pOverlay;
  int m_order;
};
