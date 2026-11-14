/*
 *  Copyright (C) 2018-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PlatformDefs.h"

namespace UNIVERSAL MEDIA CENTER::NETWORK
{
/*!
  \brief Enable SO_REUSEADDR so a socket may bind to a busy address.
  The common description is reusing a listening port/address. This is not
  the distinct SO_REUSEPORT option. On Emscripten/WASM the host stack
  does not support this call; the implementation is a no-op that returns true.
  \return True if the option was set or the platform skipped it (WASM).
 */
bool SetReusePort(SOCKET sock);

/*!
  \brief Set IPPROTO_IPV6 / IPV6_V6ONLY. Pass 0 for dual-stack, 1 for IPv6-only.
  On Emscripten/WASM, unsupported; the implementation is a no-op that returns true.
  \return True if the option was set or the platform skipped it (WASM).
 */
bool SetIPv6Only(SOCKET sock, int v6only);
} // namespace UNIVERSAL MEDIA CENTER::NETWORK
