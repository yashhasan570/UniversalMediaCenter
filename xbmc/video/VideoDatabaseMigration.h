/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CDatabase;

namespace dbiplus
{
class Dataset;
}

namespace UNIVERSAL MEDIA CENTER::DATABASE::MIGRATION
{
/*!
 * \brief Repair the video versions and version types that migration steps 123 to 131 turned
 * into extras.
 * \param[in] db the video database
 * \param[in] ds a dataset of \p db
 * \param[in] ds2 another dataset of \p db
 * \param[in] iVersion the version the database is upgraded from
 */
void RepairVideoAssetTypesV154(CDatabase& db,
                               dbiplus::Dataset& ds,
                               dbiplus::Dataset& ds2,
                               int iVersion);
} // namespace UNIVERSAL MEDIA CENTER::DATABASE::MIGRATION
