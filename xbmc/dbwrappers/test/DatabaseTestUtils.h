/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "filesystem/SpecialProtocol.h"
#include "settings/AdvancedSettings.h"

#include <string>

//! \brief Where a test database lives: an sqlite file in special://temp/.
inline DatabaseSettings TestDatabaseSettings()
{
  DatabaseSettings settings;
  settings.type = "sqlite3";
  settings.host = CSpecialProtocol::TranslatePath("special://temp/");
  return settings;
}
