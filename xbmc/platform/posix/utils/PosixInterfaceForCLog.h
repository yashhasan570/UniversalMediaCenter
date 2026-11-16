/*
 *  Copyright (C) 2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/IPlatformLog.h"

class CPosixInterfaceForCLog : public IPlatformLog
{
public:
  CPosixInterfaceForCLog() = default;
  virtual ~CPosixInterfaceForCLog() override = default;

  spdlog_filename_t GetLogFilename(const std::string& filename) const override { return filename; }
  void AddSinks(
      std::shared_ptr<spdlog::sinks::dist_sink<std::mutex>> distributionSink) const override;
};
