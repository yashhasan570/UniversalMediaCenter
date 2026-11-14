/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "IPlayback.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRealtimePlayback : public IPlayback
{
public:
  ~CRealtimePlayback() override = default;

  // implementation of IPlayback
  void Initialize() override {}
  void Quiesce() override {}
  void Deinitialize() override {}
  bool CanPause() const override { return false; }
  bool CanSeek() const override { return false; }
  unsigned int GetTimeMs() const override { return 0; }
  unsigned int GetTotalTimeMs() const override { return 0; }
  unsigned int GetCacheTimeMs() const override { return 0; }
  void SeekTimeMs(unsigned int timeMs) override {}
  double GetSpeed() const override { return 1.0; }
  void SetSpeed(double speedFactor) override {}
  void PauseAsync() override {}
  bool WaitForSavestates() override { return true; }
  void RequestAutosave() override {}
  std::string CreateSavestate(bool autosave, const std::string& savestatePath = "") override
  {
    return "";
  }
  bool LoadSavestate(const std::string& savestatePath) override { return false; }
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
