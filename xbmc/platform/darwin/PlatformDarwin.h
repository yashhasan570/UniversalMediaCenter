/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "platform/posix/PlatformPosix.h"

class CPlatformDarwin : public CPlatformPosix
{
  public:
    /**\brief C'tor */
    CPlatformDarwin() = default;

    /**\brief D'tor */
    ~CPlatformDarwin() override = default;

    bool InitStageOne() override;
};
