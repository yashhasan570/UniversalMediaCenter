/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/Resource.h"

#include <memory>

namespace ADDON
{

class CGameResource : public CResource
{
public:
  explicit CGameResource(const AddonInfoPtr& addonInfo);
  ~CGameResource() override = default;
};

}
