/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "platform/posix/PlatformPosix.h"

class CPlatformAndroid : public CPlatformPosix
{
  public:
    /**\brief C'tor */
    CPlatformAndroid() = default;

    /**\brief D'tor */
    ~CPlatformAndroid() override = default;

    bool InitStageOne() override;
    bool InitStageThree() override;
    void PlatformSyslog() override;
};
