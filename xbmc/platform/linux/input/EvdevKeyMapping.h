/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/keyboard/_keysym.h"

#include <cstdint>
#include <optional>

class CEvdevKeyMapping
{
public:
  static std::optional<Key> KeyForEvdevCode(uint32_t code);
};
