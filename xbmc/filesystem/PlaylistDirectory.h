/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "IDirectory.h"

namespace XFILE
{
  class CPlaylistDirectory : public IDirectory
  {
  public:
    CPlaylistDirectory(void);
    ~CPlaylistDirectory(void) override;
    bool GetDirectory(const CURL& url, CFileItemList &items) override;
    bool AllowAll() const override { return true; }
  };
}
