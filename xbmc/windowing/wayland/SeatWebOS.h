/*
*  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Seat.h"

namespace UNIVERSAL MEDIA CENTER::WINDOWING::WAYLAND
{

class CSeatWebOS final : public CSeat
{
public:
  CSeatWebOS(std::uint32_t globalName, wayland::seat_t const& seat, CConnection& connection)
    : CSeat(globalName, seat, connection)
  {
  }

  void SetCursor(std::uint32_t serial,
                 wayland::surface_t const& surface,
                 std::int32_t hotspotX,
                 std::int32_t hotspotY) override;

protected:
  void InstallKeyboardRepeatInfo() override;
};

} // namespace UNIVERSAL MEDIA CENTER::WINDOWING::WAYLAND
