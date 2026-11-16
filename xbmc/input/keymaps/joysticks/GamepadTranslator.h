/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <stdint.h>
#include <string>

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYMAP
{
/*!
 * \ingroup keymap
 *
 * \brief Gamepad translator, only used by EventClient
 *
 * The legacy gamepad translator uses an original Xbox controller (the one with
 * white and black buttons) for mapping.
 */
class CGamepadTranslator
{
public:
  static uint32_t TranslateString(std::string strButton);
};
} // namespace KEYMAP
} // namespace UNIVERSAL MEDIA CENTER
