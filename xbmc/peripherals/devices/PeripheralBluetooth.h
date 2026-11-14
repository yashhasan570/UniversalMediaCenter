/*
 *  Copyright (C) 2005-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Peripheral.h"

namespace PERIPHERALS
{
/*!
 * \ingroup peripherals
 */
class CPeripheralBluetooth : public CPeripheral
{
public:
  CPeripheralBluetooth(CPeripherals& manager,
                       const PeripheralScanResult& scanResult,
                       CPeripheralBus* bus);
  ~CPeripheralBluetooth(void) override = default;
};
} // namespace PERIPHERALS
