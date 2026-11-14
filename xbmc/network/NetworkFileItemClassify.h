/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CFileItem;

namespace UNIVERSAL MEDIA CENTER::NETWORK
{

//! \brief Check whether an item is a an internet stream.
bool IsInternetStream(const CFileItem& item);

//! \brief Check whether an item is on a remote location.
bool IsRemote(const CFileItem& item);

//! \brief Check whether an item is on a streamed filesystem.
bool IsStreamedFilesystem(const CFileItem& item);
} // namespace UNIVERSAL MEDIA CENTER::NETWORK
