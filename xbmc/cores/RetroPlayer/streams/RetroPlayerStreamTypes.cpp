/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RetroPlayerStreamTypes.h"

#include "IRetroPlayerStream.h"

using namespace KODI;
using namespace RETRO;

void DeleteStream::operator()(IRetroPlayerStream* stream)
{
  delete stream;
}
