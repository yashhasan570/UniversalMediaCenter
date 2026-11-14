/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "threads/CriticalSection.h"
#include "threads/Event.h"
#include "threads/Thread.h"
#include "windowing/WinEvents.h"

#include <list>
#include <queue>
#include <string>
#include <vector>

class CWinEventsTVOS : public IWinEvents, public CThread
{
public:
  CWinEventsTVOS();
  ~CWinEventsTVOS();

  void MessagePush(_Event* newEvent);
  size_t GetQueueSize();

  bool MessagePump();

private:
  CCriticalSection m_eventsCond;
  std::list<_Event> m_events;
};
