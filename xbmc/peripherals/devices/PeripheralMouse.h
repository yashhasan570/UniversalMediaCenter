/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Peripheral.h"
#include "XBDateTime.h"
#include "input/mouse/interfaces/IMouseDriverHandler.h"
#include "threads/CriticalSection.h"

#include <vector>

namespace PERIPHERALS
{
/*!
 * \ingroup peripherals
 */
class CPeripheralMouse : public CPeripheral, public UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler
{
public:
  CPeripheralMouse(CPeripherals& manager,
                   const PeripheralScanResult& scanResult,
                   CPeripheralBus* bus);

  ~CPeripheralMouse(void) override;

  // implementation of CPeripheral
  bool InitialiseFeature(const PeripheralFeature feature) override;
  void RegisterMouseDriverHandler(UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler* handler,
                                  bool bPromiscuous) override;
  void UnregisterMouseDriverHandler(UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler* handler) override;
  CDateTime LastActive() const override { return m_lastActive; }
  void SetLastActive(const CDateTime& lastActive) override;
  UNIVERSAL MEDIA CENTER::GAME::ControllerPtr ControllerProfile() const override;

  // implementation of IMouseDriverHandler
  bool OnPosition(int x, int y) override;
  bool OnButtonPress(UNIVERSAL MEDIA CENTER::MOUSE::BUTTON_ID button) override;
  void OnButtonRelease(UNIVERSAL MEDIA CENTER::MOUSE::BUTTON_ID button) override;

private:
  struct MouseHandle
  {
    UNIVERSAL MEDIA CENTER::MOUSE::IMouseDriverHandler* handler;
    bool bPromiscuous;
  };

  std::vector<MouseHandle> m_mouseHandlers;
  CCriticalSection m_mutex;
  CDateTime m_lastActive;
};
} // namespace PERIPHERALS
