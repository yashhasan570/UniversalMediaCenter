/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER::UTILS
{

// Skin tone modifiers
constexpr bool IsEmojiModifier(char32_t codepoint)
{
  return codepoint >= 0x1F3FB && codepoint <= 0x1F3FF;
}

// Code points that continue the emoji before them: zero width joiner, variation selectors,
// combining enclosing keycap, skin tone modifiers and tags
constexpr bool ContinuesEmoji(char32_t codepoint)
{
  return codepoint == 0x200D || codepoint == 0xFE0E || codepoint == 0xFE0F || codepoint == 0x20E3 ||
         IsEmojiModifier(codepoint) || (codepoint >= 0xE0020 && codepoint <= 0xE007F);
}

} // namespace UNIVERSAL MEDIA CENTER::UTILS
