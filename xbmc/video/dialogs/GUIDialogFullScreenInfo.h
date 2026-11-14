/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/GUIDialog.h"

class CGUIDialogFullScreenInfo :
      public CGUIDialog
{
public:
  CGUIDialogFullScreenInfo(void);
  ~CGUIDialogFullScreenInfo(void) override;
  bool OnAction(const CAction &action) override;
};

