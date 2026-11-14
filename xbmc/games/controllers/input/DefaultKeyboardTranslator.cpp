/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "DefaultKeyboardTranslator.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace GAME;

namespace
{
constexpr auto DEFAULT_KEYBOARD_FEATURE_BACKSPACE = "backspace";
constexpr auto DEFAULT_KEYBOARD_FEATURE_TAB = "tab";
constexpr auto DEFAULT_KEYBOARD_FEATURE_CLEAR = "clear";
constexpr auto DEFAULT_KEYBOARD_FEATURE_ENTER = "enter";
constexpr auto DEFAULT_KEYBOARD_FEATURE_PAUSE = "pause";
constexpr auto DEFAULT_KEYBOARD_FEATURE_ESCAPE = "escape";
constexpr auto DEFAULT_KEYBOARD_FEATURE_SPACE = "space";
constexpr auto DEFAULT_KEYBOARD_FEATURE_EXCLAIM = "exclaim";
constexpr auto DEFAULT_KEYBOARD_FEATURE_DOUBLEQUOTE = "doublequote";
constexpr auto DEFAULT_KEYBOARD_FEATURE_HASH = "hash";
constexpr auto DEFAULT_KEYBOARD_FEATURE_DOLLAR = "dollar";
constexpr auto DEFAULT_KEYBOARD_FEATURE_AMPERSAND = "ampersand";
constexpr auto DEFAULT_KEYBOARD_FEATURE_QUOTE = "quote";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTPAREN = "leftparen";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTPAREN = "rightparen";
constexpr auto DEFAULT_KEYBOARD_FEATURE_ASTERISK = "asterisk";
constexpr auto DEFAULT_KEYBOARD_FEATURE_PLUS = "plus";
constexpr auto DEFAULT_KEYBOARD_FEATURE_COMMA = "comma";
constexpr auto DEFAULT_KEYBOARD_FEATURE_MINUS = "minus";
constexpr auto DEFAULT_KEYBOARD_FEATURE_PERIOD = "period";
constexpr auto DEFAULT_KEYBOARD_FEATURE_SLASH = "slash";
constexpr auto DEFAULT_KEYBOARD_FEATURE_0 = "0";
constexpr auto DEFAULT_KEYBOARD_FEATURE_1 = "1";
constexpr auto DEFAULT_KEYBOARD_FEATURE_2 = "2";
constexpr auto DEFAULT_KEYBOARD_FEATURE_3 = "3";
constexpr auto DEFAULT_KEYBOARD_FEATURE_4 = "4";
constexpr auto DEFAULT_KEYBOARD_FEATURE_5 = "5";
constexpr auto DEFAULT_KEYBOARD_FEATURE_6 = "6";
constexpr auto DEFAULT_KEYBOARD_FEATURE_7 = "7";
constexpr auto DEFAULT_KEYBOARD_FEATURE_8 = "8";
constexpr auto DEFAULT_KEYBOARD_FEATURE_9 = "9";
constexpr auto DEFAULT_KEYBOARD_FEATURE_COLON = "colon";
constexpr auto DEFAULT_KEYBOARD_FEATURE_SEMICOLON = "semicolon";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LESS = "less";
constexpr auto DEFAULT_KEYBOARD_FEATURE_EQUALS = "equals";
constexpr auto DEFAULT_KEYBOARD_FEATURE_GREATER = "greater";
constexpr auto DEFAULT_KEYBOARD_FEATURE_QUESTION = "question";
constexpr auto DEFAULT_KEYBOARD_FEATURE_AT = "at";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTBRACKET = "leftbracket";
constexpr auto DEFAULT_KEYBOARD_FEATURE_BACKSLASH = "backslash";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTBRACKET = "rightbracket";
constexpr auto DEFAULT_KEYBOARD_FEATURE_CARET = "caret";
constexpr auto DEFAULT_KEYBOARD_FEATURE_UNDERSCORE = "underscore";
constexpr auto DEFAULT_KEYBOARD_FEATURE_GRAVE = "grave";
constexpr auto DEFAULT_KEYBOARD_FEATURE_A = "a";
constexpr auto DEFAULT_KEYBOARD_FEATURE_B = "b";
constexpr auto DEFAULT_KEYBOARD_FEATURE_C = "c";
constexpr auto DEFAULT_KEYBOARD_FEATURE_D = "d";
constexpr auto DEFAULT_KEYBOARD_FEATURE_E = "e";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F = "f";
constexpr auto DEFAULT_KEYBOARD_FEATURE_G = "g";
constexpr auto DEFAULT_KEYBOARD_FEATURE_H = "h";
constexpr auto DEFAULT_KEYBOARD_FEATURE_I = "i";
constexpr auto DEFAULT_KEYBOARD_FEATURE_J = "j";
constexpr auto DEFAULT_KEYBOARD_FEATURE_K = "k";
constexpr auto DEFAULT_KEYBOARD_FEATURE_L = "l";
constexpr auto DEFAULT_KEYBOARD_FEATURE_M = "m";
constexpr auto DEFAULT_KEYBOARD_FEATURE_N = "n";
constexpr auto DEFAULT_KEYBOARD_FEATURE_O = "o";
constexpr auto DEFAULT_KEYBOARD_FEATURE_P = "p";
constexpr auto DEFAULT_KEYBOARD_FEATURE_Q = "q";
constexpr auto DEFAULT_KEYBOARD_FEATURE_R = "r";
constexpr auto DEFAULT_KEYBOARD_FEATURE_S = "s";
constexpr auto DEFAULT_KEYBOARD_FEATURE_T = "t";
constexpr auto DEFAULT_KEYBOARD_FEATURE_U = "u";
constexpr auto DEFAULT_KEYBOARD_FEATURE_V = "v";
constexpr auto DEFAULT_KEYBOARD_FEATURE_W = "w";
constexpr auto DEFAULT_KEYBOARD_FEATURE_X = "x";
constexpr auto DEFAULT_KEYBOARD_FEATURE_Y = "y";
constexpr auto DEFAULT_KEYBOARD_FEATURE_Z = "z";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTBRACE = "leftbrace";
constexpr auto DEFAULT_KEYBOARD_FEATURE_BAR = "bar";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTBRACE = "rightbrace";
constexpr auto DEFAULT_KEYBOARD_FEATURE_TILDE = "tilde";
constexpr auto DEFAULT_KEYBOARD_FEATURE_DELETE = "delete";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP0 = "kp0";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP1 = "kp1";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP2 = "kp2";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP3 = "kp3";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP4 = "kp4";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP5 = "kp5";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP6 = "kp6";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP7 = "kp7";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP8 = "kp8";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KP9 = "kp9";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPPERIOD = "kpperiod";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPDIVIDE = "kpdivide";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPMULTIPLY = "kpmultiply";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPMINUS = "kpminus";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPPLUS = "kpplus";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPENTER = "kpenter";
constexpr auto DEFAULT_KEYBOARD_FEATURE_KPEQUALS = "kpequals";
constexpr auto DEFAULT_KEYBOARD_FEATURE_UP = "up";
constexpr auto DEFAULT_KEYBOARD_FEATURE_DOWN = "down";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHT = "right";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFT = "left";
constexpr auto DEFAULT_KEYBOARD_FEATURE_INSERT = "insert";
constexpr auto DEFAULT_KEYBOARD_FEATURE_HOME = "home";
constexpr auto DEFAULT_KEYBOARD_FEATURE_END = "end";
constexpr auto DEFAULT_KEYBOARD_FEATURE_PAGEUP = "pageup";
constexpr auto DEFAULT_KEYBOARD_FEATURE_PAGEDOWN = "pagedown";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F1 = "f1";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F2 = "f2";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F3 = "f3";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F4 = "f4";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F5 = "f5";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F6 = "f6";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F7 = "f7";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F8 = "f8";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F9 = "f9";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F10 = "f10";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F11 = "f11";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F12 = "f12";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F13 = "f13";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F14 = "f14";
constexpr auto DEFAULT_KEYBOARD_FEATURE_F15 = "f15";
constexpr auto DEFAULT_KEYBOARD_FEATURE_NUMLOCK = "numlock";
constexpr auto DEFAULT_KEYBOARD_FEATURE_CAPSLOCK = "capslock";
constexpr auto DEFAULT_KEYBOARD_FEATURE_SCROLLLOCK = "scrolllock";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTSHIFT = "rightshift";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTSHIFT = "leftshift";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTCTRL = "rightctrl";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTCTRL = "leftctrl";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTALT = "rightalt";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTALT = "leftalt";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTMETA = "rightmeta";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTMETA = "leftmeta";
constexpr auto DEFAULT_KEYBOARD_FEATURE_RIGHTSUPER = "rightsuper";
constexpr auto DEFAULT_KEYBOARD_FEATURE_LEFTSUPER = "leftsuper";
constexpr auto DEFAULT_KEYBOARD_FEATURE_MODE = "mode";
constexpr auto DEFAULT_KEYBOARD_FEATURE_COMPOSE = "compose";
constexpr auto DEFAULT_KEYBOARD_FEATURE_HELP = "help";
constexpr auto DEFAULT_KEYBOARD_FEATURE_PRINTSCREEN = "printscreen";
constexpr auto DEFAULT_KEYBOARD_FEATURE_SYSREQ = "sysreq";
constexpr auto DEFAULT_KEYBOARD_FEATURE_BREAK = "break";
constexpr auto DEFAULT_KEYBOARD_FEATURE_MENU = "menu";
constexpr auto DEFAULT_KEYBOARD_FEATURE_POWER = "power";
constexpr auto DEFAULT_KEYBOARD_FEATURE_EURO = "euro";
constexpr auto DEFAULT_KEYBOARD_FEATURE_UNDO = "undo";
constexpr auto DEFAULT_KEYBOARD_FEATURE_OEM_102 = "oem102";
} // namespace

const char* CDefaultKeyboardTranslator::TranslateKeycode(KEYBOARD::Key keycode)
{
  switch (keycode)
  {
    case K_BACKSPACE:
      return DEFAULT_KEYBOARD_FEATURE_BACKSPACE;
    case K_TAB:
      return DEFAULT_KEYBOARD_FEATURE_TAB;
    case K_CLEAR:
      return DEFAULT_KEYBOARD_FEATURE_CLEAR;
    case K_RETURN:
      return DEFAULT_KEYBOARD_FEATURE_ENTER;
    case K_PAUSE:
      return DEFAULT_KEYBOARD_FEATURE_PAUSE;
    case K_ESCAPE:
      return DEFAULT_KEYBOARD_FEATURE_ESCAPE;
    case K_SPACE:
      return DEFAULT_KEYBOARD_FEATURE_SPACE;
    case K_EXCLAIM:
      return DEFAULT_KEYBOARD_FEATURE_EXCLAIM;
    case K_QUOTEDBL:
      return DEFAULT_KEYBOARD_FEATURE_DOUBLEQUOTE;
    case K_HASH:
      return DEFAULT_KEYBOARD_FEATURE_HASH;
    case K_DOLLAR:
      return DEFAULT_KEYBOARD_FEATURE_DOLLAR;
    case K_AMPERSAND:
      return DEFAULT_KEYBOARD_FEATURE_AMPERSAND;
    case K_QUOTE:
      return DEFAULT_KEYBOARD_FEATURE_QUOTE;
    case K_LEFTPAREN:
      return DEFAULT_KEYBOARD_FEATURE_LEFTPAREN;
    case K_RIGHTPAREN:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTPAREN;
    case K_ASTERISK:
      return DEFAULT_KEYBOARD_FEATURE_ASTERISK;
    case K_PLUS:
      return DEFAULT_KEYBOARD_FEATURE_PLUS;
    case K_COMMA:
      return DEFAULT_KEYBOARD_FEATURE_COMMA;
    case K_MINUS:
      return DEFAULT_KEYBOARD_FEATURE_MINUS;
    case K_PERIOD:
      return DEFAULT_KEYBOARD_FEATURE_PERIOD;
    case K_SLASH:
      return DEFAULT_KEYBOARD_FEATURE_SLASH;
    case K_0:
      return DEFAULT_KEYBOARD_FEATURE_0;
    case K_1:
      return DEFAULT_KEYBOARD_FEATURE_1;
    case K_2:
      return DEFAULT_KEYBOARD_FEATURE_2;
    case K_3:
      return DEFAULT_KEYBOARD_FEATURE_3;
    case K_4:
      return DEFAULT_KEYBOARD_FEATURE_4;
    case K_5:
      return DEFAULT_KEYBOARD_FEATURE_5;
    case K_6:
      return DEFAULT_KEYBOARD_FEATURE_6;
    case K_7:
      return DEFAULT_KEYBOARD_FEATURE_7;
    case K_8:
      return DEFAULT_KEYBOARD_FEATURE_8;
    case K_9:
      return DEFAULT_KEYBOARD_FEATURE_9;
    case K_COLON:
      return DEFAULT_KEYBOARD_FEATURE_COLON;
    case K_SEMICOLON:
      return DEFAULT_KEYBOARD_FEATURE_SEMICOLON;
    case K_LESS:
      return DEFAULT_KEYBOARD_FEATURE_LESS;
    case K_EQUALS:
      return DEFAULT_KEYBOARD_FEATURE_EQUALS;
    case K_GREATER:
      return DEFAULT_KEYBOARD_FEATURE_GREATER;
    case K_QUESTION:
      return DEFAULT_KEYBOARD_FEATURE_QUESTION;
    case K_AT:
      return DEFAULT_KEYBOARD_FEATURE_AT;
    case K_LEFTBRACKET:
      return DEFAULT_KEYBOARD_FEATURE_LEFTBRACKET;
    case K_BACKSLASH:
      return DEFAULT_KEYBOARD_FEATURE_BACKSLASH;
    case K_RIGHTBRACKET:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTBRACKET;
    case K_CARET:
      return DEFAULT_KEYBOARD_FEATURE_CARET;
    case K_UNDERSCORE:
      return DEFAULT_KEYBOARD_FEATURE_UNDERSCORE;
    case K_BACKQUOTE:
      return DEFAULT_KEYBOARD_FEATURE_GRAVE;
    case K_a:
      return DEFAULT_KEYBOARD_FEATURE_A;
    case K_b:
      return DEFAULT_KEYBOARD_FEATURE_B;
    case K_c:
      return DEFAULT_KEYBOARD_FEATURE_C;
    case K_d:
      return DEFAULT_KEYBOARD_FEATURE_D;
    case K_e:
      return DEFAULT_KEYBOARD_FEATURE_E;
    case K_f:
      return DEFAULT_KEYBOARD_FEATURE_F;
    case K_g:
      return DEFAULT_KEYBOARD_FEATURE_G;
    case K_h:
      return DEFAULT_KEYBOARD_FEATURE_H;
    case K_i:
      return DEFAULT_KEYBOARD_FEATURE_I;
    case K_j:
      return DEFAULT_KEYBOARD_FEATURE_J;
    case K_k:
      return DEFAULT_KEYBOARD_FEATURE_K;
    case K_l:
      return DEFAULT_KEYBOARD_FEATURE_L;
    case K_m:
      return DEFAULT_KEYBOARD_FEATURE_M;
    case K_n:
      return DEFAULT_KEYBOARD_FEATURE_N;
    case K_o:
      return DEFAULT_KEYBOARD_FEATURE_O;
    case K_p:
      return DEFAULT_KEYBOARD_FEATURE_P;
    case K_q:
      return DEFAULT_KEYBOARD_FEATURE_Q;
    case K_r:
      return DEFAULT_KEYBOARD_FEATURE_R;
    case K_s:
      return DEFAULT_KEYBOARD_FEATURE_S;
    case K_t:
      return DEFAULT_KEYBOARD_FEATURE_T;
    case K_u:
      return DEFAULT_KEYBOARD_FEATURE_U;
    case K_v:
      return DEFAULT_KEYBOARD_FEATURE_V;
    case K_w:
      return DEFAULT_KEYBOARD_FEATURE_W;
    case K_x:
      return DEFAULT_KEYBOARD_FEATURE_X;
    case K_y:
      return DEFAULT_KEYBOARD_FEATURE_Y;
    case K_z:
      return DEFAULT_KEYBOARD_FEATURE_Z;
    case K_LEFTBRACE:
      return DEFAULT_KEYBOARD_FEATURE_LEFTBRACE;
    case K_PIPE:
      return DEFAULT_KEYBOARD_FEATURE_BAR;
    case K_RIGHTBRACE:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTBRACE;
    case K_TILDE:
      return DEFAULT_KEYBOARD_FEATURE_TILDE;
    case K_DELETE:
      return DEFAULT_KEYBOARD_FEATURE_DELETE;
    case K_KP0:
      return DEFAULT_KEYBOARD_FEATURE_KP0;
    case K_KP1:
      return DEFAULT_KEYBOARD_FEATURE_KP1;
    case K_KP2:
      return DEFAULT_KEYBOARD_FEATURE_KP2;
    case K_KP3:
      return DEFAULT_KEYBOARD_FEATURE_KP3;
    case K_KP4:
      return DEFAULT_KEYBOARD_FEATURE_KP4;
    case K_KP5:
      return DEFAULT_KEYBOARD_FEATURE_KP5;
    case K_KP6:
      return DEFAULT_KEYBOARD_FEATURE_KP6;
    case K_KP7:
      return DEFAULT_KEYBOARD_FEATURE_KP7;
    case K_KP8:
      return DEFAULT_KEYBOARD_FEATURE_KP8;
    case K_KP9:
      return DEFAULT_KEYBOARD_FEATURE_KP9;
    case K_KP_PERIOD:
      return DEFAULT_KEYBOARD_FEATURE_KPPERIOD;
    case K_KP_DIVIDE:
      return DEFAULT_KEYBOARD_FEATURE_KPDIVIDE;
    case K_KP_MULTIPLY:
      return DEFAULT_KEYBOARD_FEATURE_KPMULTIPLY;
    case K_KP_MINUS:
      return DEFAULT_KEYBOARD_FEATURE_KPMINUS;
    case K_KP_PLUS:
      return DEFAULT_KEYBOARD_FEATURE_KPPLUS;
    case K_KP_ENTER:
      return DEFAULT_KEYBOARD_FEATURE_KPENTER;
    case K_KP_EQUALS:
      return DEFAULT_KEYBOARD_FEATURE_KPEQUALS;
    case K_UP:
      return DEFAULT_KEYBOARD_FEATURE_UP;
    case K_DOWN:
      return DEFAULT_KEYBOARD_FEATURE_DOWN;
    case K_RIGHT:
      return DEFAULT_KEYBOARD_FEATURE_RIGHT;
    case K_LEFT:
      return DEFAULT_KEYBOARD_FEATURE_LEFT;
    case K_INSERT:
      return DEFAULT_KEYBOARD_FEATURE_INSERT;
    case K_HOME:
      return DEFAULT_KEYBOARD_FEATURE_HOME;
    case K_END:
      return DEFAULT_KEYBOARD_FEATURE_END;
    case K_PAGEUP:
      return DEFAULT_KEYBOARD_FEATURE_PAGEUP;
    case K_PAGEDOWN:
      return DEFAULT_KEYBOARD_FEATURE_PAGEDOWN;
    case K_F1:
      return DEFAULT_KEYBOARD_FEATURE_F1;
    case K_F2:
      return DEFAULT_KEYBOARD_FEATURE_F2;
    case K_F3:
      return DEFAULT_KEYBOARD_FEATURE_F3;
    case K_F4:
      return DEFAULT_KEYBOARD_FEATURE_F4;
    case K_F5:
      return DEFAULT_KEYBOARD_FEATURE_F5;
    case K_F6:
      return DEFAULT_KEYBOARD_FEATURE_F6;
    case K_F7:
      return DEFAULT_KEYBOARD_FEATURE_F7;
    case K_F8:
      return DEFAULT_KEYBOARD_FEATURE_F8;
    case K_F9:
      return DEFAULT_KEYBOARD_FEATURE_F9;
    case K_F10:
      return DEFAULT_KEYBOARD_FEATURE_F10;
    case K_F11:
      return DEFAULT_KEYBOARD_FEATURE_F11;
    case K_F12:
      return DEFAULT_KEYBOARD_FEATURE_F12;
    case K_F13:
      return DEFAULT_KEYBOARD_FEATURE_F13;
    case K_F14:
      return DEFAULT_KEYBOARD_FEATURE_F14;
    case K_F15:
      return DEFAULT_KEYBOARD_FEATURE_F15;
    case K_NUMLOCK:
      return DEFAULT_KEYBOARD_FEATURE_NUMLOCK;
    case K_CAPSLOCK:
      return DEFAULT_KEYBOARD_FEATURE_CAPSLOCK;
    case K_SCROLLOCK:
      return DEFAULT_KEYBOARD_FEATURE_SCROLLLOCK;
    case K_RSHIFT:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTSHIFT;
    case K_LSHIFT:
      return DEFAULT_KEYBOARD_FEATURE_LEFTSHIFT;
    case K_RCTRL:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTCTRL;
    case K_LCTRL:
      return DEFAULT_KEYBOARD_FEATURE_LEFTCTRL;
    case K_RALT:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTALT;
    case K_LALT:
      return DEFAULT_KEYBOARD_FEATURE_LEFTALT;
    case K_RMETA:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTMETA;
    case K_LMETA:
      return DEFAULT_KEYBOARD_FEATURE_LEFTMETA;
    case K_RSUPER:
      return DEFAULT_KEYBOARD_FEATURE_RIGHTSUPER;
    case K_LSUPER:
      return DEFAULT_KEYBOARD_FEATURE_LEFTSUPER;
    case K_MODE:
      return DEFAULT_KEYBOARD_FEATURE_MODE;
    case K_COMPOSE:
      return DEFAULT_KEYBOARD_FEATURE_COMPOSE;
    case K_HELP:
      return DEFAULT_KEYBOARD_FEATURE_HELP;
    case K_PRINT:
      return DEFAULT_KEYBOARD_FEATURE_PRINTSCREEN;
    case K_SYSREQ:
      return DEFAULT_KEYBOARD_FEATURE_SYSREQ;
    case K_BREAK:
      return DEFAULT_KEYBOARD_FEATURE_BREAK;
    case K_MENU:
      return DEFAULT_KEYBOARD_FEATURE_MENU;
    case K_POWER:
      return DEFAULT_KEYBOARD_FEATURE_POWER;
    case K_EURO:
      return DEFAULT_KEYBOARD_FEATURE_EURO;
    case K_UNDO:
      return DEFAULT_KEYBOARD_FEATURE_UNDO;
    case K_OEM_102:
      return DEFAULT_KEYBOARD_FEATURE_OEM_102;
    default:
      break;
  }

  return "";
}
