/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DVDSubtitleParser.h"
#include "SubtitlesAdapter.h"

#include <memory>

class CDVDSubtitleParserMicroDVD : public CDVDSubtitleParserText, private CSubtitlesAdapter
{
public:
  CDVDSubtitleParserMicroDVD(std::unique_ptr<CDVDSubtitleStream>&& stream,
                             const std::string& strFile);
  ~CDVDSubtitleParserMicroDVD() = default;

  bool Open(CDVDStreamInfo& hints) override;

private:
  double m_framerate;
};
