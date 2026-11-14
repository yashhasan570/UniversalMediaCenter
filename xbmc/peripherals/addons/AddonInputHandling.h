/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "input/joysticks/interfaces/IDriverHandler.h"
#include "input/joysticks/interfaces/IInputReceiver.h"
#include "input/keyboard/interfaces/IKeyboardDriverHandler.h"
#include "input/mouse/interfaces/IMouseDriverHandler.h"

#include <memory>

namespace UNIVERSAL MEDIA CENTER
{
namespace JOYSTICK
{
class IButtonMap;
class IDriverReceiver;
class IInputHandler;
} // namespace JOYSTICK

namespace KEYBOARD
{
class IKeyboardInputHandler;
}

namespace MOUSE
{
class IMouseInputHandler;
}
} // namespace UNIVERSAL MEDIA CENTER

namespace PERIPHERALS
{
class CPeripheral;
class CPeripherals;
class CPeripheralAddon;

/*!
* \ingroup peripherals
*/
class CAddonInputHandling : public UNIVERSAL MEDIA CENTER::JOYSTICK::IDriverHandler,
                            public UNIVERSAL MEDIA CENTER::JOYSTICK::IInputReceiver,
                            public UNIVERSAL MEDIA CENTER::KEYBOARD::IKeyboardDriverHandler,
                            public UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler
{
public:
  CAddonInputHandling(CPeripherals& manager,
                      CPeripheral* peripheral,
                      std::shared_ptr<CPeripheralAddon> addon,
                      UNIVERSAL MEDIA CENTER::JOYSTICK::IInputHandler* handler,
                      UNIVERSAL MEDIA CENTER::JOYSTICK::IDriverReceiver* receiver);

  CAddonInputHandling(CPeripherals& manager,
                      CPeripheral* peripheral,
                      std::shared_ptr<CPeripheralAddon> addon,
                      UNIVERSAL MEDIA CENTER::KEYBOARD::IKeyboardInputHandler* handler);

  CAddonInputHandling(CPeripherals& manager,
                      CPeripheral* peripheral,
                      std::shared_ptr<CPeripheralAddon> addon,
                      UNIVERSAL MEDIA CENTER::MOUSE::IMouseInputHandler* handler);

  ~CAddonInputHandling(void) override;

  bool Load();

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

  // implementation of IInputReceiver
  bool SetRumbleState(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature, float magnitude) override;

private:
  // Construction parameters
  CPeripherals& m_manager;
  CPeripheral* const m_peripheral;
  const std::shared_ptr<CPeripheralAddon> m_addon;
  UNIVERSAL MEDIA CENTER::JOYSTICK::IInputHandler* const m_joystickInputHandler{nullptr};
  UNIVERSAL MEDIA CENTER::JOYSTICK::IDriverReceiver* const m_joystickDriverReceiver{nullptr};
  UNIVERSAL MEDIA CENTER::KEYBOARD::IKeyboardInputHandler* m_keyboardInputHandler{nullptr};
  UNIVERSAL MEDIA CENTER::MOUSE::IMouseInputHandler* const m_mouseInputHandler{nullptr};

  // Input parameters
  std::unique_ptr<UNIVERSAL MEDIA CENTER::JOYSTICK::IDriverHandler> m_joystickDriverHandler;
  std::unique_ptr<UNIVERSAL MEDIA CENTER::JOYSTICK::IInputReceiver> m_joystickInputReceiver;
  std::unique_ptr<UNIVERSAL MEDIA CENTER::KEYBOARD::IKeyboardDriverHandler> m_keyboardDriverHandler;
  std::unique_ptr<UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler> m_mouseDriverHandler;
  std::unique_ptr<UNIVERSAL MEDIA CENTER::JOYSTICK::IButtonMap> m_buttonMap;
};
} // namespace PERIPHERALS
