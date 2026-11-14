/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%module(directors="1") 

%{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif

#include "interfaces/legacy/Player.h"
#include "interfaces/legacy/RenderCapture.h"
#include "interfaces/legacy/Keyboard.h"
#include "interfaces/legacy/ModuleXbmc.h"
#include "interfaces/legacy/Monitor.h"
#include "interfaces/legacy/ListItem.h"

using namespace Addon;
using namespace ;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
%}

%include "Universal Media Center_common.i"

// ListItem belongs to gui and is only forward declared here, so SWIG has no
// class node and %feature("ref") cannot attach: getPlayingItem would hand python
// an owned pointer it never acquired, and AddonClass starts at refs(0), so the
// Release on dealloc drives the count negative and never frees. Acquire here.
%typemap(out) Addon::gui::ListItem * {
  UniversalMediaCenter*wig_acquire($1);
  $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), $descriptor, SWIG_POINTER_OWN);
}

// construction in tp_new; see Universal Media Center_construct.i
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, Player)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, Monitor)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, Keyboard)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, PlayList)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, RenderCapture)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, InfoTagGame)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, InfoTagMusic)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, InfoTagPicture)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, InfoTagRadioRDS)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, InfoTagVideo)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, Actor)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, VideoStreamDetail)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, AudioStreamDetail)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, SubtitleStreamDetail)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, ContentGeometrySection)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::, ContentGeometry)

namespace Addon { namespace  { class PlayList; class Actor; class ContentGeometrySection; } }

// Player.h names these before their own headers are parsed, and spells them
// without the namespace. SWIG records the name as written, so without this it
// mints "InfoTagVideo", which matches nothing any module registers, and the
// getter silently returns an opaque object that also never refcounts.
namespace Addon { namespace  {
  class InfoTagVideo; class InfoTagMusic; class InfoTagGame; class InfoTagRadioRDS;
  class ContentGeometry;
} }
%traits_swigtype(Addon::::PlayList);
%fragment(SWIG_Traits_frag(Addon::::PlayList));
%traits_swigtype(Addon::::Actor);
%fragment(SWIG_Traits_frag(Addon::::Actor));
%traits_swigtype(Addon::::ContentGeometrySection);
%fragment(SWIG_Traits_frag(Addon::::ContentGeometrySection));

/* one line per shape crossing the boundary in this module */
%template() std::vector<std::string>;
%template() std::vector<Addon::::Actor*>;
%template() std::vector<Addon::::Actor const*>;
%template() std::vector<Addon::::ContentGeometrySection*>;
%template() Addon::Tuple<std::string, std::string>;
%template() Addon::Tuple<float, int>;
%template() Addon::Tuple<int, std::string, std::string>;
%template() std::vector<Addon::Tuple<int, std::string, std::string> >;
%template() Addon::Alternative<std::string, Addon::::PlayList const*>;
%template() std::map<std::string, std::string, std::less<> >;
%template() std::map<std::string, Addon::Tuple<float, int> >;
%template() Addon::Dictionary<std::string>;
%template() std::vector<Addon::Dictionary<std::string> >;

%include "interfaces/legacy/swighelper.h"

%include "interfaces/legacy/AddonString.h"
%include "interfaces/legacy/ModuleXbmc.h"
%include "interfaces/legacy/Dictionary.h"

%feature("director") Player;

%include "interfaces/legacy/Player.h"

%include "interfaces/legacy/RenderCapture.h"

%include "interfaces/legacy/InfoTagGame.h"
%include "interfaces/legacy/InfoTagMusic.h"
%include "interfaces/legacy/InfoTagPicture.h"
%include "interfaces/legacy/InfoTagRadioRDS.h"
%include "interfaces/legacy/InfoTagVideo.h"
%include "interfaces/legacy/Keyboard.h"
// -builtin dispatches these through type slots; a method merely named __len__
// is not reachable, so the slot must be declared explicitly
// slot closures are fixed arity, so these must not take a keyword dict
%feature("kwargs", "0") Addon::::PlayList::__len__;
%feature("kwargs", "0") Addon::::PlayList::__getitem__;
%feature("python:slot", "sq_length",   functype="lenfunc")    Addon::::PlayList::__len__;
%feature("python:slot", "mp_subscript", functype="binaryfunc") Addon::::PlayList::__getitem__;
%extend Addon::::PlayList {
  Addon::gui::ListItem* __getitem__(long i) { return (*$self)[i]; }
  long __len__() const { return const_cast<Addon::::PlayList*>($self)->size(); }
}

%include "interfaces/legacy/PlayList.h"

%feature("director") Monitor;

%include "interfaces/legacy/Monitor.h"



