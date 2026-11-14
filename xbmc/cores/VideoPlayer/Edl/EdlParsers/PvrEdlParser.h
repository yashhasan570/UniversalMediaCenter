/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/VideoPlayer/Edl/EdlParser.h"

#include <chrono>

namespace EDL
{

/*!
 * @brief Parser for PVR EDL data
 *
 * Retrieves edit decision list data from PVR recordings and EPG items.
 * This parser implements IEdlParser directly (not CEdlFileParserBase)
 * as it doesn't read from files.
 */
class CPvrEdlParser : public IEdlParser
{
public:
  bool CanParse(const CFileItem& item) const override;
  CEdlParserResult Parse(const CFileItem& item,
                         float fps,
                         std::chrono::milliseconds duration) override;
};

} // namespace EDL
