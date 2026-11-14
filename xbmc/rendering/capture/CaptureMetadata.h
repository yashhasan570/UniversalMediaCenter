/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/iimage.h"

class CWinSystemBase;

namespace UNIVERSAL MEDIA CENTER
{
namespace RENDERING
{
namespace CAPTURE
{

//! \brief H.273 description of what the display output shows right now.
ImageColorMetadata GetOutputColorMetadata(CWinSystemBase& winSystem);

} // namespace CAPTURE
} // namespace RENDERING
} // namespace UNIVERSAL MEDIA CENTER
