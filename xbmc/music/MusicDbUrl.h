/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DbUrl.h"

#include <string>

class CVariant;

class CMusicDbUrl : public CDbUrl
{
public:
  CMusicDbUrl();
  ~CMusicDbUrl() override;

protected:
  bool parse() override;
  bool validateOption(const std::string &key, const CVariant &value) override;
};
