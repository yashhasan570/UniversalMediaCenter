/*
 *  Copyright (C) 2013-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

class StringValidation
{
public:
  typedef bool (*Validator)(const std::string &input, void *data);

  static bool NonEmpty(const std::string &input, void *data) { return !input.empty(); }
  static bool IsInteger(const std::string &input, void *data);
  static bool IsPositiveInteger(const std::string &input, void *data);
  static bool IsTime(const std::string &input, void *data);

private:
  StringValidation() = default;
};
