/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "DirectoryNodeRoot.h"

using namespace XFILE::MUSICDATABASEDIRECTORY;

CDirectoryNodeRoot::CDirectoryNodeRoot(const std::string& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NodeType::ROOT, strName, pParent)
{

}

NodeType CDirectoryNodeRoot::GetChildType() const
{
  return NodeType::OVERVIEW;
}
