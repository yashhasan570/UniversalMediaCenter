/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "settings/lib/ISettingsMigrationStep.h"
#include "utils/TinyXML.h"

namespace UNIVERSAL MEDIA CENTER::SETTINGS
{

/*!
 * \brief Return the default list of migration functions.
 * \return The migration functions list.
 */
MigrationStepList BuildMigrationSteps();

} // namespace UNIVERSAL MEDIA CENTER::SETTINGS
