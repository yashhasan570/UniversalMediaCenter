/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/joysticks/interfaces/IButtonMapCallback.h"
#include "input/joysticks/interfaces/IDriverHandler.h"
#include "input/keyboard/interfaces/IKeyboardDriverHandler.h"
#include "input/mouse/interfaces/IMouseDriverHandler.h"

#include <memory>

namespace UNIVERSAL MEDIA CENTER
{
namespace JOYSTICK
{
class CButtonMapping;
class IButtonMap;
class IButtonMapper;
} // namespace JOYSTICK
} // namespace UNIVERSAL MEDIA CENTER

namespace PERIPHERALS
{
class CPeripheral;
class CPeripherals;

/*!
* \ingroup peripherals
*/
class CAddonButtonMapping : public UNIVERSAL MEDIA CENTER::JOYSTICK::IDriverHandler,
                            public UNIVERSAL MEDIA CENTER::KEYBOARD::IKeyboardDriverHandler,
                            public UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler,
                            public UNIVERSAL MEDIA CENTER::JOYSTICK::IButtonMapCallback
{
public:
  CAddonButtonMapping(CPeripherals& manager,
                      CPeripheral* peripheral,
                      UNIVERSAL MEDIA CENTER::JOYSTICK::IButtonMapper* mapper);

  ~CAddonButtonMapping(void) override;

  // implementation of IDriverHandler
  bool OnButtonMotion(unsigned int buttonIndex, bool bPressed) override;
  bool OnHatMotion(unsigned int hatIndex, UNIVERSAL MEDIA CENTER::JOYSTICK::HAT_STATE state) override;
  bool OnAxisMotion(unsigned int axisIndex,
                    float position,
                    int center,
                    unsigned int range) override;
  void OnInputFrame(void) override;

  // implementation of IKeyboardDriverHandler
  bool OnKeyPress(const CKey& key) override;
  void OnKeyRelease(const CKey& key) override;

  // implementation of IMouseDriverHandler
  bool OnPosition(int x, int y) override;
  bool OnButtonPress(UNIVERSAL MEDIA CENTER::MOUSE::BUTTON_ID button) override;
  void OnButtonRelease(UNIVERSAL MEDIA CENTER::MOUSE::BUTTON_ID button) override;

  // implementation of IButtonMapCallback
  void SaveButtonMap() override;
  void ResetIgnoredPrimitives() override;
  void RevertButtonMap() override;

private:
  std::unique_ptr<UNIVERSAL MEDIA CENTER::JOYSTICK::CButtonMapping> m_buttonMapping;
  std::unique_ptr<UNIVERSAL MEDIA CENTER::JOYSTICK::IButtonMap> m_buttonMap;
};
} // namespace PERIPHERALS
