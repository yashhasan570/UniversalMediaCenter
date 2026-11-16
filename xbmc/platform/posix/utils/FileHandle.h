/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/ScopeGuard.h"

#include <unistd.h>

namespace UNIVERSAL MEDIA CENTER
{
namespace UTILS
{
namespace POSIX
{

class CFileHandle : public CScopeGuard<int, -1, decltype(close)>
{
public:
  CFileHandle() noexcept : CScopeGuard(close, -1) {}
  explicit CFileHandle(int fd) : CScopeGuard(close, fd) {}
};

}
}
}
