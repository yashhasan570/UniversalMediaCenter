/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "windowing/WinEvents.h"
#include "windowing/_events.h"

#include <deque>
#include <mutex>

class CWinEventsWasm : public IWinEvents
{
public:
  CWinEventsWasm();
  ~CWinEventsWasm() override;

  bool MessagePump() override;

  void MessagePush(const _Event& newEvent);

private:
  void ProcessProxyCallbacks();
  bool DispatchQueuedEvents();

  std::mutex m_mutex;
  std::deque<_Event> m_events;
};
