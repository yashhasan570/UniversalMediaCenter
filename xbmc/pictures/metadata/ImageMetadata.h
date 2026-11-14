/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Exif.h"
#include "Iptc.h"

struct ImageMetadata
{
  int height{};
  int width{};
  bool isColor{};
  std::string encodingProcess{};
  std::string fileComment{};

  ExifInfo exifInfo;
  IPTCInfo iptcInfo;
};
