/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace JSONRPC
{
  class IClient
  {
  public:
    virtual ~IClient() = default;
    virtual int GetPermissionFlags() = 0;
    virtual int GetAnnouncementFlags() = 0;
    virtual bool SetAnnouncementFlags(int flags) = 0;
  };
}
