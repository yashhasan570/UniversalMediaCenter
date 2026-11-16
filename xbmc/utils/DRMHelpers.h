/*
 *  Copyright (C) 2005-2021 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <cstdint>
#include <string>

namespace DRMHELPERS
{

std::string FourCCToString(uint32_t fourcc);

std::string ModifierToString(uint64_t modifier);

} // namespace DRMHELPERS
