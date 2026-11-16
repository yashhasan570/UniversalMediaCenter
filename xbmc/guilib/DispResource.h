/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

// interface for registering into windowing
// to get notified about display events
// interface only, does not control lifetime of the object
class IDispResource
{
public:
  virtual ~IDispResource() = default;

  virtual void OnLostDisplay() {}
  virtual void OnResetDisplay() {}
  virtual void OnAppFocusChange(bool focus) {}
};

// interface used by clients to register into render loop
// interface only, does not control lifetime of the object
class IRenderLoop
{
public:
  virtual ~IRenderLoop() = default;

  virtual void FrameMove() = 0;
};
