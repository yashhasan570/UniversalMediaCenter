/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%module addon

%{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif

#include "interfaces/legacy/Addon.h"
#include "interfaces/legacy/Settings.h"

using namespace Addon;
using namespace addon;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

%}

// This is all about warning suppression. It's OK that these base classes are
// not part of what swig parses.
%feature("knownbasetypes") Addon::addon "AddonClass"

%include "Universal Media Center_common.i"

// declared before the header that returns it, fully qualified, so SWIG
// records a name the registering module also uses
namespace Addon { namespace addon { class Settings; } }

// construction in tp_new; see Universal Media Center_construct.i
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::addon, Addon)

/* one line per shape crossing the boundary in this module */
%template() std::vector<bool>;
%template() std::vector<int>;
%template() std::vector<double>;
%template() std::vector<std::string>;

%include "interfaces/legacy/swighelper.h"
%include "interfaces/legacy/AddonString.h"

%include "interfaces/legacy/Addon.h"
%nodefaultctor Settings;
%include "interfaces/legacy/Settings.h"

