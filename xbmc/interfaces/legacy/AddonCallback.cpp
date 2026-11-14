/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */
#include "AddonCallback.h"

namespace Addon
{
  // need a place to put the vtab
  AddonCallback::~AddonCallback() = default;

  void AddonCallback::invokeCallback(Callback* callback)
  {
    if (callback)
    {
      if (hasHandler())
        handler->invokeCallback(callback);
      else
        callback->executeCallback();
    }
  }
}

