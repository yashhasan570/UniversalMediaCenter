/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <cstring>
#include <stdint.h>

class CAEDeviceInfo;

class CAEELDParser {
public:
  static void Parse(const uint8_t *data, size_t length, CAEDeviceInfo& info);
};

