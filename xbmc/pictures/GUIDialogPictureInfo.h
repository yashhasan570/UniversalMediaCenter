/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/GUIDialog.h"

#include <memory>

class CFileItemList;

class CGUIDialogPictureInfo :
      public CGUIDialog
{
public:
  CGUIDialogPictureInfo(void);
  ~CGUIDialogPictureInfo(void) = default;
  void SetPicture(CFileItem *item);
  void FrameMove() override;

protected:
  void OnInitWindow() override;
  void OnDeinitWindow(int nextWindowID) override;
  bool OnAction(const CAction& action) override;
  void UpdatePictureInfo();

  std::unique_ptr<CFileItemList> m_pictureInfo;
  std::string    m_currentPicture;
};
