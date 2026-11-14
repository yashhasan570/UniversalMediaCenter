/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <cstdint>
#include <vector>

class CCaptionBlock
{
public:
  explicit CCaptionBlock(int size) : m_pts(0.0), m_data(size) {}
  double m_pts;
  std::vector<uint8_t> m_data;
};
