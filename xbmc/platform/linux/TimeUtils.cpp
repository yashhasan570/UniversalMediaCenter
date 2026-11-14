/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "TimeUtils.h"

std::int64_t UNIVERSAL MEDIA CENTER::LINUX::TimespecDifference(timespec const& start, timespec const& end)
{
  return (end.tv_sec - start.tv_sec) * UINT64_C(1000000000) + (end.tv_nsec - start.tv_nsec);
}