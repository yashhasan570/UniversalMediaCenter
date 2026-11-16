/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

namespace HTML
{
class CHTMLUtil
{
public:
  CHTMLUtil(void);
  virtual ~CHTMLUtil(void);
  static void RemoveTags(std::string& strHTML);
  static void ConvertHTMLToW(const std::wstring& strHTML, std::wstring& strStripped);
};
}
