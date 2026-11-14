/*
 *  Copyright (C) 2005-2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "AppParamParserLinux.h"

class CAppParamParserWebOS : public CAppParamParserLinux
{
public:
  CAppParamParserWebOS() = default;
  ~CAppParamParserWebOS() = default;

protected:
  void ParseArg(const std::string& arg) override;

private:
  int m_nArgs{0};
};
