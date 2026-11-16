/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "pvr/dialogs/GUIDialogPVRItemsViewBase.h"

#include <memory>

namespace PVR
{
class CPVRChannel;

class CGUIDialogPVRChannelGuide : public CGUIDialogPVRItemsViewBase
{
public:
  CGUIDialogPVRChannelGuide();
  ~CGUIDialogPVRChannelGuide() override = default;

  void Open(const std::shared_ptr<const CPVRChannel>& channel);

protected:
  void OnInitWindow() override;
  void OnDeinitWindow(int nextWindowID) override;

private:
  std::shared_ptr<const CPVRChannel> m_channel;
};
} // namespace PVR
