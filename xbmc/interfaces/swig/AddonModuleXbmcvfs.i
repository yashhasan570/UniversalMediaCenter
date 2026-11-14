/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%module vfs

%{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif

#include "interfaces/legacy/ModuleXbmcvfs.h"
#include "interfaces/legacy/File.h"
#include "interfaces/legacy/Stat.h"
#include "utils/log.h"

using namespace Addon;
using namespace vfs;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

%}


%include "Universal Media Center_common.i"

// construction in tp_new; see Universal Media Center_construct.i
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::vfs, File)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::vfs, Stat)

/* one line per shape crossing the boundary in this module */
%template() std::vector<std::string>;
%template() Addon::Tuple<std::vector<std::string>, std::vector<std::string> >;

%include "interfaces/legacy/swighelper.h"
%include "interfaces/legacy/AddonString.h"

// The shipped bindings decode File.read strictly (%feature("python:strictUnicode"),
// a Universal Media Center-invented feature stock SWIG drops). Stock SWIG_FromCharPtrAndSize uses
// surrogateescape, which turns binary content into surrogates instead of raising,
// so a caller reading a non-text file gets silent mojibake rather than an error.
%typemap(out) Addon::String Addon::vfs::File::read {
  $result = PyUnicode_DecodeUTF8($1.c_str(), (Py_ssize_t)$1.size(), "strict");
  if (!$result)
    SWIG_fail;
}

/* Python calls __exit__ with the exception triple, which File.h does not take. */
%ignore Addon::vfs::File::__exit__();
%extend Addon::vfs::File {
  void __exit__(PyObject* exc_type = nullptr, PyObject* exc_value = nullptr,
                PyObject* traceback = nullptr)
  {
    $self->close();
  }
}

%include "interfaces/legacy/File.h"

%rename ("st_atime") Addon::vfs::Stat::atime;
%rename ("st_mtime") Addon::vfs::Stat::mtime;
%rename ("st_ctime") Addon::vfs::Stat::ctime;
%include "interfaces/legacy/Stat.h"

%rename ("delete") Addon::vfs::deleteFile;
%include "interfaces/legacy/ModuleXbmcvfs.h"

