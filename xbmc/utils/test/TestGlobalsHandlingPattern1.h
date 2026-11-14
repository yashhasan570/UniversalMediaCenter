/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/GlobalsHandling.h"

#include <iostream>

namespace util
{
  namespace test
  {
    class TestGlobalPattern1
    {
    public:
      static bool ctorCalled;
      static bool dtorCalled;

      int somethingToAccess = 0;

      TestGlobalPattern1() { ctorCalled = true; }
      ~TestGlobalPattern1()
      {
        std::cout << "Clean shutdown of TestGlobalPattern1" << std::endl << std::flush;
        dtorCalled = true;
      }

      void beHappy() { if (somethingToAccess) throw somethingToAccess; }
    };
  }
}

_GLOBAL_REF(util::test::TestGlobalPattern1,g_testGlobalPattern1);
#define g_testGlobalPattern1 _GLOBAL_USE(util::test::TestGlobalPattern1)
