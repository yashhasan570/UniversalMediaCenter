/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/binary-addons/AddonInstanceHandler.h"
#include "addons/kodi-dev-kit/include/kodi/addon-instance/Screensaver.h"

namespace KODI::ADDONS
{

class CScreenSaver : public ADDON::IAddonInstanceHandler
{
public:
  explicit CScreenSaver(const ADDON::AddonInfoPtr& addonInfo);
  ~CScreenSaver() override;

  bool Start();
  void Stop();
  void Render();

  // Addon callback functions
  void GetProperties(struct KODI_ADDON_SCREENSAVER_PROPS* props) const;
};

} // namespace KODI::ADDONS
