/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "KeyboardTranslator.h"

#include "utils/Map.h"

#include <string_view>

using namespace UNIVERSAL MEDIA CENTER;
using namespace KEYBOARD;

namespace
{
constexpr auto KeyboardSymbols = make_map<std::string_view, Key>({
    {KEY_SYMBOL_BACKSPACE, K_BACKSPACE},
    {KEY_SYMBOL_TAB, K_TAB},
    {KEY_SYMBOL_CLEAR, K_CLEAR},
    {KEY_SYMBOL_ENTER, K_RETURN},
    {KEY_SYMBOL_PAUSE, K_PAUSE},
    {KEY_SYMBOL_ESCAPE, K_ESCAPE},
    {KEY_SYMBOL_SPACE, K_SPACE},
    {KEY_SYMBOL_EXCLAIM, K_EXCLAIM},
    {KEY_SYMBOL_DOUBLEQUOTE, K_QUOTEDBL},
    {KEY_SYMBOL_HASH, K_HASH},
    {KEY_SYMBOL_DOLLAR, K_DOLLAR},
    {KEY_SYMBOL_AMPERSAND, K_AMPERSAND},
    {KEY_SYMBOL_QUOTE, K_QUOTE},
    {KEY_SYMBOL_LEFTPAREN, K_LEFTPAREN},
    {KEY_SYMBOL_RIGHTPAREN, K_RIGHTPAREN},
    {KEY_SYMBOL_ASTERISK, K_ASTERISK},
    {KEY_SYMBOL_PLUS, K_PLUS},
    {KEY_SYMBOL_COMMA, K_COMMA},
    {KEY_SYMBOL_MINUS, K_MINUS},
    {KEY_SYMBOL_PERIOD, K_PERIOD},
    {KEY_SYMBOL_SLASH, K_SLASH},
    {KEY_SYMBOL_0, K_0},
    {KEY_SYMBOL_1, K_1},
    {KEY_SYMBOL_2, K_2},
    {KEY_SYMBOL_3, K_3},
    {KEY_SYMBOL_4, K_4},
    {KEY_SYMBOL_5, K_5},
    {KEY_SYMBOL_6, K_6},
    {KEY_SYMBOL_7, K_7},
    {KEY_SYMBOL_8, K_8},
    {KEY_SYMBOL_9, K_9},
    {KEY_SYMBOL_COLON, K_COLON},
    {KEY_SYMBOL_SEMICOLON, K_SEMICOLON},
    {KEY_SYMBOL_LESS, K_LESS},
    {KEY_SYMBOL_EQUALS, K_EQUALS},
    {KEY_SYMBOL_GREATER, K_GREATER},
    {KEY_SYMBOL_QUESTION, K_QUESTION},
    {KEY_SYMBOL_AT, K_AT},
    {KEY_SYMBOL_LEFTBRACKET, K_LEFTBRACKET},
    {KEY_SYMBOL_BACKSLASH, K_BACKSLASH},
    {KEY_SYMBOL_RIGHTBRACKET, K_RIGHTBRACKET},
    {KEY_SYMBOL_CARET, K_CARET},
    {KEY_SYMBOL_UNDERSCORE, K_UNDERSCORE},
    {KEY_SYMBOL_GRAVE, K_BACKQUOTE},
    {KEY_SYMBOL_A, K_a},
    {KEY_SYMBOL_B, K_b},
    {KEY_SYMBOL_C, K_c},
    {KEY_SYMBOL_D, K_d},
    {KEY_SYMBOL_E, K_e},
    {KEY_SYMBOL_F, K_f},
    {KEY_SYMBOL_G, K_g},
    {KEY_SYMBOL_H, K_h},
    {KEY_SYMBOL_I, K_i},
    {KEY_SYMBOL_J, K_j},
    {KEY_SYMBOL_K, K_k},
    {KEY_SYMBOL_L, K_l},
    {KEY_SYMBOL_M, K_m},
    {KEY_SYMBOL_N, K_n},
    {KEY_SYMBOL_O, K_o},
    {KEY_SYMBOL_P, K_p},
    {KEY_SYMBOL_Q, K_q},
    {KEY_SYMBOL_R, K_r},
    {KEY_SYMBOL_S, K_s},
    {KEY_SYMBOL_T, K_t},
    {KEY_SYMBOL_U, K_u},
    {KEY_SYMBOL_V, K_v},
    {KEY_SYMBOL_W, K_w},
    {KEY_SYMBOL_X, K_x},
    {KEY_SYMBOL_Y, K_y},
    {KEY_SYMBOL_Z, K_z},
    {KEY_SYMBOL_LEFTBRACE, K_LEFTBRACE},
    {KEY_SYMBOL_BAR, K_PIPE},
    {KEY_SYMBOL_RIGHTBRACE, K_RIGHTBRACE},
    {KEY_SYMBOL_TILDE, K_TILDE},
    {KEY_SYMBOL_DELETE, K_DELETE},
    {KEY_SYMBOL_KP0, K_KP0},
    {KEY_SYMBOL_KP1, K_KP1},
    {KEY_SYMBOL_KP2, K_KP2},
    {KEY_SYMBOL_KP3, K_KP3},
    {KEY_SYMBOL_KP4, K_KP4},
    {KEY_SYMBOL_KP5, K_KP5},
    {KEY_SYMBOL_KP6, K_KP6},
    {KEY_SYMBOL_KP7, K_KP7},
    {KEY_SYMBOL_KP8, K_KP8},
    {KEY_SYMBOL_KP9, K_KP9},
    {KEY_SYMBOL_KPPERIOD, K_KP_PERIOD},
    {KEY_SYMBOL_KPDIVIDE, K_KP_DIVIDE},
    {KEY_SYMBOL_KPMULTIPLY, K_KP_MULTIPLY},
    {KEY_SYMBOL_KPMINUS, K_KP_MINUS},
    {KEY_SYMBOL_KPPLUS, K_KP_PLUS},
    {KEY_SYMBOL_KPENTER, K_KP_ENTER},
    {KEY_SYMBOL_KPEQUALS, K_KP_EQUALS},
    {KEY_SYMBOL_UP, K_UP},
    {KEY_SYMBOL_DOWN, K_DOWN},
    {KEY_SYMBOL_RIGHT, K_RIGHT},
    {KEY_SYMBOL_LEFT, K_LEFT},
    {KEY_SYMBOL_INSERT, K_INSERT},
    {KEY_SYMBOL_HOME, K_HOME},
    {KEY_SYMBOL_END, K_END},
    {KEY_SYMBOL_PAGEUP, K_PAGEUP},
    {KEY_SYMBOL_PAGEDOWN, K_PAGEDOWN},
    {KEY_SYMBOL_F1, K_F1},
    {KEY_SYMBOL_F2, K_F2},
    {KEY_SYMBOL_F3, K_F3},
    {KEY_SYMBOL_F4, K_F4},
    {KEY_SYMBOL_F5, K_F5},
    {KEY_SYMBOL_F6, K_F6},
    {KEY_SYMBOL_F7, K_F7},
    {KEY_SYMBOL_F8, K_F8},
    {KEY_SYMBOL_F9, K_F9},
    {KEY_SYMBOL_F10, K_F10},
    {KEY_SYMBOL_F11, K_F11},
    {KEY_SYMBOL_F12, K_F12},
    {KEY_SYMBOL_F13, K_F13},
    {KEY_SYMBOL_F14, K_F14},
    {KEY_SYMBOL_F15, K_F15},
    {KEY_SYMBOL_NUMLOCK, K_NUMLOCK},
    {KEY_SYMBOL_CAPSLOCK, K_CAPSLOCK},
    {KEY_SYMBOL_SCROLLLOCK, K_SCROLLOCK},
    {KEY_SYMBOL_LEFTSHIFT, K_LSHIFT},
    {KEY_SYMBOL_RIGHTSHIFT, K_RSHIFT},
    {KEY_SYMBOL_LEFTCTRL, K_LCTRL},
    {KEY_SYMBOL_RIGHTCTRL, K_RCTRL},
    {KEY_SYMBOL_LEFTALT, K_LALT},
    {KEY_SYMBOL_RIGHTALT, K_RALT},
    {KEY_SYMBOL_LEFTMETA, K_LMETA},
    {KEY_SYMBOL_RIGHTMETA, K_RMETA},
    {KEY_SYMBOL_LEFTSUPER, K_LSUPER},
    {KEY_SYMBOL_RIGHTSUPER, K_RSUPER},
    {KEY_SYMBOL_MODE, K_MODE},
    {KEY_SYMBOL_COMPOSE, K_COMPOSE},
    {KEY_SYMBOL_HELP, K_HELP},
    {KEY_SYMBOL_PRINTSCREEN, K_PRINT},
    {KEY_SYMBOL_SYSREQ, K_SYSREQ},
    {KEY_SYMBOL_BREAK, K_BREAK},
    {KEY_SYMBOL_MENU, K_MENU},
    {KEY_SYMBOL_POWER, K_POWER},
    {KEY_SYMBOL_EURO, K_EURO},
    {KEY_SYMBOL_UNDO, K_UNDO},
    {KEY_SYMBOL_OEM102, K_OEM_102},
});
} // namespace

Key CKeyboardTranslator::TranslateKeysym(const SymbolName& symbolName)
{
  return KeyboardSymbols.get(symbolName).value_or(K_UNKNOWN);
}

const char* CKeyboardTranslator::TranslateKeycode(Key keycode)
{
  switch (keycode)
  {
    case K_BACKSPACE:
      return KEY_SYMBOL_BACKSPACE;
    case K_TAB:
    case K_XKB_KP_TAB:
      return KEY_SYMBOL_TAB;
    case K_CLEAR:
      return KEY_SYMBOL_CLEAR;
    case K_RETURN:
      return KEY_SYMBOL_ENTER;
    case K_PAUSE:
      return KEY_SYMBOL_PAUSE;
    case K_ESCAPE:
      return KEY_SYMBOL_ESCAPE;
    case K_SPACE:
    case K_XKB_KP_SPACE:
      return KEY_SYMBOL_SPACE;
    case K_EXCLAIM:
      return KEY_SYMBOL_EXCLAIM;
    case K_QUOTEDBL:
      return KEY_SYMBOL_DOUBLEQUOTE;
    case K_HASH:
      return KEY_SYMBOL_HASH;
    case K_DOLLAR:
      return KEY_SYMBOL_DOLLAR;
    case K_AMPERSAND:
      return KEY_SYMBOL_AMPERSAND;
    case K_QUOTE:
      return KEY_SYMBOL_QUOTE;
    case K_LEFTPAREN:
      return KEY_SYMBOL_LEFTPAREN;
    case K_RIGHTPAREN:
      return KEY_SYMBOL_RIGHTPAREN;
    case K_ASTERISK:
      return KEY_SYMBOL_ASTERISK;
    case K_PLUS:
      return KEY_SYMBOL_PLUS;
    case K_COMMA:
      return KEY_SYMBOL_COMMA;
    case K_MINUS:
      return KEY_SYMBOL_MINUS;
    case K_PERIOD:
      return KEY_SYMBOL_PERIOD;
    case K_SLASH:
      return KEY_SYMBOL_SLASH;
    case K_0:
      return KEY_SYMBOL_0;
    case K_1:
      return KEY_SYMBOL_1;
    case K_2:
      return KEY_SYMBOL_2;
    case K_3:
      return KEY_SYMBOL_3;
    case K_4:
      return KEY_SYMBOL_4;
    case K_5:
      return KEY_SYMBOL_5;
    case K_6:
      return KEY_SYMBOL_6;
    case K_7:
      return KEY_SYMBOL_7;
    case K_8:
      return KEY_SYMBOL_8;
    case K_9:
      return KEY_SYMBOL_9;
    case K_COLON:
      return KEY_SYMBOL_COLON;
    case K_SEMICOLON:
      return KEY_SYMBOL_SEMICOLON;
    case K_LESS:
      return KEY_SYMBOL_LESS;
    case K_EQUALS:
      return KEY_SYMBOL_EQUALS;
    case K_GREATER:
      return KEY_SYMBOL_GREATER;
    case K_QUESTION:
      return KEY_SYMBOL_QUESTION;
    case K_AT:
      return KEY_SYMBOL_AT;
    case K_LEFTBRACKET:
      return KEY_SYMBOL_LEFTBRACKET;
    case K_BACKSLASH:
      return KEY_SYMBOL_BACKSLASH;
    case K_RIGHTBRACKET:
      return KEY_SYMBOL_RIGHTBRACKET;
    case K_CARET:
      return KEY_SYMBOL_CARET;
    case K_UNDERSCORE:
      return KEY_SYMBOL_UNDERSCORE;
    case K_BACKQUOTE:
      return KEY_SYMBOL_GRAVE;
    case K_a:
      return KEY_SYMBOL_A;
    case K_b:
      return KEY_SYMBOL_B;
    case K_c:
      return KEY_SYMBOL_C;
    case K_d:
      return KEY_SYMBOL_D;
    case K_e:
      return KEY_SYMBOL_E;
    case K_f:
      return KEY_SYMBOL_F;
    case K_g:
      return KEY_SYMBOL_G;
    case K_h:
      return KEY_SYMBOL_H;
    case K_i:
      return KEY_SYMBOL_I;
    case K_j:
      return KEY_SYMBOL_J;
    case K_k:
      return KEY_SYMBOL_K;
    case K_l:
      return KEY_SYMBOL_L;
    case K_m:
      return KEY_SYMBOL_M;
    case K_n:
      return KEY_SYMBOL_N;
    case K_o:
      return KEY_SYMBOL_O;
    case K_p:
      return KEY_SYMBOL_P;
    case K_q:
      return KEY_SYMBOL_Q;
    case K_r:
      return KEY_SYMBOL_R;
    case K_s:
      return KEY_SYMBOL_S;
    case K_t:
      return KEY_SYMBOL_T;
    case K_u:
      return KEY_SYMBOL_U;
    case K_v:
      return KEY_SYMBOL_V;
    case K_w:
      return KEY_SYMBOL_W;
    case K_x:
      return KEY_SYMBOL_X;
    case K_y:
      return KEY_SYMBOL_Y;
    case K_z:
      return KEY_SYMBOL_Z;
    case K_LEFTBRACE:
      return KEY_SYMBOL_LEFTBRACE;
    case K_PIPE:
      return KEY_SYMBOL_BAR;
    case K_RIGHTBRACE:
      return KEY_SYMBOL_RIGHTBRACE;
    case K_TILDE:
      return KEY_SYMBOL_TILDE;
    case K_DELETE:
      return KEY_SYMBOL_DELETE;
    case K_KP0:
    case K_XKB_KP_INSERT: // numlock disabled
    case K_XKB_KP0: // numlock enabled
      return KEY_SYMBOL_KP0;
    case K_KP1:
    case K_XKB_KP_END: // numlock disabled
    case K_XKB_KP1: // numlock enabled
      return KEY_SYMBOL_KP1;
    case K_KP2:
    case K_XKB_KP_DOWN: // numlock disabled
    case K_XKB_KP2: // numlock enabled
      return KEY_SYMBOL_KP2;
    case K_KP3:
    case K_XKB_KP_PAGE_DOWN: // numlock disabled
    case K_XKB_KP3: // numlock enabled
      return KEY_SYMBOL_KP3;
    case K_KP4:
    case K_XKB_KP_LEFT: // numlock disabled
    case K_XKB_KP4: // numlock enabled
      return KEY_SYMBOL_KP4;
    case K_KP5:
    case K_XKB_KP_BEGIN: // numlock disabled
    case K_XKB_KP5: // numlock enabled
      return KEY_SYMBOL_KP5;
    case K_KP6:
    case K_XKB_KP_RIGHT: // numlock disabled
    case K_XKB_KP6: // numlock enabled
      return KEY_SYMBOL_KP6;
    case K_KP7:
    case K_XKB_KP_HOME: // numlock disabled
    case K_XKB_KP7: // numlock enabled
      return KEY_SYMBOL_KP7;
    case K_KP8:
    case K_XKB_KP_UP: // numlock disabled
    case K_XKB_KP8: // numlock enabled
      return KEY_SYMBOL_KP8;
    case K_KP9:
    case K_XKB_KP_PAGE_UP: // numlock disabled
    case K_XKB_KP9: // numlock enabled
      return KEY_SYMBOL_KP9;
    case K_KP_PERIOD:
    case K_XKB_KP_DELETE: // numlock disabled
    case K_XKB_KP_DECIMAL: // numlock enabled
      return KEY_SYMBOL_KPPERIOD;
    case K_KP_DIVIDE:
    case K_XKB_KP_DIVIDE:
      return KEY_SYMBOL_KPDIVIDE;
    case K_KP_MULTIPLY:
    case K_XKB_KP_MULTIPLY:
      return KEY_SYMBOL_KPMULTIPLY;
    case K_KP_MINUS:
    case K_XKB_KP_SUBTRACT:
      return KEY_SYMBOL_KPMINUS;
    case K_KP_PLUS:
    case K_XKB_KP_ADD:
      return KEY_SYMBOL_KPPLUS;
    case K_KP_ENTER:
    case K_XKB_KP_ENTER:
      return KEY_SYMBOL_KPENTER;
    case K_KP_EQUALS:
    case K_XKB_KP_EQUALS:
      return KEY_SYMBOL_KPEQUALS;
    case K_UP:
      return KEY_SYMBOL_UP;
    case K_DOWN:
      return KEY_SYMBOL_DOWN;
    case K_RIGHT:
      return KEY_SYMBOL_RIGHT;
    case K_LEFT:
      return KEY_SYMBOL_LEFT;
    case K_INSERT:
      return KEY_SYMBOL_INSERT;
    case K_HOME:
      return KEY_SYMBOL_HOME;
    case K_END:
      return KEY_SYMBOL_END;
    case K_PAGEUP:
      return KEY_SYMBOL_PAGEUP;
    case K_PAGEDOWN:
      return KEY_SYMBOL_PAGEDOWN;
    case K_F1:
    case K_XKB_KP_F1:
      return KEY_SYMBOL_F1;
    case K_F2:
    case K_XKB_KP_F2:
      return KEY_SYMBOL_F2;
    case K_F3:
    case K_XKB_KP_F3:
      return KEY_SYMBOL_F3;
    case K_F4:
    case K_XKB_KP_F4:
      return KEY_SYMBOL_F4;
    case K_F5:
      return KEY_SYMBOL_F5;
    case K_F6:
      return KEY_SYMBOL_F6;
    case K_F7:
      return KEY_SYMBOL_F7;
    case K_F8:
      return KEY_SYMBOL_F8;
    case K_F9:
      return KEY_SYMBOL_F9;
    case K_F10:
      return KEY_SYMBOL_F10;
    case K_F11:
      return KEY_SYMBOL_F11;
    case K_F12:
      return KEY_SYMBOL_F12;
    case K_F13:
      return KEY_SYMBOL_F13;
    case K_F14:
      return KEY_SYMBOL_F14;
    case K_F15:
      return KEY_SYMBOL_F15;
    case K_NUMLOCK:
      return KEY_SYMBOL_NUMLOCK;
    case K_CAPSLOCK:
      return KEY_SYMBOL_CAPSLOCK;
    case K_SCROLLOCK:
      return KEY_SYMBOL_SCROLLLOCK;
    case K_LSHIFT:
      return KEY_SYMBOL_LEFTSHIFT;
    case K_RSHIFT:
      return KEY_SYMBOL_RIGHTSHIFT;
    case K_LCTRL:
      return KEY_SYMBOL_LEFTCTRL;
    case K_RCTRL:
      return KEY_SYMBOL_RIGHTCTRL;
    case K_LALT:
      return KEY_SYMBOL_LEFTALT;
    case K_RALT:
      return KEY_SYMBOL_RIGHTALT;
    case K_LMETA:
      return KEY_SYMBOL_LEFTMETA;
    case K_RMETA:
      return KEY_SYMBOL_RIGHTMETA;
    case K_LSUPER:
      return KEY_SYMBOL_LEFTSUPER;
    case K_RSUPER:
      return KEY_SYMBOL_RIGHTSUPER;
    case K_MODE:
      return KEY_SYMBOL_MODE;
    case K_COMPOSE:
      return KEY_SYMBOL_COMPOSE;
    case K_HELP:
      return KEY_SYMBOL_HELP;
    case K_PRINT:
      return KEY_SYMBOL_PRINTSCREEN;
    case K_SYSREQ:
      return KEY_SYMBOL_SYSREQ;
    case K_BREAK:
      return KEY_SYMBOL_BREAK;
    case K_MENU:
      return KEY_SYMBOL_MENU;
    case K_POWER:
      return KEY_SYMBOL_POWER;
    case K_EURO:
      return KEY_SYMBOL_EURO;
    case K_UNDO:
      return KEY_SYMBOL_UNDO;
    case K_OEM_102:
      return KEY_SYMBOL_OEM102;
    default:
      break;
  }

  return "";
}
