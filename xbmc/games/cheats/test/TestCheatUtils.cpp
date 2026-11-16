/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "games/cheats/CheatUtils.h"

#include <gtest/gtest.h>

using namespace UNIVERSAL MEDIA CENTER::GAME;

TEST(TestCheatUtils, CheatFileNamePreservesTheExactGameBasename)
{
  EXPECT_EQ(CCheatUtils::GetCheatFileName("/games/Nintendo Game Boy/Frogger (USA).gb"),
            "Frogger (USA).cht");
  EXPECT_EQ(CCheatUtils::GetCheatFileName("/games/Game (Rev. 1).gb"), "Game (Rev. 1).cht");
  EXPECT_EQ(CCheatUtils::GetCheatFileName("game"), "game.cht");
  EXPECT_EQ(CCheatUtils::GetCheatFileName("zip://%2fgames%2fFrogger.zip/Frogger (USA).gb"),
            "Frogger (USA).cht");
}
