/*
 *  Copyright (C) 2007-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "input/keyboard/_keytable.h"

#include "input/keyboard/_keysym.h"
#include "input/keyboard/_vkeys.h"
#include "utils/StringUtils.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace KEYBOARD;

namespace
{
// The array of KEYTABLEs used in .
// sym, unicode, ascii, vkey, keyname
// clang-format off
static const KEYTABLE KeyTable[] = {
    {K_BACKSPACE, 0, 0, VK_BACK, "backspace"},
    {K_TAB, 0, 0, VK_TAB, "tab"},
    {K_RETURN, 0, 0, VK_RETURN, "return"},
    {K_ESCAPE, 0, 0, VK_ESCAPE, "escape"},
    {0, 0, 0, VK_ESCAPE, "esc"} // Allowed abbreviation for "escape"

    // Number keys on the main keyboard
    ,
    {K_0, '0', '0', VK_0, "zero"},
    {K_1, '1', '1', VK_1, "one"},
    {K_2, '2', '2', VK_2, "two"},
    {K_3, '3', '3', VK_3, "three"},
    {K_4, '4', '4', VK_4, "four"},
    {K_5, '5', '5', VK_5, "five"},
    {K_6, '6', '6', VK_6, "six"},
    {K_7, '7', '7', VK_7, "seven"},
    {K_8, '8', '8', VK_8, "eight"},
    {K_9, '9', '9', VK_9, "nine"}

    // A to Z - note that upper case A-Z don't have a matching name or
    // vkey. Only the lower case a-z are used in key mappings.
    ,
    {K_a, 'A', 'A', VK_A, NULL},
    {K_b, 'B', 'B', VK_B, NULL},
    {K_c, 'C', 'C', VK_C, NULL},
    {K_d, 'D', 'D', VK_D, NULL},
    {K_e, 'E', 'E', VK_E, NULL},
    {K_f, 'F', 'F', VK_F, NULL},
    {K_g, 'G', 'G', VK_G, NULL},
    {K_h, 'H', 'H', VK_H, NULL},
    {K_i, 'I', 'I', VK_I, NULL},
    {K_j, 'J', 'J', VK_J, NULL},
    {K_k, 'K', 'K', VK_K, NULL},
    {K_l, 'L', 'L', VK_L, NULL},
    {K_m, 'M', 'M', VK_M, NULL},
    {K_n, 'N', 'N', VK_N, NULL},
    {K_o, 'O', 'O', VK_O, NULL},
    {K_p, 'P', 'P', VK_P, NULL},
    {K_q, 'Q', 'Q', VK_Q, NULL},
    {K_r, 'R', 'R', VK_R, NULL},
    {K_s, 'S', 'S', VK_S, NULL},
    {K_t, 'T', 'T', VK_T, NULL},
    {K_u, 'U', 'U', VK_U, NULL},
    {K_v, 'V', 'V', VK_V, NULL},
    {K_w, 'W', 'W', VK_W, NULL},
    {K_x, 'X', 'X', VK_X, NULL},
    {K_y, 'Y', 'Y', VK_Y, NULL},
    {K_z, 'Z', 'Z', VK_Z, NULL}

    ,
    {K_a, 'a', 'a', VK_A, "a"},
    {K_b, 'b', 'b', VK_B, "b"},
    {K_c, 'c', 'c', VK_C, "c"},
    {K_d, 'd', 'd', VK_D, "d"},
    {K_e, 'e', 'e', VK_E, "e"},
    {K_f, 'f', 'f', VK_F, "f"},
    {K_g, 'g', 'g', VK_G, "g"},
    {K_h, 'h', 'h', VK_H, "h"},
    {K_i, 'i', 'i', VK_I, "i"},
    {K_j, 'j', 'j', VK_J, "j"},
    {K_k, 'k', 'k', VK_K, "k"},
    {K_l, 'l', 'l', VK_L, "l"},
    {K_m, 'm', 'm', VK_M, "m"},
    {K_n, 'n', 'n', VK_N, "n"},
    {K_o, 'o', 'o', VK_O, "o"},
    {K_p, 'p', 'p', VK_P, "p"},
    {K_q, 'q', 'q', VK_Q, "q"},
    {K_r, 'r', 'r', VK_R, "r"},
    {K_s, 's', 's', VK_S, "s"},
    {K_t, 't', 't', VK_T, "t"},
    {K_u, 'u', 'u', VK_U, "u"},
    {K_v, 'v', 'v', VK_V, "v"},
    {K_w, 'w', 'w', VK_W, "w"},
    {K_x, 'x', 'x', VK_X, "x"},
    {K_y, 'y', 'y', VK_Y, "y"},
    {K_z, 'z', 'z', VK_Z, "z"}

    // Misc printing characters
    ,
    {K_SPACE, ' ', ' ', VK_SPACE, "space"},
    {K_EXCLAIM, '!', '!', VK_EXCLAIM, "exclaim"},
    {K_QUOTEDBL, '"', '"', VK_QUOTEDBL, "doublequote"},
    {K_HASH, '#', '#', VK_HASH, "hash"},
    {K_DOLLAR, '$', '$', VK_DOLLAR, "dollar"},
    {K_PERCENT, '%', '%', VK_PERCENT, "percent"},
    {K_AMPERSAND, '&', '&', VK_AMPERSAND, "ampersand"},
    {K_QUOTE, '\'', '\'', VK_QUOTE, "quote"},
    {K_LEFTPAREN, '(', '(', VK_LEFTPAREN, "leftbracket"},
    {K_RIGHTPAREN, ')', ')', VK_RIGHTPAREN, "rightbracket"},
    {K_ASTERISK, '*', '*', VK_ASTERISK, "asterisk"},
    {K_PLUS, '+', '+', VK_PLUS, "plus"},
    {K_COMMA, ',', ',', VK_COMMA, "comma"},
    {K_MINUS, '-', '-', VK_MINUS, "minus"},
    {K_PERIOD, '.', '.', VK_PERIOD, "period"},
    {K_SLASH, '/', '/', VK_SLASH, "forwardslash"}

    ,
    {K_COLON, ':', ':', VK_COLON, "colon"},
    {K_SEMICOLON, ';', ';', VK_SEMICOLON, "semicolon"},
    {K_LESS, '<', '<', VK_LESS, "lessthan"},
    {K_EQUALS, '=', '=', VK_EQUALS, "equals"},
    {K_GREATER, '>', '>', VK_GREATER, "greaterthan"},
    {K_QUESTION, '?', '?', VK_QUESTION, "questionmark"},
    {K_AT, '@', '@', VK_AT, "at"}

    ,
    {K_LEFTBRACKET, '[', '[', VK_LEFTBRACKET, "opensquarebracket"},
    {K_BACKSLASH, '\\', '\\', VK_BACKSLASH, "backslash"},
    {K_RIGHTBRACKET, ']', ']', VK_RIGHTBRACKET, "closesquarebracket"},
    {K_CARET, '^', '^', VK_CARET, "caret"},
    {K_UNDERSCORE, '_', '_', VK_UNDERSCORE, "underline"},
    {K_BACKQUOTE, '`', '`', VK_BACKQUOTE, "leftquote"}

    ,
    {K_LEFTBRACE, '{', '{', VK_LEFTBRACE, "openbrace"},
    {K_PIPE, '|', '|', VK_PIPE, "pipe"},
    {K_RIGHTBRACE, '}', '}', VK_RIGHTBRACE, "closebrace"},
    {K_TILDE, '~', '~', VK_TILDE, "tilde"}

    // Numeric keypad
    ,
    {K_KP0, '0', '0', VK_NUMPAD0, "numpadzero"},
    {K_KP1, '1', '1', VK_NUMPAD1, "numpadone"},
    {K_KP2, '2', '2', VK_NUMPAD2, "numpadtwo"},
    {K_KP3, '3', '3', VK_NUMPAD3, "numpadthree"},
    {K_KP4, '4', '4', VK_NUMPAD4, "numpadfour"},
    {K_KP5, '5', '5', VK_NUMPAD5, "numpadfive"},
    {K_KP6, '6', '6', VK_NUMPAD6, "numpadsix"},
    {K_KP7, '7', '7', VK_NUMPAD7, "numpadseven"},
    {K_KP8, '8', '8', VK_NUMPAD8, "numpadeight"},
    {K_KP9, '9', '9', VK_NUMPAD9, "numpadnine"}

    ,
    {K_KP_DIVIDE, '/', '/', VK_NUMPADDIVIDE, "numpaddivide"},
    {K_KP_MULTIPLY, '*', '*', VK_NUMPADTIMES, "numpadtimes"},
    {K_KP_MINUS, '-', '-', VK_NUMPADMINUS, "numpadminus"},
    {K_KP_PLUS, '+', '+', VK_NUMPADPLUS, "numpadplus"},
    {K_KP_ENTER, 0, 0, VK_NUMPADENTER, "enter"},
    {K_KP_PERIOD, '.', '.', VK_NUMPADPERIOD, "numpadperiod"}

    // Multimedia keys
    ,
    {K_BROWSER_BACK, 0, 0, VK_BROWSER_BACK, "browser_back"},
    {K_BROWSER_FORWARD, 0, 0, VK_BROWSER_FORWARD, "browser_forward"},
    {K_BROWSER_REFRESH, 0, 0, VK_BROWSER_REFRESH, "browser_refresh"},
    {K_BROWSER_STOP, 0, 0, VK_BROWSER_STOP, "browser_stop"},
    {K_BROWSER_SEARCH, 0, 0, VK_BROWSER_SEARCH, "browser_search"},
    {K_BROWSER_FAVORITES, 0, 0, VK_BROWSER_FAVORITES, "browser_favorites"},
    {K_BROWSER_HOME, 0, 0, VK_BROWSER_HOME, "browser_home"},
    {K_VOLUME_MUTE, 0, 0, VK_VOLUME_MUTE, "volume_mute"},
    {K_VOLUME_DOWN, 0, 0, VK_VOLUME_DOWN, "volume_down"},
    {K_VOLUME_UP, 0, 0, VK_VOLUME_UP, "volume_up"},
    {K_MEDIA_NEXT_TRACK, 0, 0, VK_MEDIA_NEXT_TRACK, "next_track"},
    {K_MEDIA_PREV_TRACK, 0, 0, VK_MEDIA_PREV_TRACK, "prev_track"},
    {K_MEDIA_STOP, 0, 0, VK_MEDIA_STOP, "stop"},
    {K_MEDIA_PLAY_PAUSE, 0, 0, VK_MEDIA_PLAY_PAUSE, "play_pause"},
    {K_MEDIA_REWIND, 0, 0, VK_MEDIA_REWIND, "rewind"},
    {K_MEDIA_FASTFORWARD, 0, 0, VK_MEDIA_FASTFORWARD, "fastforward"},
    {K_LAUNCH_MAIL, 0, 0, VK_LAUNCH_MAIL, "launch_mail"},
    {K_LAUNCH_MEDIA_SELECT, 0, 0, VK_LAUNCH_MEDIA_SELECT, "launch_media_select"},
    {K_LAUNCH_APP1, 0, 0, VK_LAUNCH_APP1, "launch_app1_pc_icon"},
    {K_LAUNCH_APP2, 0, 0, VK_LAUNCH_APP2, "launch_app2_pc_icon"},
    {K_LAUNCH_FILE_BROWSER, 0, 0, VK_LAUNCH_FILE_BROWSER, "launch_file_browser"},
    {K_LAUNCH_MEDIA_CENTER, 0, 0, VK_LAUNCH_MEDIA_CENTER, "launch_media_center"},
    {K_PLAY, 0, 0, VK_MEDIA_PLAY_PAUSE, "play_pause"},
    {K_STOP, 0, 0, VK_MEDIA_STOP, "stop"},
    {K_REWIND, 0, 0, VK_MEDIA_REWIND, "rewind"},
    {K_FASTFORWARD, 0, 0, VK_MEDIA_FASTFORWARD, "fastforward"},
    {K_RECORD, 0, 0, VK_MEDIA_RECORD, "record"},
    {K_LAUNCH_MESSENGER, 0, 0, VK_LAUNCH_MESSENGER, "launch_messenger"},
    {K_LAUNCH_PRESENTATION, 0, 0, VK_LAUNCH_PRESENTATION, "launch_presentation"},
    {K_BRIGHTNESS_UP, 0, 0, VK_BRIGHTNESS_UP, "brightness_up"},
    {K_BRIGHTNESS_DOWN, 0, 0, VK_BRIGHTNESS_DOWN, "brightness_down"},

    // Remote control keys

    {K_SUBTITLE, 0, 0, VK_SUBTITLE, "subtitle"},
    {K_OK, 0, 0, VK_OK, "ok"},
    {K_LANGUAGE, 0, 0, VK_LANGUAGE, "language"},
    {K_CHANNEL_UP, 0, 0, VK_CHANNEL_UP, "channel_up"},
    {K_CHANNEL_DOWN, 0, 0, VK_CHANNEL_DOWN, "channel_down"},
    {K_SELECT, 0, 0, VK_SELECT, "select"},
    {K_EJECT, 0, 0, VK_EJECT, "eject"},
    {K_SHUFFLE, 0, 0, VK_SHUFFLE, "shuffle"},
    {K_PREVIOUS, 0, 0, VK_PREVIOUS, "previous"},
    {K_NEXT, 0, 0, VK_NEXT, "next"},
    {K_POWER2, 0, 0, VK_POWER2, "power2"},
    {K_SETUP, 0, 0, VK_SETUP, "setup"},
    {K_RECALL_LAST, 0, 0, VK_RECALL_LAST, "recall_last"},
    {K_LIST, 0, 0, VK_LIST, "list"},
    {K_DVD, 0, 0, VK_DVD, "dvd"},
    {K_TV, 0, 0, VK_TV, "tv"},
    {K_RADIO, 0, 0, VK_RADIO, "radio"},
    {K_AUDIO, 0, 0, VK_AUDIO, "audio"},
    {K_VIDEO, 0, 0, VK_VIDEO, "video"},
    {K_CAMERA, 0, 0, VK_CAMERA, "camera"},
    {K_TUNER, 0, 0, VK_TUNER, "tuner"},
    {K_PVR, 0, 0, VK_PVR, "pvr"},
    {K_FULLSCREEN, 0, 0, VK_FULLSCREEN, "fullscreen"},
    {K_TITLE_MENU, 0, 0, VK_TITLE_MENU, "title_menu"},
    {K_AUDIO_MODE, 0, 0, VK_AUDIO_MODE, "audio_mode"},
    {K_AGAIN, 0, 0, VK_AGAIN, "again"},
    {K_CHANNEL, 0, 0, VK_CHANNEL, "channel"},
    {K_EXIT, 0, 0, VK_EXIT, "exit"},
    {K_CONTEXT_MENU, 0, 0, VK_CONTEXT_MENU, "context_menu"},
    {K_TIME, 0, 0, VK_TIME, "time"},
    {K_RELOAD, 0, 0, VK_RELOAD, "reload"},
    {K_VIDEO_DEFAULT, 0, 0, VK_VIDEO_DEFAULT, "video_default"},
    {K_ANGLE, 0, 0, VK_ANGLE, "angle"},
    {K_GOTO, 0, 0, VK_GOTO, "goto"},
    {K_CABLE, 0, 0, VK_CABLE, "cable"},
    {K_OPTION, 0, 0, VK_OPTION, "option"},
    {K_FRAME_BACK, 0, 0, VK_FRAME_BACK, "frame_back"},
    {K_FRAME_FORWARD, 0, 0, VK_FRAME_FORWARD, "frame_forward"},
    {K_PROPERTIES, 0, 0, VK_PROPERTIES, "properties"},
    {K_MP3, 0, 0, VK_MP3, "mp3"},

    // Function keys

    {K_F1, 0, 0, VK_F1, "f1"},
    {K_F2, 0, 0, VK_F2, "f2"},
    {K_F3, 0, 0, VK_F3, "f3"},
    {K_F4, 0, 0, VK_F4, "f4"},
    {K_F5, 0, 0, VK_F5, "f5"},
    {K_F6, 0, 0, VK_F6, "f6"},
    {K_F7, 0, 0, VK_F7, "f7"},
    {K_F8, 0, 0, VK_F8, "f8"},
    {K_F9, 0, 0, VK_F9, "f9"},
    {K_F10, 0, 0, VK_F10, "f10"},
    {K_F11, 0, 0, VK_F11, "f11"},
    {K_F12, 0, 0, VK_F12, "f12"},
    {K_F13, 0, 0, VK_F13, "f13"},
    {K_F14, 0, 0, VK_F14, "f14"},
    {K_F15, 0, 0, VK_F15, "f15"}

    // Misc non-printing keys
    ,
    {K_UP, 0, 0, VK_UP, "up"},
    {K_DOWN, 0, 0, VK_DOWN, "down"},
    {K_RIGHT, 0, 0, VK_RIGHT, "right"},
    {K_LEFT, 0, 0, VK_LEFT, "left"},
    {K_INSERT, 0, 0, VK_INSERT, "insert"},
    {K_DELETE, 0, 0, VK_DELETE, "delete"},
    {K_HOME, 0, 0, VK_HOME, "home"},
    {K_END, 0, 0, VK_END, "end"},
    {K_PAGEUP, 0, 0, VK_PAGEUP, "pageup"},
    {K_PAGEDOWN, 0, 0, VK_PAGEDOWN, "pagedown"},
    {K_NUMLOCK, 0, 0, VK_NUMLOCK, "numlock"},
    {K_CAPSLOCK, 0, 0, VK_CAPSLOCK, "capslock"},
    {K_RSHIFT, 0, 0, VK_RSHIFT, "rightshift"},
    {K_LSHIFT, 0, 0, VK_LSHIFT, "leftshift"},
    {K_RCTRL, 0, 0, VK_RCONTROL, "rightctrl"},
    {K_LCTRL, 0, 0, VK_LCONTROL, "leftctrl"},
    {K_LALT, 0, 0, VK_LMENU, "leftalt"},
    {K_LSUPER, 0, 0, VK_LWIN, "leftwindows"},
    {K_RSUPER, 0, 0, VK_RWIN, "rightwindows"},
    {K_MENU, 0, 0, VK_MENU, "menu"},
    {K_PAUSE, 0, 0, VK_PAUSE, "pause"},
    {K_SCROLLOCK, 0, 0, VK_SCROLLLOCK, "scrolllock"},
    {K_PRINT, 0, 0, VK_PRINTSCREEN, "printscreen"},
    {K_POWER, 0, 0, VK_POWER, "power"},
    {K_SLEEP, 0, 0, VK_SLEEP, "sleep"},
    {K_GUIDE, 0, 0, VK_GUIDE, "guide"},
    {K_SETTINGS, 0, 0, VK_SETTINGS, "settings"},
    {K_INFO, 0, 0, VK_INFO, "info"},
    {K_RED, 0, 0, VK_RED, "red"},
    {K_GREEN, 0, 0, VK_GREEN, "green"},
    {K_YELLOW, 0, 0, VK_YELLOW, "yellow"},
    {K_BLUE, 0, 0, VK_BLUE, "blue"},
    {K_ZOOM, 0, 0, VK_ZOOM, "zoom"},
    {K_TEXT, 0, 0, VK_TEXT, "text"},
    {K_FAVORITES, 0, 0, VK_FAVORITES, "favorites"},
    {K_HOMEPAGE, 0, 0, VK_HOMEPAGE, "homepage"},
    {K_CONFIG, 0, 0, VK_CONFIG, "config"},
    {K_EPG, 0, 0, VK_EPG, "epg"},
    {K_PHONE, 0, 0, VK_PHONE, "phone"},

    /*
     * Numpad extended keypad keys at table end
     *
     * They are appended to the end of this key table to ensure backward
     * compatibility and minimize disruption to existing keycode mappings.
     */

    // Extended keypad key symbols for Num Lock state-specific behaviors, with
    // Num Lock disabled
    {K_XKB_KP_HOME, 0, 0, VK_HOME, "home"},
    {K_XKB_KP_LEFT, 0, 0, VK_LEFT, "left"},
    {K_XKB_KP_UP, 0, 0, VK_UP, "up"},
    {K_XKB_KP_RIGHT, 0, 0, VK_RIGHT, "right"},
    {K_XKB_KP_DOWN, 0, 0, VK_DOWN, "down"},
    {K_XKB_KP_PAGE_UP, 0, 0, VK_PAGEUP, "pageup"},
    {K_XKB_KP_PAGE_DOWN, 0, 0, VK_PAGEDOWN, "pagedown"},
    {K_XKB_KP_END, 0, 0, VK_END, "end"},
    {K_XKB_KP_BEGIN, 0, 0, VK_HOME, "home"},
    {K_XKB_KP_INSERT, 0, 0, VK_INSERT, "insert"},
    {K_XKB_KP_DELETE, 0, 0, VK_DELETE, "delete"},

    // Extended keypad key symbols for Num Lock state-specific behaviors, with
    // Num Lock enabled
    {K_XKB_KP_DECIMAL, '.', '.', VK_NUMPADPERIOD, "numpadperiod"},
    {K_XKB_KP0, '0', '0', VK_NUMPAD0, "numpadzero"},
    {K_XKB_KP1, '1', '1', VK_NUMPAD1, "numpadone"},
    {K_XKB_KP2, '2', '2', VK_NUMPAD2, "numpadtwo"},
    {K_XKB_KP3, '3', '3', VK_NUMPAD3, "numpadthree"},
    {K_XKB_KP4, '4', '4', VK_NUMPAD4, "numpadfour"},
    {K_XKB_KP5, '5', '5', VK_NUMPAD5, "numpadfive"},
    {K_XKB_KP6, '6', '6', VK_NUMPAD6, "numpadsix"},
    {K_XKB_KP7, '7', '7', VK_NUMPAD7, "numpadseven"},
    {K_XKB_KP8, '8', '8', VK_NUMPAD8, "numpadeight"},
    {K_XKB_KP9, '9', '9', VK_NUMPAD9, "numpadnine"},

    // Extended keypad key symbols for Num Lock state-independent behaviors
    {K_XKB_KP_SPACE, ' ', ' ', VK_SPACE, "space"},
    {K_XKB_KP_TAB, 0, 0, VK_TAB, "tab"},
    {K_XKB_KP_ENTER, 0, 0, VK_NUMPADENTER, "enter"},
    {K_XKB_KP_F1, 0, 0, VK_F1, "f1"},
    {K_XKB_KP_F2, 0, 0, VK_F2, "f2"},
    {K_XKB_KP_F3, 0, 0, VK_F3, "f3"},
    {K_XKB_KP_F4, 0, 0, VK_F4, "f4"},
    {K_XKB_KP_EQUALS, '=', '=', 0, "numpadequals"},
    {K_XKB_KP_MULTIPLY, '*', '*', VK_NUMPADTIMES, "numpadtimes"},
    {K_XKB_KP_ADD, '+', '+', VK_NUMPADPLUS, "numpadplus"},
    {K_XKB_KP_SEPARATOR, 0, 0, 0, "numpadseparator"},
    {K_XKB_KP_SUBTRACT, '-', '-', VK_NUMPADMINUS, "numpadminus"},
    {K_XKB_KP_DIVIDE, '/', '/', VK_NUMPADDIVIDE, "numpaddivide"},
};
// clang-format on

static int KeyTableSize = sizeof(KeyTable) / sizeof(KEYTABLE);
} // namespace

bool KeyTable::LookupName(std::string keyname, KEYTABLE* keytable)
{
  // If the name being searched for is empty there will be no match
  if (keyname.empty())
    return false;

  // We need the button name to be in lowercase
  StringUtils::ToLower(keyname);

  // Look up the key name in KeyTable
  for (int i = 0; i < KeyTableSize; i++)
  {
    if (KeyTable[i].keyname)
    {
      if (strcmp(keyname.c_str(), KeyTable[i].keyname) == 0)
      {
        *keytable = KeyTable[i];
        return true;
      }
    }
  }

  // The name wasn't found
  return false;
}

bool KeyTable::LookupSym(uint16_t sym, KEYTABLE* keytable)
{
  // If the sym being searched for is zero there will be no match
  if (sym == 0)
    return false;

  // Look up the sym in KeyTable
  for (int i = 0; i < KeyTableSize; i++)
  {
    if (sym == KeyTable[i].sym)
    {
      *keytable = KeyTable[i];
      return true;
    }
  }

  // The name wasn't found
  return false;
}

bool KeyTable::LookupUnicode(uint16_t unicode, KEYTABLE* keytable)
{
  // If the unicode being searched for is zero there will be no match
  if (unicode == 0)
    return false;

  // Look up the unicode in KeyTable
  for (int i = 0; i < KeyTableSize; i++)
  {
    if (unicode == KeyTable[i].unicode)
    {
      *keytable = KeyTable[i];
      return true;
    }
  }

  // The name wasn't found
  return false;
}

bool KeyTable::LookupSymAndUnicode(uint16_t sym, uint16_t unicode, KEYTABLE* keytable)
{
  // If the sym being searched for is zero there will be no match (the
  // unicode can be zero if the sym is non-zero)
  if (sym == 0)
    return false;

  // Look up the sym and unicode in KeyTable
  for (int i = 0; i < KeyTableSize; i++)
  {
    if (sym == KeyTable[i].sym && unicode == KeyTable[i].unicode)
    {
      *keytable = KeyTable[i];
      return true;
    }
  }

  // The sym and unicode weren't found
  return false;
}

bool KeyTable::LookupVKeyName(uint32_t vkey, KEYTABLE* keytable)
{
  // If the vkey being searched for is zero there will be no match
  if (vkey == 0)
    return false;

  // Look up the vkey in KeyTable
  for (int i = 0; i < KeyTableSize; i++)
  {
    if (vkey == KeyTable[i].vkey && KeyTable[i].keyname)
    {
      *keytable = KeyTable[i];
      return true;
    }
  }

  // The name wasn't found
  return false;
}
