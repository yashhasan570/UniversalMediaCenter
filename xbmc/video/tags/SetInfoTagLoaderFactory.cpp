/*
 *  Copyright (C) 2024-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "SetInfoTagLoaderFactory.h"

#include "SetTagLoaderNFO.h"

using namespace UNIVERSAL MEDIA CENTER::VIDEO;

std::unique_ptr<ISetInfoTagLoader> CSetInfoTagLoaderFactory::CreateLoader(const std::string& title)
{
  auto nfo{std::make_unique<CSetTagLoaderNFO>(title)};
  if (nfo->HasInfo())
    return nfo;

  return nullptr;
}
