/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <algorithm>
#include <random>

namespace UNIVERSAL MEDIA CENTER
{
namespace UTILS
{
template<class TIterator>
void RandomShuffle(TIterator begin, TIterator end)
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::shuffle(begin, end, mt);
}
}
}
