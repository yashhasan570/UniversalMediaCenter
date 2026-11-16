/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "WasmWebApis.h"

namespace UNIVERSAL MEDIA CENTER::PLATFORM::WASM
{
class CTitanWebApis
{
public:
  static WasmDeviceInfo GetDeviceInfo();
};
} // namespace UNIVERSAL MEDIA CENTER::PLATFORM::WASM
