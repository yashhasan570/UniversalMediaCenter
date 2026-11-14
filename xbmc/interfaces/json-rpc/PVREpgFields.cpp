/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "PVREpgFields.h"

#include "addons/kodi-dev-kit/include/kodi/c-api/addon-instance/pvr/pvr_epg.h" // EPG_STRING_TOKEN_SEPARATOR
#include "utils/StringUtils.h"
#include "utils/Variant.h"

namespace JSONRPC
{

CVariant TranslateEpgCast(const std::string& cast)
{
  CVariant result(CVariant::VariantTypeArray);

  int order{0};
  for (const auto& name : StringUtils::Split(cast, EPG_STRING_TOKEN_SEPARATOR))
  {
    if (name.empty())
      continue;

    CVariant actor;
    actor["name"] = name;
    actor["role"] = "";
    actor["order"] = order++;
    result.push_back(std::move(actor));
  }

  return result;
}

} // namespace JSONRPC
