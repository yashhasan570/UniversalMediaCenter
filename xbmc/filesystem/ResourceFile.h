/*
 *  Copyright (C) 2014-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "filesystem/OverrideFile.h"

namespace XFILE
{
class CResourceFile : public COverrideFile
{
public:
  CResourceFile();
  ~CResourceFile() override;

  static bool TranslatePath(const std::string &path, std::string &translatedPath);
  static bool TranslatePath(const CURL &url, std::string &translatedPath);

protected:
  std::string TranslatePath(const CURL &url) override;
};
}
