/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "media/MediaType.h"

#include <gtest/gtest.h>

using namespace UNIVERSAL MEDIA CENTER::MEDIA;

namespace
{
constexpr UNIVERSAL MEDIA CENTER::MEDIA::TYPE FIRST{UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC};
constexpr UNIVERSAL MEDIA CENTER::MEDIA::TYPE LAST{UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_VERSION};

UNIVERSAL MEDIA CENTER::MEDIA::TYPE Next(UNIVERSAL MEDIA CENTER::MEDIA::TYPE type)
{
  return static_cast<UNIVERSAL MEDIA CENTER::MEDIA::TYPE>(static_cast<int>(type) + 1);
}
} // namespace

TEST(TestMediaType, EveryTypeReadsBackFromItsNames)
{
  for (UNIVERSAL MEDIA CENTER::MEDIA::TYPE type{FIRST}; type <= LAST; type = Next(type))
  {
    EXPECT_FALSE(NameOf(type).empty());
    EXPECT_EQ(MediaTypeFromName(NameOf(type)), type) << NameOf(type);
    EXPECT_EQ(MediaTypeFromName(PluralNameOf(type)), type) << PluralNameOf(type);
  }
}

TEST(TestMediaType, NamesAreTheStoredSpellings)
{
  EXPECT_EQ(NameOf(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION), "set");
  EXPECT_EQ(PluralNameOf(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION), "sets");
  EXPECT_EQ(NameOf(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW), "tvshow");
  EXPECT_EQ(PluralNameOf(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC), "music");
  EXPECT_EQ(NameOf(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE), "");
}

TEST(TestMediaType, FormatsAsItsName)
{
  const UNIVERSAL MEDIA CENTER::MEDIA::TYPE movie{UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE};
  EXPECT_EQ(fmt::format("{}", movie), "movie");
  EXPECT_EQ(fmt::format("{}", UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW), "tvshow");
  EXPECT_EQ(fmt::format("{:s}", UNIVERSAL MEDIA CENTER::MEDIA::TYPE::ALBUM), "album");
}

TEST(TestMediaType, AFacetOrUnknownNameIsNoType)
{
  EXPECT_EQ(MediaTypeFromName(""), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
  EXPECT_EQ(MediaTypeFromName("genre"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
  EXPECT_EQ(MediaTypeFromName("actor"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
  EXPECT_EQ(MediaTypeFromName("year"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
}

TEST(TestMediaType, ANameIsReadInAnyCase)
{
  EXPECT_EQ(MediaTypeFromName("Movie"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE);
  EXPECT_EQ(MediaTypeFromName("TVSHOWS"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW);
}

TEST(TestMediaType, OnlyTheStoredNameIsTheTypeExactly)
{
  for (UNIVERSAL MEDIA CENTER::MEDIA::TYPE type{FIRST}; type <= LAST; type = Next(type))
    EXPECT_EQ(MediaTypeOf(NameOf(type)), type) << NameOf(type);
  EXPECT_EQ(MediaTypeOf("movies"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
  EXPECT_EQ(MediaTypeOf("Movie"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
  EXPECT_EQ(MediaTypeOf("genre"), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
  EXPECT_EQ(MediaTypeOf(""), UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE);
}

TEST(TestMediaType, ContainersHoldOtherItems)
{
  EXPECT_TRUE(IsContainer(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::ALBUM));
  EXPECT_TRUE(IsContainer(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW));
  EXPECT_TRUE(IsContainer(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION));
  EXPECT_FALSE(IsContainer(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE));
  EXPECT_FALSE(IsContainer(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SONG));
  EXPECT_FALSE(IsContainer(UNIVERSAL MEDIA CENTER::MEDIA::TYPE::NONE));
}
