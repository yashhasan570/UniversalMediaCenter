/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER::GAME
{
enum class RestoreResult
{
  Restored, // Target machine and media state restored.
  Rejected, // Target rejected; the previous running state is still valid.
  StateUncertain, // Machine or media state may be inconsistent.
};
} // namespace UNIVERSAL MEDIA CENTER::GAME
