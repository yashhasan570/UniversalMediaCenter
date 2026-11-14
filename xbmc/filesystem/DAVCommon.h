/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

namespace tinyxml2
{
class XMLElement;
class XMLNode;
} // namespace tinyxml2

namespace XFILE
{
  class CDAVCommon
  {
    public:
      static bool ValueWithoutNamespace(const tinyxml2::XMLNode* node, const std::string& value);
      static std::string GetStatusTag(const tinyxml2::XMLElement* element);
  };
}
