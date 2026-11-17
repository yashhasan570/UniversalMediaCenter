/*
 *  Copyright (C) 2013-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "JSONRPC.h"

class CVariant;

namespace JSONRPC
{
  class CTextureOperations
  {
  public:
    static JSONRPC_STATUS GetTextures(const CVariant& parameterObject, CVariant& result);
    static JSONRPC_STATUS RemoveTexture(const CVariant& parameterObject, CVariant& result);
  };
}
