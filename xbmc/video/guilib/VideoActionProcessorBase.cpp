/*
 *  Copyright (C) 2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "VideoActionProcessorBase.h"

namespace KODI::VIDEO::GUILIB
{

bool CVideoActionProcessorBase::ProcessDefaultAction()
{
  return ProcessAction(GetDefaultAction());
}

bool CVideoActionProcessorBase::ProcessAction(Action action)
{
  m_userCancelled = false;

  return Process(action);
}

} // namespace KODI::VIDEO::GUILIB
