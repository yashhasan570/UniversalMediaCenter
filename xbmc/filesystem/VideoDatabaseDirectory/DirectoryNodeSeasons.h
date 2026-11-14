/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DirectoryNode.h"

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CDirectoryNodeSeasons : public CDirectoryNode
    {
    public:
      CDirectoryNodeSeasons(const std::string& strName, CDirectoryNode* pParent);

    protected:
      NodeType GetChildType() const override;
      bool GetContent(CFileItemList& items) const override;
      std::string GetLocalizedName() const override;

    private:
      /*!
       * \brief Get the title of chosen season.
       * \return The season title.
       */
      std::string GetSeasonTitle() const;
    };
  }
}


