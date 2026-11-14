/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "utils/AliasShortcutUtils.h"
#include "filesystem/File.h"
#include "test/TestUtils.h"

#if defined(TARGET_DARWIN_OSX)
#include "platform/darwin/DarwinUtils.h"
#endif
#include <gtest/gtest.h>

TEST(TestAliasShortcutUtils, IsAliasShortcut)
{
  XFILE::CFile *tmpFile = _CREATETEMPFILE("noaliastest");
  std::string noalias = _TEMPFILEPATH(tmpFile);

#if defined(TARGET_DARWIN_OSX)
  XFILE::CFile *aliasDestFile = _CREATETEMPFILE("aliastest");
  std::string alias = _TEMPFILEPATH(aliasDestFile);

  //we only need the path here so delete the alias file
  //which will be recreated as shortcut later:
  _DELETETEMPFILE(aliasDestFile);

  // create alias from a pointing to /Volumes
  CDarwinUtils::CreateAliasShortcut(alias, "/Volumes");
  EXPECT_TRUE(IsAliasShortcut(alias, true));
  XFILE::CFile::Delete(alias);

  // volumes is not a shortcut but a dir
  EXPECT_FALSE(IsAliasShortcut("/Volumes", true));
#endif

  // a regular file is not a shortcut
  EXPECT_FALSE(IsAliasShortcut(noalias, false));
  _DELETETEMPFILE(tmpFile);

  // empty string is not an alias
  std::string emptyString;
  EXPECT_FALSE(IsAliasShortcut(emptyString, false));

  // non-existent file is no alias
  std::string nonExistingFile="/IDontExistsNormally/somefile.txt";
  EXPECT_FALSE(IsAliasShortcut(nonExistingFile, false));
}

TEST(TestAliasShortcutUtils, TranslateAliasShortcut)
{
  XFILE::CFile *tmpFile = _CREATETEMPFILE("noaliastest");
  std::string noalias = _TEMPFILEPATH(tmpFile);
  std::string noaliastemp = noalias;

#if defined(TARGET_DARWIN_OSX)
  XFILE::CFile *aliasDestFile = _CREATETEMPFILE("aliastest");
  std::string alias = _TEMPFILEPATH(aliasDestFile);

  //we only need the path here so delete the alias file
  //which will be recreated as shortcut later:
  _DELETETEMPFILE(aliasDestFile);

  // create alias from a pointing to /Volumes
  CDarwinUtils::CreateAliasShortcut(alias, "/Volumes");

  // resolve the shortcut
  TranslateAliasShortcut(alias);
  EXPECT_STREQ("/Volumes", alias.c_str());
  XFILE::CFile::Delete(alias);
#endif

  // translating a non-shortcut url should result in no change...
  TranslateAliasShortcut(noaliastemp);
  EXPECT_STREQ(noaliastemp.c_str(), noalias.c_str());
  _DELETETEMPFILE(tmpFile);

  //translate empty should stay empty
  std::string emptyString;
  TranslateAliasShortcut(emptyString);
  EXPECT_STREQ("", emptyString.c_str());

  // translate non-existent file should result in no change...
  std::string nonExistingFile="/IDontExistsNormally/somefile.txt";
  std::string resolvedNonExistingFile=nonExistingFile;
  TranslateAliasShortcut(resolvedNonExistingFile);
  EXPECT_STREQ(resolvedNonExistingFile.c_str(), nonExistingFile.c_str());
}
