/*
 *  Copyright (C) 2015-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "view/GUIViewState.h"

class CGUIViewStateEventLog : public CGUIViewState
{
public:
  explicit CGUIViewStateEventLog(const CFileItemList& items);
  ~CGUIViewStateEventLog() override = default;

  // specializations of CGUIViewState
  bool HideExtensions() override { return true; }
  bool HideParentDirItems() override { return true; }
  bool DisableAddSourceButtons() override { return true; }

protected:
  // specializations of CGUIViewState
  void SaveViewState() override;
  std::string GetExtensions() override;
};

