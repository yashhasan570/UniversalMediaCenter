/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "filesystem/OverrideFile.h"

namespace XFILE
{
class CSpecialProtocolFile : public COverrideFile
{
public:
  CSpecialProtocolFile(void);
  ~CSpecialProtocolFile(void) override;

protected:
  std::string TranslatePath(const CURL& url) override;
};
}
