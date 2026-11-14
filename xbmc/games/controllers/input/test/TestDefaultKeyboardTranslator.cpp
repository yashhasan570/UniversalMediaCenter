/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ServiceBroker.h"
#include "addons/AddonManager.h"
#include "addons/addoninfo/AddonType.h"
#include "games/controllers/Controller.h"
#include "games/controllers/ControllerIDs.h"
#include "games/controllers/input/DefaultKeyboardTranslator.h"
#include "games/controllers/input/PhysicalFeature.h"

#include <gtest/gtest.h>

using namespace UNIVERSAL MEDIA CENTER;
using namespace GAME;

namespace
{
// Helper functions
KEYBOARD::Key GetKeycode(KEYBOARD::Key keysym,
                             const ControllerPtr& controller,
                             unsigned int& count)
{
  KEYBOARD::KeyName keyName = CDefaultKeyboardTranslator::TranslateKeycode(keysym);
  ++count;
  return controller->GetFeature(keyName).Keycode();
}

const GAME::ControllerPtr GetController()
{
  ADDON::CAddonMgr& addonManager = CServiceBroker::GetAddonMgr();

  // Load add-on info
  ADDON::AddonPtr addon;
  EXPECT_TRUE(addonManager.GetAddon(DEFAULT_KEYBOARD_ID, addon, ADDON::AddonType::GAME_CONTROLLER,
                                    ADDON::OnlyEnabled::CHOICE_YES));

  // Convert to game controller
  GAME::ControllerPtr controller = std::static_pointer_cast<GAME::CController>(addon);
  EXPECT_NE(controller.get(), nullptr);
  EXPECT_EQ(controller->ID(), DEFAULT_KEYBOARD_ID);

  // Load controller profile
  EXPECT_TRUE(controller->LoadLayout());
  EXPECT_EQ(controller->Features().size(), 140);

  return controller;
}
} // namespace

TEST(TestDefaultKeyboardTranslator, TranslateKeycode)
{
  GAME::ControllerPtr controller = GetController();

  //
  // Spec: Should translate all keyboard keys
  //
  unsigned int count = 0;

  EXPECT_EQ(GetKeycode(K_BACKSPACE, controller, count), K_BACKSPACE);
  EXPECT_EQ(GetKeycode(K_TAB, controller, count), K_TAB);
  EXPECT_EQ(GetKeycode(K_CLEAR, controller, count), K_CLEAR);
  EXPECT_EQ(GetKeycode(K_RETURN, controller, count), K_RETURN);
  EXPECT_EQ(GetKeycode(K_PAUSE, controller, count), K_PAUSE);
  EXPECT_EQ(GetKeycode(K_ESCAPE, controller, count), K_ESCAPE);
  EXPECT_EQ(GetKeycode(K_SPACE, controller, count), K_SPACE);
  EXPECT_EQ(GetKeycode(K_EXCLAIM, controller, count), K_EXCLAIM);
  EXPECT_EQ(GetKeycode(K_QUOTEDBL, controller, count), K_QUOTEDBL);
  EXPECT_EQ(GetKeycode(K_HASH, controller, count), K_HASH);
  EXPECT_EQ(GetKeycode(K_DOLLAR, controller, count), K_DOLLAR);
  EXPECT_EQ(GetKeycode(K_AMPERSAND, controller, count), K_AMPERSAND);
  EXPECT_EQ(GetKeycode(K_QUOTE, controller, count), K_QUOTE);
  EXPECT_EQ(GetKeycode(K_LEFTPAREN, controller, count), K_LEFTPAREN);
  EXPECT_EQ(GetKeycode(K_RIGHTPAREN, controller, count), K_RIGHTPAREN);
  EXPECT_EQ(GetKeycode(K_ASTERISK, controller, count), K_ASTERISK);
  EXPECT_EQ(GetKeycode(K_PLUS, controller, count), K_PLUS);
  EXPECT_EQ(GetKeycode(K_COMMA, controller, count), K_COMMA);
  EXPECT_EQ(GetKeycode(K_MINUS, controller, count), K_MINUS);
  EXPECT_EQ(GetKeycode(K_PERIOD, controller, count), K_PERIOD);
  EXPECT_EQ(GetKeycode(K_SLASH, controller, count), K_SLASH);
  EXPECT_EQ(GetKeycode(K_0, controller, count), K_0);
  EXPECT_EQ(GetKeycode(K_1, controller, count), K_1);
  EXPECT_EQ(GetKeycode(K_2, controller, count), K_2);
  EXPECT_EQ(GetKeycode(K_3, controller, count), K_3);
  EXPECT_EQ(GetKeycode(K_4, controller, count), K_4);
  EXPECT_EQ(GetKeycode(K_5, controller, count), K_5);
  EXPECT_EQ(GetKeycode(K_6, controller, count), K_6);
  EXPECT_EQ(GetKeycode(K_7, controller, count), K_7);
  EXPECT_EQ(GetKeycode(K_8, controller, count), K_8);
  EXPECT_EQ(GetKeycode(K_9, controller, count), K_9);
  EXPECT_EQ(GetKeycode(K_COLON, controller, count), K_COLON);
  EXPECT_EQ(GetKeycode(K_SEMICOLON, controller, count), K_SEMICOLON);
  EXPECT_EQ(GetKeycode(K_LESS, controller, count), K_LESS);
  EXPECT_EQ(GetKeycode(K_EQUALS, controller, count), K_EQUALS);
  EXPECT_EQ(GetKeycode(K_GREATER, controller, count), K_GREATER);
  EXPECT_EQ(GetKeycode(K_QUESTION, controller, count), K_QUESTION);
  EXPECT_EQ(GetKeycode(K_AT, controller, count), K_AT);
  EXPECT_EQ(GetKeycode(K_LEFTBRACKET, controller, count), K_LEFTBRACKET);
  EXPECT_EQ(GetKeycode(K_BACKSLASH, controller, count), K_BACKSLASH);
  EXPECT_EQ(GetKeycode(K_RIGHTBRACKET, controller, count), K_RIGHTBRACKET);
  EXPECT_EQ(GetKeycode(K_CARET, controller, count), K_CARET);
  EXPECT_EQ(GetKeycode(K_UNDERSCORE, controller, count), K_UNDERSCORE);
  EXPECT_EQ(GetKeycode(K_BACKQUOTE, controller, count), K_BACKQUOTE);
  EXPECT_EQ(GetKeycode(K_a, controller, count), K_a);
  EXPECT_EQ(GetKeycode(K_b, controller, count), K_b);
  EXPECT_EQ(GetKeycode(K_c, controller, count), K_c);
  EXPECT_EQ(GetKeycode(K_d, controller, count), K_d);
  EXPECT_EQ(GetKeycode(K_e, controller, count), K_e);
  EXPECT_EQ(GetKeycode(K_f, controller, count), K_f);
  EXPECT_EQ(GetKeycode(K_g, controller, count), K_g);
  EXPECT_EQ(GetKeycode(K_h, controller, count), K_h);
  EXPECT_EQ(GetKeycode(K_i, controller, count), K_i);
  EXPECT_EQ(GetKeycode(K_j, controller, count), K_j);
  EXPECT_EQ(GetKeycode(K_k, controller, count), K_k);
  EXPECT_EQ(GetKeycode(K_l, controller, count), K_l);
  EXPECT_EQ(GetKeycode(K_m, controller, count), K_m);
  EXPECT_EQ(GetKeycode(K_n, controller, count), K_n);
  EXPECT_EQ(GetKeycode(K_o, controller, count), K_o);
  EXPECT_EQ(GetKeycode(K_p, controller, count), K_p);
  EXPECT_EQ(GetKeycode(K_q, controller, count), K_q);
  EXPECT_EQ(GetKeycode(K_r, controller, count), K_r);
  EXPECT_EQ(GetKeycode(K_s, controller, count), K_s);
  EXPECT_EQ(GetKeycode(K_t, controller, count), K_t);
  EXPECT_EQ(GetKeycode(K_u, controller, count), K_u);
  EXPECT_EQ(GetKeycode(K_v, controller, count), K_v);
  EXPECT_EQ(GetKeycode(K_w, controller, count), K_w);
  EXPECT_EQ(GetKeycode(K_x, controller, count), K_x);
  EXPECT_EQ(GetKeycode(K_y, controller, count), K_y);
  EXPECT_EQ(GetKeycode(K_z, controller, count), K_z);
  EXPECT_EQ(GetKeycode(K_LEFTBRACE, controller, count), K_LEFTBRACE);
  EXPECT_EQ(GetKeycode(K_PIPE, controller, count), K_PIPE);
  EXPECT_EQ(GetKeycode(K_RIGHTBRACE, controller, count), K_RIGHTBRACE);
  EXPECT_EQ(GetKeycode(K_TILDE, controller, count), K_TILDE);
  EXPECT_EQ(GetKeycode(K_DELETE, controller, count), K_DELETE);
  EXPECT_EQ(GetKeycode(K_KP0, controller, count), K_KP0);
  EXPECT_EQ(GetKeycode(K_KP1, controller, count), K_KP1);
  EXPECT_EQ(GetKeycode(K_KP2, controller, count), K_KP2);
  EXPECT_EQ(GetKeycode(K_KP3, controller, count), K_KP3);
  EXPECT_EQ(GetKeycode(K_KP4, controller, count), K_KP4);
  EXPECT_EQ(GetKeycode(K_KP5, controller, count), K_KP5);
  EXPECT_EQ(GetKeycode(K_KP6, controller, count), K_KP6);
  EXPECT_EQ(GetKeycode(K_KP7, controller, count), K_KP7);
  EXPECT_EQ(GetKeycode(K_KP8, controller, count), K_KP8);
  EXPECT_EQ(GetKeycode(K_KP9, controller, count), K_KP9);
  EXPECT_EQ(GetKeycode(K_KP_PERIOD, controller, count), K_KP_PERIOD);
  EXPECT_EQ(GetKeycode(K_KP_DIVIDE, controller, count), K_KP_DIVIDE);
  EXPECT_EQ(GetKeycode(K_KP_MULTIPLY, controller, count), K_KP_MULTIPLY);
  EXPECT_EQ(GetKeycode(K_KP_MINUS, controller, count), K_KP_MINUS);
  EXPECT_EQ(GetKeycode(K_KP_PLUS, controller, count), K_KP_PLUS);
  EXPECT_EQ(GetKeycode(K_KP_ENTER, controller, count), K_KP_ENTER);
  EXPECT_EQ(GetKeycode(K_KP_EQUALS, controller, count), K_KP_EQUALS);
  EXPECT_EQ(GetKeycode(K_UP, controller, count), K_UP);
  EXPECT_EQ(GetKeycode(K_DOWN, controller, count), K_DOWN);
  EXPECT_EQ(GetKeycode(K_RIGHT, controller, count), K_RIGHT);
  EXPECT_EQ(GetKeycode(K_LEFT, controller, count), K_LEFT);
  EXPECT_EQ(GetKeycode(K_INSERT, controller, count), K_INSERT);
  EXPECT_EQ(GetKeycode(K_HOME, controller, count), K_HOME);
  EXPECT_EQ(GetKeycode(K_END, controller, count), K_END);
  EXPECT_EQ(GetKeycode(K_PAGEUP, controller, count), K_PAGEUP);
  EXPECT_EQ(GetKeycode(K_PAGEDOWN, controller, count), K_PAGEDOWN);
  EXPECT_EQ(GetKeycode(K_F1, controller, count), K_F1);
  EXPECT_EQ(GetKeycode(K_F2, controller, count), K_F2);
  EXPECT_EQ(GetKeycode(K_F3, controller, count), K_F3);
  EXPECT_EQ(GetKeycode(K_F4, controller, count), K_F4);
  EXPECT_EQ(GetKeycode(K_F5, controller, count), K_F5);
  EXPECT_EQ(GetKeycode(K_F6, controller, count), K_F6);
  EXPECT_EQ(GetKeycode(K_F7, controller, count), K_F7);
  EXPECT_EQ(GetKeycode(K_F8, controller, count), K_F8);
  EXPECT_EQ(GetKeycode(K_F9, controller, count), K_F9);
  EXPECT_EQ(GetKeycode(K_F10, controller, count), K_F10);
  EXPECT_EQ(GetKeycode(K_F11, controller, count), K_F11);
  EXPECT_EQ(GetKeycode(K_F12, controller, count), K_F12);
  EXPECT_EQ(GetKeycode(K_F13, controller, count), K_F13);
  EXPECT_EQ(GetKeycode(K_F14, controller, count), K_F14);
  EXPECT_EQ(GetKeycode(K_F15, controller, count), K_F15);
  EXPECT_EQ(GetKeycode(K_NUMLOCK, controller, count), K_NUMLOCK);
  EXPECT_EQ(GetKeycode(K_CAPSLOCK, controller, count), K_CAPSLOCK);
  EXPECT_EQ(GetKeycode(K_SCROLLOCK, controller, count), K_SCROLLOCK);
  EXPECT_EQ(GetKeycode(K_LSHIFT, controller, count), K_LSHIFT);
  EXPECT_EQ(GetKeycode(K_RSHIFT, controller, count), K_RSHIFT);
  EXPECT_EQ(GetKeycode(K_LCTRL, controller, count), K_LCTRL);
  EXPECT_EQ(GetKeycode(K_RCTRL, controller, count), K_RCTRL);
  EXPECT_EQ(GetKeycode(K_LALT, controller, count), K_LALT);
  EXPECT_EQ(GetKeycode(K_RALT, controller, count), K_RALT);
  EXPECT_EQ(GetKeycode(K_LMETA, controller, count), K_LMETA);
  EXPECT_EQ(GetKeycode(K_RMETA, controller, count), K_RMETA);
  EXPECT_EQ(GetKeycode(K_LSUPER, controller, count), K_LSUPER);
  EXPECT_EQ(GetKeycode(K_RSUPER, controller, count), K_RSUPER);
  EXPECT_EQ(GetKeycode(K_MODE, controller, count), K_MODE);
  EXPECT_EQ(GetKeycode(K_COMPOSE, controller, count), K_COMPOSE);
  EXPECT_EQ(GetKeycode(K_HELP, controller, count), K_HELP);
  EXPECT_EQ(GetKeycode(K_PRINT, controller, count), K_PRINT);
  EXPECT_EQ(GetKeycode(K_SYSREQ, controller, count), K_SYSREQ);
  EXPECT_EQ(GetKeycode(K_BREAK, controller, count), K_BREAK);
  EXPECT_EQ(GetKeycode(K_MENU, controller, count), K_MENU);
  EXPECT_EQ(GetKeycode(K_POWER, controller, count), K_POWER);
  EXPECT_EQ(GetKeycode(K_EURO, controller, count), K_EURO);
  EXPECT_EQ(GetKeycode(K_UNDO, controller, count), K_UNDO);
  EXPECT_EQ(GetKeycode(K_OEM_102, controller, count), K_OEM_102);

  EXPECT_EQ(count, 140);
}
