/*
 *  Copyright (C) 2015-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/Variant.h"

#include <string>

class CJSONVariantParser
{
public:
  CJSONVariantParser() = delete;

  static bool Parse(const char* json, CVariant& data);
  static bool Parse(const std::string& json, CVariant& data);
};
