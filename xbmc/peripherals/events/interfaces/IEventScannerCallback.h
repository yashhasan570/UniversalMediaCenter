/*
 *  Copyright (C) 2018-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace PERIPHERALS
{
/*!
 * \ingroup peripherals
 */
class IEventScannerCallback
{
public:
  virtual ~IEventScannerCallback(void) = default;

  virtual void ProcessEvents(void) = 0;
};
} // namespace PERIPHERALS
