/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GameResource.h"

#include "addons/addoninfo/AddonType.h"

#include <utility>

using namespace ADDON;

CGameResource::CGameResource(const AddonInfoPtr& addonInfo)
  : CResource(addonInfo, AddonType::RESOURCE_GAMES)
{
}
