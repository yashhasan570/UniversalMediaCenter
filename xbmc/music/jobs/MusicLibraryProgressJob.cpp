/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "MusicLibraryProgressJob.h"

CMusicLibraryProgressJob::CMusicLibraryProgressJob(CGUIDialogProgressBarHandle* progressBar)
  : CProgressJob(progressBar)
{ }

CMusicLibraryProgressJob::~CMusicLibraryProgressJob() = default;

bool CMusicLibraryProgressJob::DoWork()
{
  bool result = CMusicLibraryJob::DoWork();

  MarkFinished();

  return result;
}
