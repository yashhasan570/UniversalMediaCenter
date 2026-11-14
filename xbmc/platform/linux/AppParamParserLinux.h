/*
 *  Copyright (C) 2005-2021 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "application/AppParamParser.h"

class CAppParamParserLinux : public CAppParamParser
{
public:
  CAppParamParserLinux();
  ~CAppParamParserLinux();

protected:
  void ParseArg(const std::string& arg) override;
  void DisplayHelp() override;
};
