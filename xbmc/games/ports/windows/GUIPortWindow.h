/*
 *  Copyright (C) 2021 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "games/GameTypes.h"
#include "guilib/GUIDialog.h"

#include <memory>

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
class IPortList;

/*!
 * \ingroup games
 */
class CGUIPortWindow : public CGUIDialog
{
public:
  CGUIPortWindow();
  ~CGUIPortWindow() override;

  // Implementation of CGUIControl via CGUIDialog
  bool OnMessage(CGUIMessage& message) override;

protected:
  // Implementation of CGUIWindow via CGUIDialog
  void OnWindowLoaded() override;
  void OnWindowUnload() override;
  void OnInitWindow() override;
  void OnDeinitWindow(int nextWindowID) override;
  void FrameMove() override;

private:
  // Actions for port list
  void UpdatePortList();
  void FocusPortList();
  bool OnClickAction();

  // Actions for the available buttons
  void ResetPorts();
  void CloseDialog();

  // GUI parameters
  std::unique_ptr<IPortList> m_portList;

  // Game parameters
  GameClientPtr m_gameClient;
};
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
