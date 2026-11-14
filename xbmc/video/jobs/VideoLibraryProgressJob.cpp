/*
 *  Copyright (C) 2014-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "VideoLibraryProgressJob.h"

CVideoLibraryProgressJob::CVideoLibraryProgressJob(CGUIDialogProgressBarHandle* progressBar)
  : CProgressJob(progressBar)
{ }

CVideoLibraryProgressJob::~CVideoLibraryProgressJob() = default;

bool CVideoLibraryProgressJob::DoWork()
{
  bool result = CVideoLibraryJob::DoWork();

  MarkFinished();

  return result;
}
