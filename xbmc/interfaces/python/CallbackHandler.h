/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "interfaces/legacy/CallbackHandler.h"

#include <Python.h>

namespace Addon
{
  namespace Python
  {
    /**
     * This class represents a specialization of the callback handler
     *  that specifically checks to see if we're in an OK thread state
     *  based on Python specifics.
     */
    class PythonCallbackHandler : public RetardedAsyncCallbackHandler
    {
      PyThreadState* objectThreadState;
    public:

      /**
       * We are ASS-U-MEing that this construction is happening
       *  within the context of a Python call. This way we can
       *  store off the PyThreadState to later verify that we're
       *  handling callbacks in the appropriate thread.
       */
      PythonCallbackHandler();
      bool isStateOk(AddonClass* obj) override;
      bool shouldRemoveCallback(AddonClass* obj, void* threadState) override;
    };
  }
}
