/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/GUIDialog.h"

#include <memory>

namespace KODI
{
namespace ADDONS
{
class CScreenSaver;
} // namespace ADDONS
} // namespace KODI

class CGUIWindowScreensaver : public CGUIDialog
{
public:
  CGUIWindowScreensaver();

  bool OnMessage(CGUIMessage& message) override;
  bool OnAction(const CAction& action) override
  {
    // We're just a screen saver, nothing to do here
    return false;
  }
  void Render() override;
  void Process(unsigned int currentTime, CDirtyRegionList& regions) override;

protected:
  void UpdateVisibility() override;
  void OnInitWindow() override;

private:
  std::unique_ptr<KODI::ADDONS::CScreenSaver> m_addon;
  bool m_visible{false};
};
