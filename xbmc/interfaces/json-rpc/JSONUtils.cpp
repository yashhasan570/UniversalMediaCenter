/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JSONUtils.h"

#include "XBDateTime.h"

namespace JSONRPC
{

void CJSONUtils::SetFromDBDate(const CVariant& jsonDate, CDateTime& date)
{
  if (!jsonDate.isString())
    return;

  if (jsonDate.empty())
    date.Reset();
  else
    date.SetFromDBDate(jsonDate.asString());
}

void CJSONUtils::SetFromDBDateTime(const CVariant& jsonDate, CDateTime& date)
{
  if (!jsonDate.isString())
    return;

  if (jsonDate.empty())
    date.Reset();
  else
    date.SetFromDBDateTime(jsonDate.asString());
}

} // namespace JSONRPC
