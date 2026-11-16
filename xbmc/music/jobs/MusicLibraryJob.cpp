/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "MusicLibraryJob.h"

#include "music/MusicDatabase.h"

CMusicLibraryJob::CMusicLibraryJob() = default;

CMusicLibraryJob::~CMusicLibraryJob() = default;

bool CMusicLibraryJob::DoWork()
{
  CMusicDatabase db;
  if (!db.Open())
    return false;

  return Work(db);
}
