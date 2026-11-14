/*
 *  Copyright (C) 2011-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

class Base64
{
public:
  static void Encode(const char* input, unsigned int length, std::string &output);
  static std::string Encode(const char* input, unsigned int length);
  static void Encode(const std::string &input, std::string &output);
  static std::string Encode(const std::string &input);
  static void Decode(const char* input, unsigned int length, std::string &output);
  static std::string Decode(const char* input, unsigned int length);
  static void Decode(const std::string &input, std::string &output);
  static std::string Decode(const std::string &input);

private:
  static const std::string m_characters;
};
