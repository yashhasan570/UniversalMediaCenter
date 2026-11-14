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

namespace UNIVERSAL MEDIA CENTER
{
namespace ADDONS
{
class CScreenSaver;
} // namespace ADDONS
} // namespace UNIVERSAL MEDIA CENTER

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
  std::unique_ptr<UNIVERSAL MEDIA CENTER::ADDONS::CScreenSaver> m_addon;
  bool m_visible{false};
};
