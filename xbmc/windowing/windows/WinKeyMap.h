/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "ServiceBroker.h"
#include "Util.h"
#include "input/keyboard/_keysym.h"
#include "input/keyboard/_vkeys.h"
#include "settings/AdvancedSettings.h"
#include "settings/SettingsComponent.h"

#include <array>

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace WINDOWS
{

static std::array<Key, K_LAST> VK_keymap;

static void DIB_InitOSKeymap()
{
  /* Map the VK keysyms */
  VK_keymap.fill(K_UNKNOWN);

  VK_keymap[VK_BACK] = K_BACKSPACE;
  VK_keymap[VK_TAB] = K_TAB;
  VK_keymap[VK_CLEAR] = K_CLEAR;
  VK_keymap[VK_RETURN] = K_RETURN;
  VK_keymap[VK_PAUSE] = K_PAUSE;
  VK_keymap[VK_ESCAPE] = K_ESCAPE;
  VK_keymap[VK_SPACE] = K_SPACE;
  VK_keymap[VK_APOSTROPHE] = K_QUOTE;
  VK_keymap[VK_COMMA] = K_COMMA;
  VK_keymap[VK_MINUS] = K_MINUS;
  VK_keymap[VK_PERIOD] = K_PERIOD;
  VK_keymap[VK_SLASH] = K_SLASH;
  VK_keymap[VK_0] = K_0;
  VK_keymap[VK_1] = K_1;
  VK_keymap[VK_2] = K_2;
  VK_keymap[VK_3] = K_3;
  VK_keymap[VK_4] = K_4;
  VK_keymap[VK_5] = K_5;
  VK_keymap[VK_6] = K_6;
  VK_keymap[VK_7] = K_7;
  VK_keymap[VK_8] = K_8;
  VK_keymap[VK_9] = K_9;
  VK_keymap[VK_SEMICOLON] = K_SEMICOLON;
  VK_keymap[VK_EQUALS] = K_EQUALS;
  VK_keymap[VK_LBRACKET] = K_LEFTBRACKET;
  VK_keymap[VK_BACKSLASH] = K_BACKSLASH;
  VK_keymap[VK_OEM_102] = K_BACKSLASH;
  VK_keymap[VK_RBRACKET] = K_RIGHTBRACKET;
  VK_keymap[VK_GRAVE] = K_BACKQUOTE;
  VK_keymap[VK_BACKTICK] = K_BACKQUOTE;
  VK_keymap[VK_A] = K_a;
  VK_keymap[VK_B] = K_b;
  VK_keymap[VK_C] = K_c;
  VK_keymap[VK_D] = K_d;
  VK_keymap[VK_E] = K_e;
  VK_keymap[VK_F] = K_f;
  VK_keymap[VK_G] = K_g;
  VK_keymap[VK_H] = K_h;
  VK_keymap[VK_I] = K_i;
  VK_keymap[VK_J] = K_j;
  VK_keymap[VK_K] = K_k;
  VK_keymap[VK_L] = K_l;
  VK_keymap[VK_M] = K_m;
  VK_keymap[VK_N] = K_n;
  VK_keymap[VK_O] = K_o;
  VK_keymap[VK_P] = K_p;
  VK_keymap[VK_Q] = K_q;
  VK_keymap[VK_R] = K_r;
  VK_keymap[VK_S] = K_s;
  VK_keymap[VK_T] = K_t;
  VK_keymap[VK_U] = K_u;
  VK_keymap[VK_V] = K_v;
  VK_keymap[VK_W] = K_w;
  VK_keymap[VK_X] = K_x;
  VK_keymap[VK_Y] = K_y;
  VK_keymap[VK_Z] = K_z;
  VK_keymap[VK_DELETE] = K_DELETE;

  VK_keymap[VK_NUMPAD0] = K_KP0;
  VK_keymap[VK_NUMPAD1] = K_KP1;
  VK_keymap[VK_NUMPAD2] = K_KP2;
  VK_keymap[VK_NUMPAD3] = K_KP3;
  VK_keymap[VK_NUMPAD4] = K_KP4;
  VK_keymap[VK_NUMPAD5] = K_KP5;
  VK_keymap[VK_NUMPAD6] = K_KP6;
  VK_keymap[VK_NUMPAD7] = K_KP7;
  VK_keymap[VK_NUMPAD8] = K_KP8;
  VK_keymap[VK_NUMPAD9] = K_KP9;
  VK_keymap[VK_DECIMAL] = K_KP_PERIOD;
  VK_keymap[VK_DIVIDE] = K_KP_DIVIDE;
  VK_keymap[VK_MULTIPLY] = K_KP_MULTIPLY;
  VK_keymap[VK_SUBTRACT] = K_KP_MINUS;
  VK_keymap[VK_ADD] = K_KP_PLUS;

  VK_keymap[VK_UP] = K_UP;
  VK_keymap[VK_DOWN] = K_DOWN;
  VK_keymap[VK_RIGHT] = K_RIGHT;
  VK_keymap[VK_LEFT] = K_LEFT;
  VK_keymap[VK_INSERT] = K_INSERT;
  VK_keymap[VK_HOME] = K_HOME;
  VK_keymap[VK_END] = K_END;
  VK_keymap[VK_PRIOR] = K_PAGEUP;
  VK_keymap[VK_NEXT] = K_PAGEDOWN;

  VK_keymap[VK_F1] = K_F1;
  VK_keymap[VK_F2] = K_F2;
  VK_keymap[VK_F3] = K_F3;
  VK_keymap[VK_F4] = K_F4;
  VK_keymap[VK_F5] = K_F5;
  VK_keymap[VK_F6] = K_F6;
  VK_keymap[VK_F7] = K_F7;
  VK_keymap[VK_F8] = K_F8;
  VK_keymap[VK_F9] = K_F9;
  VK_keymap[VK_F10] = K_F10;
  VK_keymap[VK_F11] = K_F11;
  VK_keymap[VK_F12] = K_F12;
  VK_keymap[VK_F13] = K_F13;
  VK_keymap[VK_F14] = K_F14;
  VK_keymap[VK_F15] = K_F15;

  VK_keymap[VK_NUMLOCK] = K_NUMLOCK;
  VK_keymap[VK_CAPITAL] = K_CAPSLOCK;
  VK_keymap[VK_SCROLL] = K_SCROLLOCK;
  VK_keymap[VK_RSHIFT] = K_RSHIFT;
  VK_keymap[VK_LSHIFT] = K_LSHIFT;
  VK_keymap[VK_RCONTROL] = K_RCTRL;
  VK_keymap[VK_LCONTROL] = K_LCTRL;
  VK_keymap[VK_RMENU] = K_RALT;
  VK_keymap[VK_LMENU] = K_LALT;
  VK_keymap[VK_RWIN] = K_RSUPER;
  VK_keymap[VK_LWIN] = K_LSUPER;

  VK_keymap[VK_HELP] = K_HELP;
#ifdef VK_PRINT
  VK_keymap[VK_PRINT] = K_PRINT;
#endif
  VK_keymap[VK_SNAPSHOT] = K_PRINT;
  VK_keymap[VK_CANCEL] = K_BREAK;
  VK_keymap[VK_APPS] = K_MENU;

  // Only include the multimedia keys if they have been enabled in the
  // advanced settings
  if (CServiceBroker::GetSettingsComponent()->GetAdvancedSettings()->m_enableMultimediaKeys)
  {
    VK_keymap[VK_BROWSER_BACK] = K_BROWSER_BACK;
    VK_keymap[VK_BROWSER_FORWARD] = K_BROWSER_FORWARD;
    VK_keymap[VK_BROWSER_REFRESH] = K_BROWSER_REFRESH;
    VK_keymap[VK_BROWSER_STOP] = K_BROWSER_STOP;
    VK_keymap[VK_BROWSER_SEARCH] = K_BROWSER_SEARCH;
    VK_keymap[VK_BROWSER_FAVORITES] = K_BROWSER_FAVORITES;
    VK_keymap[VK_BROWSER_HOME] = K_BROWSER_HOME;
    VK_keymap[VK_VOLUME_MUTE] = K_VOLUME_MUTE;
    VK_keymap[VK_VOLUME_DOWN] = K_VOLUME_DOWN;
    VK_keymap[VK_VOLUME_UP] = K_VOLUME_UP;
    VK_keymap[VK_MEDIA_NEXT_TRACK] = K_MEDIA_NEXT_TRACK;
    VK_keymap[VK_MEDIA_PREV_TRACK] = K_MEDIA_PREV_TRACK;
    VK_keymap[VK_MEDIA_STOP] = K_MEDIA_STOP;
    VK_keymap[VK_MEDIA_PLAY_PAUSE] = K_MEDIA_PLAY_PAUSE;
    VK_keymap[VK_LAUNCH_MAIL] = K_LAUNCH_MAIL;
    VK_keymap[VK_LAUNCH_MEDIA_SELECT] = K_LAUNCH_MEDIA_SELECT;
    VK_keymap[VK_LAUNCH_APP1] = K_LAUNCH_APP1;
    VK_keymap[VK_LAUNCH_APP2] = K_LAUNCH_APP2;
  }
}

} // namespace WINDOWS
} // namespace WINDOWING
} // namespace UNIVERSAL MEDIA CENTER
