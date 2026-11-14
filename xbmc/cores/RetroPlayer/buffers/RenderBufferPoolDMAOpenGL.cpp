/*
 *  Copyright (C) 2017-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "RenderBufferPoolDMAOpenGL.h"

#include "RenderBufferDMAOpenGL.h"

using namespace KODI;
using namespace RETRO;

IRenderBuffer* CRenderBufferPoolDMAOpenGL::CreateRenderBuffer(void* header /* = nullptr */)
{
  return new CRenderBufferDMAOpenGL(GetFourcc());
}
