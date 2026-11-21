/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "cores/VideoPlayer/RadioRDSLanguages.h"
#include "language/LanguageTag.h"

#include <string>

#include <gtest/gtest.h>

using UNIVERSAL MEDIA CENTER::LANGUAGE::CLanguageTag;

namespace
{

// A broadcaster names a language by index, so a cell that names nothing readable takes a
// language off the air entirely, with nothing to log and nobody to ask
TEST(TestRadioRDSLanguages, EveryAssignedIndexNamesALanguage)
{
  for (unsigned int index = 0; index < UNIVERSAL MEDIA CENTER::RDS::LANGUAGE_INDEX_COUNT; ++index)
  {
    const std::string_view code{UNIVERSAL MEDIA CENTER::RDS::LanguageCode(index)};
    if (code.empty())
      continue;

    const CLanguageTag language{UNIVERSAL MEDIA CENTER::RDS::Language(index)};
    EXPECT_TRUE(language.IsValid())
        << "index " << index << " holds '" << code << "', which names no language";
    EXPECT_FALSE(language.IsUndetermined()) << "index " << index << " holds '" << code << "'";
  }
}

TEST(TestRadioRDSLanguages, AnIndexNamingNoLanguageIsUndetermined)
{
  // 0x00 is reserved, as is the block from 0x2C to 0x44
  for (const unsigned int index : {0x00U, 0x2CU, 0x3FU, 0x44U})
  {
    EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(index).empty()) << "index " << index;
    EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::Language(index).IsUndetermined()) << "index " << index;
  }

  // and so is anything past the table
  EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(UNIVERSAL MEDIA CENTER::RDS::LANGUAGE_INDEX_COUNT).empty());
  EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::Language(UNIVERSAL MEDIA CENTER::RDS::LANGUAGE_INDEX_COUNT).IsUndetermined());
  EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::Language(0xFFFFU).IsUndetermined());
}

// Cells pinned against EBU Tech 3244 Annex J. From 0x45 the standard runs reverse-alphabetically
// by English name, which fixes which language each index names independently of the code
// printed for it.
TEST(TestRadioRDSLanguages, NamesTheLanguageTheStandardAssignsToAnIndex)
{
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x09).ToString(), "en");
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x08).ToString(), "de");
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x0F).ToString(), "fr");

  // 0x0E is Faroese, whose ISO 639-2 code is fao
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(0x0E), "fao");
  EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::Language(0x0E).Matches(CLanguageTag::Parse("fo")));

  // 0x23 is Romansh, whose ISO 639-2 code is roh; rom is Romany
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(0x23), "roh");
  EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::Language(0x23).Matches(CLanguageTag::Parse("rm")));

  // 0x61 is Malay, whose ISO 639-2/B code is may
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(0x61), "may");
  EXPECT_TRUE(UNIVERSAL MEDIA CENTER::RDS::Language(0x61).Matches(CLanguageTag::Parse("ms")));

  // 0x64 is Laotian, between Macedonian and Korean in the reverse-alphabetical run
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(0x64), "lao");
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x64).ToString(), "lo");

  // The standard names some languages twice, once in each block, and the two agree
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x22), UNIVERSAL MEDIA CENTER::RDS::Language(0x60)); // Romanian
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x1D), UNIVERSAL MEDIA CENTER::RDS::Language(0x2A)); // Dutch, as dut and nld
}

// The standard prints ISO 639-2/B codes, two of which ISO has since withdrawn. A withdrawn code
// names nothing, so the table holds the code Universal Media Center reads as the same language.
TEST(TestRadioRDSLanguages, HoldsTheCodeUniversal Media CenterReadsWhereTheStandardPrintsAWithdrawnOne)
{
  // 0x54 is Serbo-Croat, printed as scc, withdrawn 2008-06-28. Serbian has its own index at
  // 0x24, so the cell holds scr, Universal Media Center's code for Serbo-Croatian, not srp
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(0x54), "scr");
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x54).ToString(), "sh");
  EXPECT_NE(UNIVERSAL MEDIA CENTER::RDS::Language(0x54), UNIVERSAL MEDIA CENTER::RDS::Language(0x24));

  // 0x60 is Moldavian, printed as mol, withdrawn as a language distinct from Romanian
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::LanguageCode(0x60), "rum");
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x60).ToString(), "ro");
}

// The standard names two languages ISO 639-2 has no code for, and ISO 639-3 has
TEST(TestRadioRDSLanguages, HoldsAnIso6393CodeWhereIso6392HasNone)
{
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x55).ToString(), "rue"); // Rusyn
  EXPECT_EQ(UNIVERSAL MEDIA CENTER::RDS::Language(0x73).ToString(), "prs"); // Dari
}

} // unnamed namespace
