/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../OSScreenSaver.h"

#include <cstdint>

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace LINUX
{

// FIXME This is not really linux-specific, BSD could also have this. Better directory name?

class COSScreenSaverFreedesktop : public IOSScreenSaver
{
public:
  COSScreenSaverFreedesktop() = default;

  static bool IsAvailable();
  void Inhibit() override;
  void Uninhibit() override;

private:
  bool m_inhibited{false};
  std::uint32_t m_cookie;
};

}
}
}
