/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GUIDialogYesNo.h"

class CGUIDialogPlayEject : public CGUIDialogYesNo
{
public:
  CGUIDialogPlayEject();
  ~CGUIDialogPlayEject() override;
  bool OnMessage(CGUIMessage& message) override;
  void FrameMove() override;

  static bool ShowAndGetInput(const std::string& strLine1,
                              const std::string& strLine2,
                              unsigned int uiAutoCloseTime = 0);

protected:
  void OnInitWindow() override;
};
