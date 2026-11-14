/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "media/MediaSection.h"

#include <gtest/gtest.h>

using namespace UNIVERSAL MEDIA CENTER::MEDIA;

TEST(TestMediaSection, EverySectionReadsBackFromItsName)
{
  for (const MediaSection section : MEDIA_SECTIONS)
    EXPECT_EQ(MediaSectionFromName(NameOf(section)), section) << NameOf(section);
}

TEST(TestMediaSection, TheOlderSpellingsNameTheirSection)
{
  EXPECT_EQ(MediaSectionFromName("videos"), MediaSection::VIDEO);
  EXPECT_EQ(MediaSectionFromName("myprograms"), MediaSection::PROGRAMS);
}

TEST(TestMediaSection, AnyOtherTextNamesNoSection)
{
  EXPECT_FALSE(MediaSectionFromName(""));
  EXPECT_FALSE(MediaSectionFromName("movie"));
  EXPECT_FALSE(MediaSectionFromName("Video"));
}
