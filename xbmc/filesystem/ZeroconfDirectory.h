/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "IDirectory.h"
//txt-records as of http://www.dns-sd.org/ServiceTypes.html
#define TXT_RECORD_PATH_KEY     "path"
#define TXT_RECORD_USERNAME_KEY "u"
#define TXT_RECORD_PASSWORD_KEY "p"

namespace XFILE
{
  class CZeroconfDirectory : public IDirectory
  {
    public:
      CZeroconfDirectory(void);
      ~CZeroconfDirectory(void) override;
      bool GetDirectory(const CURL& url, CFileItemList &items) override;
      CacheType GetCacheType(const CURL& url) const override { return CacheType::NEVER; }
  };
}

