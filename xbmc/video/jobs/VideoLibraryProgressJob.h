/*
 *  Copyright (C) 2014-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/ProgressJob.h"
#include "video/jobs/VideoLibraryJob.h"

/*!
 \brief Combined base implementation of a video library job with a progress bar.
 */
class CVideoLibraryProgressJob : public CProgressJob, public CVideoLibraryJob
{
public:
  ~CVideoLibraryProgressJob() override;

  // implementation of CJob
  bool DoWork() override;
  const char* GetType() const override { return "CVideoLibraryProgressJob"; }

protected:
  explicit CVideoLibraryProgressJob(CGUIDialogProgressBarHandle* progressBar);
};
