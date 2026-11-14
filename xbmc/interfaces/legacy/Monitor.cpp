/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Monitor.h"

#include "threads/SystemClock.h"

#include <algorithm>
#include <math.h>

using namespace std::chrono_literals;

namespace Addon
{
  namespace 
  {
    Monitor::Monitor(): abortEvent(true)
    {
      _TRACE;
      if (languageHook)
      {
        Id = languageHook->GetAddonId();
        invokerId = languageHook->GetInvokerId();
        languageHook->RegisterMonitorCallback(this);
      }
    }

    void Monitor::AbortNotify()
    {
      _TRACE;
      abortEvent.Set();
    }

    bool Monitor::waitForAbort(double timeout)
    {
      _TRACE;
      int timeoutMS = ceil(timeout * 1000);
      XbmcThreads::EndTime<> endTime{std::chrono::milliseconds(timeoutMS)};

      if (timeoutMS <= 0)
        endTime.SetInfinite();

      while (!endTime.IsTimePast())
      {
        {
          DelayedCallGuard dg(languageHook);
          auto timeout = std::min(endTime.GetTimeLeft(), 100ms);
          if (abortEvent.Wait(timeout))
            return true;
        }
        if (languageHook)
          languageHook->MakePendingCalls();
      }
      return false;
    }

    bool Monitor::abortRequested()
    {
      _TRACE;
      return abortEvent.Signaled();
    }

    Monitor::~Monitor()
    {
      _TRACE;
      deallocating();
      DelayedCallGuard dg(languageHook);
      // we're shutting down so unregister me.
      if (languageHook)
      {
        DelayedCallGuard dc;
        languageHook->UnregisterMonitorCallback(this);
      }
    }
  }
}

