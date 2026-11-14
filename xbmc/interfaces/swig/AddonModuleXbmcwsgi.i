/*
 *  Copyright (C) 2015-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%begin %{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif
%}

/* HAS_WEB_SERVER guarded the whole generated file through an %insert("footer")
   #endif. The python backend has no footer section, so the guard belongs in the
   build system: compile this module only when HAS_WEB_SERVER is set. */

%module wsgi

%{
#include "interfaces/legacy/wsgi/WsgiErrorStream.h"
#include "interfaces/legacy/wsgi/WsgiInputStream.h"
#include "interfaces/legacy/wsgi/WsgiResponse.h"
#include "interfaces/legacy/wsgi/WsgiResponseBody.h"

using namespace Addon;
using namespace wsgi;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

%}

%include "Universal Media Center_common.i"

// declared before the header that returns it, fully qualified, so SWIG
// records a name the registering module also uses
namespace Addon { namespace wsgi { class WsgiResponseBody; } }

// construction in tp_new; see Universal Media Center_construct.i
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::wsgi, WsgiErrorStream)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::wsgi, WsgiInputStream)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::wsgi, WsgiInputStreamIterator)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::wsgi, WsgiResponse)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::wsgi, WsgiResponseBody)

/* one line per shape crossing the boundary in this module */
%template() std::vector<std::string>;
%template() Addon::Tuple<std::string, std::string>;
%template() std::vector<Addon::Tuple<std::string, std::string> >;

/* -builtin routes operator() through the tp_call slot, whose closure drops the
   keyword dict and calls a two-argument wrapper. */
%feature("kwargs", "0") Addon::wsgi::WsgiResponse::operator();
%feature("kwargs", "0") Addon::wsgi::WsgiResponseBody::operator();

%include "interfaces/legacy/swighelper.h"
%include "interfaces/legacy/AddonString.h"

%include "interfaces/legacy/wsgi/WsgiErrorStream.h"
// stock SWIG needs explicit tp_iter/tp_iternext slots for iteration
%feature("kwargs", "0") Addon::wsgi::WsgiInputStream::__iter__;
%feature("kwargs", "0") Addon::wsgi::WsgiInputStreamIterator::__iter__;
%feature("kwargs", "0") Addon::wsgi::WsgiInputStreamIterator::__next__;
%feature("python:slot", "tp_iter",     functype="getiterfunc") Addon::wsgi::WsgiInputStream::__iter__;
%feature("python:slot", "tp_iter",     functype="getiterfunc") Addon::wsgi::WsgiInputStreamIterator::__iter__;
%feature("python:slot", "tp_iternext", functype="iternextfunc") Addon::wsgi::WsgiInputStreamIterator::__next__;
%newobject Addon::wsgi::WsgiInputStream::__iter__;
%extend Addon::wsgi::WsgiInputStream {
  Addon::wsgi::WsgiInputStreamIterator* __iter__() { return $self->begin(); }
}
%extend Addon::wsgi::WsgiInputStreamIterator {
  PyObject* __iter__() {
    return SWIG_Python_NewPointerObj(NULL, $self,
             SWIGTYPE_p_Addon__wsgi__WsgiInputStreamIterator, 0);
  }
  PyObject* __next__() {
    if ($self->end()) { PyErr_SetNone(PyExc_StopIteration); return NULL; }
    std::string line = *(*$self);
    ++(*$self);
    return PyUnicode_DecodeUTF8(line.c_str(), line.size(), "surrogateescape");
  }
}

%include "interfaces/legacy/wsgi/WsgiInputStream.h"
// WsgiResponse::operator() returns WsgiResponseBody*, so that class must be
// wrapped before it is named, or SWIG has no class node and %feature("ref")
// never fires: the call operator then hands python an owned pointer it leaks.
%include "interfaces/legacy/wsgi/WsgiResponseBody.h"
%include "interfaces/legacy/wsgi/WsgiResponse.h"


// for HTTPPythonWsgiInvoker; %wrapper has C linkage (no overloads); owned!=0: dealloc Releases the caller's Acquire
%wrapper %{
extern "C" PyObject* UniversalMediaCenter*wig_wrapWsgiResponse(Addon::wsgi::WsgiResponse* obj, int owned)
{
  return SWIG_Python_NewPointerObj(NULL, obj, SWIGTYPE_p_Addon__wsgi__WsgiResponse,
                                   owned ? SWIG_POINTER_OWN : 0);
}
extern "C" PyObject* UniversalMediaCenter*wig_wrapWsgiInputStream(Addon::wsgi::WsgiInputStream* obj, int owned)
{
  return SWIG_Python_NewPointerObj(NULL, obj, SWIGTYPE_p_Addon__wsgi__WsgiInputStream,
                                   owned ? SWIG_POINTER_OWN : 0);
}
extern "C" PyObject* UniversalMediaCenter*wig_wrapWsgiErrorStream(Addon::wsgi::WsgiErrorStream* obj, int owned)
{
  return SWIG_Python_NewPointerObj(NULL, obj, SWIGTYPE_p_Addon__wsgi__WsgiErrorStream,
                                   owned ? SWIG_POINTER_OWN : 0);
}
%}
