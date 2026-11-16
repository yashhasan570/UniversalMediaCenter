/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DirectoryNode.h"

namespace XFILE
{
  namespace MUSICDATABASEDIRECTORY
  {
    class CDirectoryNodeSongTop100 : public CDirectoryNode
    {
    public:
      CDirectoryNodeSongTop100(const std::string& strName, CDirectoryNode* pParent);
    protected:
      bool GetContent(CFileItemList& items) const override;
    };
  }
}


