/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "ImusicInfoTagLoader.h"

class CFileItem;  // forward

namespace MUSIC_INFO
{
  class CMusicInfoTagLoaderFactory
  {
    public:
      CMusicInfoTagLoaderFactory(void);
      virtual ~CMusicInfoTagLoaderFactory();

      static IMusicInfoTagLoader* CreateLoader(const CFileItem& item);
  };
}

