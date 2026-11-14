/*
 *  Copyright (C) 2005-2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "AppParams.h"

#include "FileItemList.h"

CAppParams::CAppParams() : m_playlist(std::make_unique<CFileItemList>())
{
}

CAppParams::~CAppParams() = default;

void CAppParams::SetRawArgs(std::vector<std::string> args)
{
  m_rawArgs = std::move(args);
}
