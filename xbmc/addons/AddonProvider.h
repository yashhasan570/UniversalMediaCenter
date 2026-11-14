/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/AddonBase.h"

#include <memory>

/*
 * Interface to retrieve sub-addons from already active addons
 * See Inputstream.cpp/h for an explaric use case
 */

namespace ADDON
{
class CAddonInfo;
using AddonInfoPtr = std::shared_ptr<CAddonInfo>;

class IAddonProvider
{
public:
  virtual ~IAddonProvider() = default;
  enum class InstanceType
  {
    INPUTSTREAM,
    VIDEOCODEC
  };
  virtual void GetAddonInstance(InstanceType instance_type,
                                ADDON::AddonInfoPtr& addonInfo,
                                UNIVERSALMEDIA_HANDLE& parentInstance) = 0;
};

} // namespace ADDON
