/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%module drm

%{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif

#include "interfaces/legacy/DrmCryptoSession.h"
#include "utils/log.h"

using namespace Addon;
using namespace drm;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

%}

%include "Universal Media Center_common.i"

// construction in tp_new; see Universal Media Center_construct.i
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::drm, CryptoSession)

/* one line per shape crossing the boundary in this module */
%template() std::map<std::string, std::string>;

%include "interfaces/legacy/swighelper.h"
%include "interfaces/legacy/AddonString.h"
%include "interfaces/legacy/DrmCryptoSession.h"
