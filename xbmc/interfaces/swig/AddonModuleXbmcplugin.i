/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%module plugin

%{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif

#include "interfaces/legacy/ModuleXbmcplugin.h"

using namespace Addon;
using namespace plugin;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

%}

%include "Universal Media Center_common.i"

namespace Addon { namespace gui { class ListItem; } }
%traits_swigtype(Addon::gui::ListItem);
%fragment(SWIG_Traits_frag(Addon::gui::ListItem));

/* one line per shape crossing the boundary in this module */
%template() Addon::Tuple<std::string, Addon::gui::ListItem const*, bool>;
%template() std::vector<Addon::Tuple<std::string, Addon::gui::ListItem const*, bool> >;

%include "interfaces/legacy/swighelper.h"
%include "interfaces/legacy/AddonString.h"
%include "interfaces/legacy/ModuleXbmcplugin.h"

