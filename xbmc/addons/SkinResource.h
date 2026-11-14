/*
 *  Copyright (C) 2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/Resource.h"

namespace ADDON
{

class CSkinResource : public CResource
{
public:
  explicit CSkinResource(const AddonInfoPtr& addonInfo);

protected:
  Published PublishedFiles() const override;
};

} // namespace ADDON
