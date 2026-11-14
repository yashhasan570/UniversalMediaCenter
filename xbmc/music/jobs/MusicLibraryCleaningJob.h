/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "music/jobs/MusicLibraryProgressJob.h"

#include <set>

/*!
 \brief Music library job implementation for cleaning the video library.
*/
class CMusicLibraryCleaningJob : public CMusicLibraryProgressJob
{
public:
  /*!
   \brief Creates a new music library cleaning job.
   \param[in] progressDialog Progress dialog to be used to display the cleaning progress
  */
  CMusicLibraryCleaningJob(CGUIDialogProgress* progressDialog);
  ~CMusicLibraryCleaningJob() override;

  // specialization of CJob
  const char *GetType() const override { return "MusicLibraryCleaningJob"; }
  bool Equals(const CJob* job) const override;

protected:
  // implementation of CMusicLibraryJob
  bool Work(CMusicDatabase &db) override;

private:

};
