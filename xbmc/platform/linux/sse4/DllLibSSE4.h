/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DynamicDll.h"

extern "C" {

}

class DllLibSSE4Interface
{
public:
  virtual ~DllLibSSE4Interface() = default;
  virtual void copy_frame(void * pSrc, void * pDest, void * pCacheBlock, unsigned int width, unsigned int height, unsigned int pitch) = 0;
};

class DllLibSSE4 : public DllDynamic, DllLibSSE4Interface
{
  DECLARE_DLL_WRAPPER(DllLibSSE4, DLL_PATH_LIBSSE4)
  DEFINE_METHOD6(void, copy_frame, (void *p1, void *p2, void *p3, unsigned int p4, unsigned int p5, unsigned int p6))

  BEGIN_METHOD_RESOLVE()
    RESOLVE_METHOD(copy_frame)
  END_METHOD_RESOLVE()
};
