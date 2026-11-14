/*
 *  Copyright (C) 2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

class CProcessInfo;
struct VideoPicture;

class IDVDVideoPP
{
public:
  virtual ~IDVDVideoPP() = default;

  virtual void SetType(const std::string& mType, bool deinterlace) = 0;
  virtual void Process(VideoPicture* picture) = 0;
};
