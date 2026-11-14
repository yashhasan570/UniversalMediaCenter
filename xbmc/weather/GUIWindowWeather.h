/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/GUIWindow.h"

#include <vector>

class CGUIWindowWeather : public CGUIWindow
{
public:
  CGUIWindowWeather();
  ~CGUIWindowWeather() override;
  bool OnMessage(CGUIMessage& message) override;
  void FrameMove() override;

protected:
  void OnInitWindow() override;

  void UpdateButtons();
  void UpdateLocations();
  void SetProps();
  void ClearProps();
  void RefreshImages();
  void SetLocation(int loc);

private:
  unsigned int m_maxLocation{0};
  const std::vector<std::string> m_windowProps;
};
