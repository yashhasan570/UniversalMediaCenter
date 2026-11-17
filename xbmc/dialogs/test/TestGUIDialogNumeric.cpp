/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "dialogs/GUIDialogNumeric.h"
#include "input/actions/Action.h"
#include "input/actions/ActionIDs.h"

#include <gtest/gtest.h>

TEST(TestGUIDialogNumeric, BackspaceInTheSecondsRemovesASecondsDigit)
{
  UNIVERSAL MEDIA CENTER::TIME::SystemTime initial{};
  initial.hour = 1;
  initial.minute = 42;

  CGUIDialogNumeric dialog;
  dialog.SetMode(UNIVERSAL MEDIA CENTER::DIALOGS::NUMERIC_MODE::TIME_SECONDS, initial);

  dialog.OnAction(CAction(ACTION_NEXT_ITEM));
  dialog.OnAction(CAction(ACTION_NEXT_ITEM));
  dialog.OnAction(CAction(REMOTE_3));
  dialog.OnAction(CAction(ACTION_BACKSPACE));

  const UNIVERSAL MEDIA CENTER::TIME::SystemTime time{dialog.GetOutput()};
  EXPECT_EQ(1, time.hour);
  EXPECT_EQ(42, time.minute);
  EXPECT_EQ(0, time.second);
}

TEST(TestGUIDialogNumeric, TheSecondsCanBeReachedAfterTextInput)
{
#if defined(TARGET_DARWIN_OSX) || defined(TARGET_FREEBSD)
  GTEST_SKIP() << "mktime does not handle dates before 1900 on this platform";
#endif

  CGUIDialogNumeric dialog;
  dialog.SetMode(UNIVERSAL MEDIA CENTER::DIALOGS::NUMERIC_MODE::TIME_SECONDS, "01:42:00");

  dialog.OnAction(CAction(ACTION_NEXT_ITEM));
  dialog.OnAction(CAction(ACTION_NEXT_ITEM));
  dialog.OnAction(CAction(REMOTE_3));

  const UNIVERSAL MEDIA CENTER::TIME::SystemTime time{dialog.GetOutput()};
  EXPECT_EQ(42, time.minute);
  EXPECT_EQ(3, time.second);
}
