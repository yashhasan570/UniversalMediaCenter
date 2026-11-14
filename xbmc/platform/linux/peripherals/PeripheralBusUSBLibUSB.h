/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "peripherals/bus/PeripheralBus.h"
#include "peripherals/devices/Peripheral.h"

struct usb_bus;

namespace PERIPHERALS
{
  class CPeripherals;

  class CPeripheralBusUSB : public CPeripheralBus
  {
  public:
    explicit CPeripheralBusUSB(CPeripherals& manager);

    /*!
     * @see PeripheralBus::PerformDeviceScan()
     */
    bool PerformDeviceScan(PeripheralScanResults &results);

  protected:
    static const PeripheralType GetType(int iDeviceClass);
    struct usb_bus *m_busses;
  };
}
