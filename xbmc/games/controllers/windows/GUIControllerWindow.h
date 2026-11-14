/*
 *  Copyright (C) 2014-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/RepositoryUpdater.h"
#include "games/GameTypes.h"
#include "guilib/GUIDialog.h"

#include <memory>

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
class CControllerInstaller;
class IControllerList;
class IFeatureList;

/*!
 * \ingroup games
 */
class CGUIControllerWindow : public CGUIDialog
{
public:
  CGUIControllerWindow(void);
  ~CGUIControllerWindow() override;

  // implementation of CGUIControl via CGUIDialog
  void DoProcess(unsigned int currentTime, CDirtyRegionList& dirtyregions) override;
  bool OnMessage(CGUIMessage& message) override;

protected:
  // implementation of CGUIWindow via CGUIDialog
  void OnInitWindow() override;
  void OnDeinitWindow(int nextWindowID) override;

private:
  void OnControllerFocused(unsigned int controllerIndex);
  void OnControllerSelected(unsigned int controllerIndex);
  void OnFeatureFocused(unsigned int featureIndex);
  void OnFeatureSelected(unsigned int featureIndex);
  void UpdateButtons(void);

  // Action for the available button
  void GetMoreControllers(void);
  void GetAllControllers();
  void ResetController(void);
  void ShowHelp(void);
  void ShowButtonCaptureDialog(void);

  IControllerList* m_controllerList = nullptr;
  IFeatureList* m_featureList = nullptr;

  // Game parameters
  GameClientPtr m_gameClient;
  std::string m_controllerId;

  // Controller parameters
  std::unique_ptr<CControllerInstaller> m_installer;
};
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
