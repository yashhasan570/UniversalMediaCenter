/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "test/TestUtils.h"
#include "utils/ScraperParser.h"

#include <gtest/gtest.h>

TEST(TestScraperParser, General)
{
  CScraperParser a;

  a.Clear();
  EXPECT_TRUE(a.Load(_REF_FILE_PATH("/addons/metadata.local/local.xml")));

  EXPECT_STREQ("UTF-8", a.GetSearchStringEncoding().c_str());
}
