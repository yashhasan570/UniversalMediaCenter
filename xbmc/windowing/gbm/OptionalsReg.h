/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

//-----------------------------------------------------------------------------
// VAAPI
//-----------------------------------------------------------------------------

namespace KODI
{
namespace WINDOWING
{
namespace GBM
{
class CVaapiProxy;

CVaapiProxy* VaapiProxyCreate(int fd);
void VaapiProxyDelete(CVaapiProxy* proxy);
void VaapiProxyConfig(CVaapiProxy* proxy, void* eglDpy);
void VAAPIRegister(CVaapiProxy* winSystem, bool deepColor);
#if defined(HAS_GL)
void VAAPIRegisterRenderGL(CVaapiProxy* winSystem, bool& general, bool& deepColor);
#endif
#if defined(HAS_GLES)
void VAAPIRegisterRenderGLES(CVaapiProxy* winSystem, bool& general, bool& deepColor);
#endif
} // namespace GBM
} // namespace WINDOWING
} // namespace KODI
