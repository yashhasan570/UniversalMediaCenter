/*
 *  Copyright (C) 2005-2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <memory>

class CAppParams;

class CAppEnvironment
{
public:
  static void SetUp(const std::shared_ptr<CAppParams>& appParams);
  static void TearDown();
};
