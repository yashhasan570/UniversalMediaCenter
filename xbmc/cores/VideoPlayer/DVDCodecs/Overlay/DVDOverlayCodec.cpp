/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */
#include "DVDOverlayCodec.h"

#include "cores/VideoPlayer/Interface/DemuxPacket.h"
#include "cores/VideoPlayer/Interface/TimingConstants.h"


void CDVDOverlayCodec::GetAbsoluteTimes(double& starttime, double& stoptime, DemuxPacket* pkt)
{
  if (!pkt)
    return;

  double duration = 0.0;
  double pts = starttime;

  // we assume pts from packet is better than what
  // decoder gives us, only take duration
  // from decoder if available
  if (stoptime > starttime)
    duration = stoptime - starttime;
  else if (pkt->duration != DVD_NOPTS_VALUE)
    duration = pkt->duration;

  if (pkt->pts != DVD_NOPTS_VALUE)
    pts = pkt->pts;
  else if (pkt->dts != DVD_NOPTS_VALUE)
    pts = pkt->dts;

  starttime = pts;
  if (duration > 0)
    stoptime = pts + duration;
  else
    stoptime = 0;
}
