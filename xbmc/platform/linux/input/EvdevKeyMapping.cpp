/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "EvdevKeyMapping.h"

#include "utils/Map.h"

#include <linux/input.h>

constexpr auto evdevMap = make_map<uint32_t, Key>({
    // still missing in libxkbcommon 1.13.2
    {KEY_PREVIOUS, K_PREVIOUS},
    {KEY_NEXT, K_NEXT},
    {KEY_POWER2, K_POWER2},
    {KEY_SETUP, K_SETUP},
    {KEY_LAST, K_RECALL_LAST},
    {KEY_LIST, K_LIST},
    {KEY_MP3, K_MP3},

    // ambiguously mapped in xkb, map via evdev
    {KEY_AGAIN, K_AGAIN},
    {KEY_CHANNEL, K_CHANNEL},
    {KEY_EXIT, K_EXIT},

    // added in libxkbcommon 1.11.0 - see also XkbCompat.h
    {KEY_OK, K_OK}, // XKB_KEY_XF86OK
    {KEY_EPG, K_EPG}, // XKB_KEY_XF86MediaSelectProgramGuide
    {KEY_PROGRAM, K_EPG}, // XKB_KEY_XF86MediaSelectProgramGuide
    {KEY_PVR, K_PVR}, // XKB_KEY_XF86MediaSelectHome
    {KEY_LANGUAGE, K_LANGUAGE}, // XKB_KEY_XF86MediaLanguageMenu
    {KEY_TITLE, K_TITLE_MENU}, // XKB_KEY_XF86MediaTitleMenu
    {KEY_MODE, K_AUDIO_MODE}, // XKB_KEY_XF86AudioChannelMode
    {KEY_TV, K_TV}, // XKB_KEY_XF86MediaSelectTV
    {KEY_RADIO, K_RADIO}, // XKB_KEY_XF86MediaSelectRadio
    {KEY_TUNER, K_TUNER}, // XKB_KEY_XF86MediaSelectTuner
    {KEY_PLAYER, K_LAUNCH_MEDIA_SELECT}, // XKB_KEY_XF86MediaPlayer
    {KEY_TEXT, K_TEXT} // XKB_KEY_XF86MediaSelectTeletext
});

std::optional<Key> CEvdevKeyMapping::KeyForEvdevCode(uint32_t code)
{
  return evdevMap.get(code);
}
