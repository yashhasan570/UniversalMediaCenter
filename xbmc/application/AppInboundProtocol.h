/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "threads/CriticalSection.h"
#include "windowing/_events.h"

#include <deque>

class CApplication;

class CAppInboundProtocol
{
  friend class CApplication;

public:
  CAppInboundProtocol(CApplication& app);
  bool OnEvent(const _Event& newEvent);
  void SetRenderGUI(bool renderGUI);
  void Close();

protected:
  void HandleEvents();

  bool m_closed = false;
  CApplication &m_pApp;
  std::deque<_Event> m_portEvents;
  CCriticalSection m_portSection;
};
