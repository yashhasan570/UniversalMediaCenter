/*
 *  Copyright (C) 2018-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "EventLockHandle.h"

using namespace PERIPHERALS;

CEventLockHandle::CEventLockHandle(IEventLockCallback& callback) : m_callback(callback)
{
}

CEventLockHandle::~CEventLockHandle(void)
{
  m_callback.ReleaseLock(*this);
}
