/*
 *  Copyright (C) 2005-2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

%module(directors="1") gui

%{
#if defined(TARGET_WINDOWS)
#  include <windows.h>
#endif

#include "interfaces/legacy/Dialog.h"
#include "interfaces/legacy/ModuleXbmcgui.h"
#include "interfaces/legacy/Control.h"
#include "interfaces/legacy/Window.h"
#include "interfaces/legacy/WindowDialog.h"
#include "interfaces/legacy/WindowXML.h"
#include "input/actions/ActionIDs.h"
#include "input/keymaps/keyboard/KeyIDs.h"

using namespace Addon;
using namespace gui;

#if defined(__GNUG__)
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

%}

%include "Universal Media Center_common.i"

// Window.getControl() and getFocus() are declared to return the base Control*,
// but the object is a concrete subclass. Without RTTI dispatch python gets a
// base Control and every derived method raises AttributeError.
UNIVERSAL MEDIA CENTER_DYNAMIC_RETURN(Addon::gui::Control)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlButton)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlEdit)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlFadeLabel)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlGroup)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlImage)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlLabel)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlList)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlProgress)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlRadioButton)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlSlider)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlSpin)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlTextBox)
UNIVERSAL MEDIA CENTER_REGISTER_TYPE(Addon::gui::ControlVideoWindow)

// Window subclasses dispose() before Release; see Universal Media Center_addonclass.i
%feature("unref") Addon::gui::Window          "UniversalMediaCenter*wig_releaseWindow($this);"
%feature("unref") Addon::gui::WindowDialog    "UniversalMediaCenter*wig_releaseWindow($this);"
%feature("unref") Addon::gui::WindowXML       "UniversalMediaCenter*wig_releaseWindow($this);"
%feature("unref") Addon::gui::WindowXMLDialog "UniversalMediaCenter*wig_releaseWindow($this);"

// construction in tp_new; see Universal Media Center_construct.i
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ListItem)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, Action)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlButton)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlEdit)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlFadeLabel)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlGroup)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlImage)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlLabel)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlList)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlProgress)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlRadioButton)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlSlider)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlTextBox)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, ControlVideoWindow)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, Dialog)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, DialogProgress)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, DialogProgressBG)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, Window)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, WindowDialog)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, WindowXML)
UNIVERSAL MEDIA CENTER_CONSTRUCT(Addon::gui, WindowXMLDialog)

namespace Addon { namespace gui { class ListItem; class Control; } }

// ListItem.h sits inside namespace Addon and spells these partially
// qualified as ::InfoTagVideo. Without the fully qualified declaration
// SWIG mints "::InfoTagVideo", which does not match the name the 
// module registers, and cross-module lookup silently yields an opaque pointer.
namespace Addon { namespace  {
  class InfoTagVideo; class InfoTagMusic; class InfoTagPicture; class InfoTagGame;
} }
%traits_swigtype(Addon::gui::ListItem);
%fragment(SWIG_Traits_frag(Addon::gui::ListItem));
%traits_swigtype(Addon::gui::Control);
%fragment(SWIG_Traits_frag(Addon::gui::Control));

/* one line per shape crossing the boundary in this module */
%template() std::vector<int>;
%template() std::vector<std::string>;
%template() std::vector<Addon::gui::Control*>;
%template() std::vector<Addon::gui::ListItem const*>;
%template() Addon::Tuple<std::string, std::string>;
%template() std::vector<Addon::Tuple<std::string, std::string> >;
%template() Addon::Alternative<std::string, std::vector<std::string> >;
%template() Addon::Alternative<std::string, Addon::gui::ListItem const*>;
%template() std::vector<Addon::Alternative<std::string, Addon::gui::ListItem const*> >;
%template() Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> >;
%template() std::vector<Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> > >;
%template() Addon::Alternative<std::string, std::vector<Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> > > >;
%template() Addon::Dictionary<std::string>;
%template() std::vector<Addon::Dictionary<std::string> >;
%template() Addon::Dictionary<Addon::Alternative<std::string, std::vector<Addon::Alternative<std::string, Addon::Tuple<std::string, std::string> > > > >;

/* -builtin routes the comparison operators through tp_richcompare, whose
   dispatcher calls a two-argument wrapper. */
%feature("kwargs", "0") Addon::gui::Control::operator==;
%feature("kwargs", "0") Addon::gui::Control::operator>;
%feature("kwargs", "0") Addon::gui::Control::operator<;

/* multiselect hands back ownership of a list it built; python gets the list. */
%typemap(out) std::unique_ptr<std::vector<int> >
{
  $result = $1 ? swig::from(*$1) : SWIG_Py_Void();
}

%include "interfaces/legacy/swighelper.h"
%include "interfaces/legacy/AddonString.h"

%include "interfaces/legacy/ModuleXbmcgui.h"

%include "interfaces/legacy/Exception.h"

%include "interfaces/legacy/Dictionary.h"

%include "interfaces/legacy/ListItem.h"

%template() std::vector<Addon::gui::ListItem*>;
%include "interfaces/legacy/Control.h"

%Universal Media Center_defaulted_container(%arg(std::vector<Addon::gui::ListItem const *>))
%Universal Media Center_defaulted_container(%arg(std::vector<int>))
%include "interfaces/legacy/Dialog.h"

%feature("director") Window;
%feature("director") WindowDialog;
%feature("director") WindowXML;
%feature("director") WindowXMLDialog;

// scripts compare Actions to ints: a non-Action operand compares against the id.
%feature("python:slot", "tp_richcompare", functype="richcmpfunc") Addon::gui::Action::__eq__;
%feature("kwargs", "0") Addon::gui::Action::__eq__;
%extend Addon::gui::Action {
  PyObject* __eq__(PyObject* obj2) {
    void* argp = 0;
    if (SWIG_IsOK(SWIG_ConvertPtr(obj2, &argp, SWIGTYPE_p_Addon__gui__Action, 0)) && argp)
    {
      Addon::gui::Action* a2 = reinterpret_cast<Addon::gui::Action*>(argp);
      if ($self->id == a2->id && $self->buttonCode == a2->buttonCode &&
          $self->fAmount1 == a2->fAmount1 && $self->fAmount2 == a2->fAmount2 &&
          $self->fRepeat == a2->fRepeat && $self->strAction == a2->strAction)
        Py_RETURN_TRUE;
      Py_RETURN_FALSE;
    }
    PyObject* o1 = PyLong_FromLong($self->id);
    PyObject* r = PyObject_RichCompare(o1, obj2, Py_EQ);
    Py_DECREF(o1);
    return r;
  }
}

%include "interfaces/legacy/Window.h"
%include "interfaces/legacy/WindowDialog.h"

%include "interfaces/legacy/WindowXML.h"

%include "input/actions/ActionIDs.h"
%include "input/keymaps/keyboard/KeyIDs.h"

// for ContextItemAddonInvoker; %wrapper has C linkage; owned!=0: dealloc Releases the caller's Acquire
%wrapper %{
extern "C" PyObject* UniversalMediaCenter*wig_wrapListItem(Addon::gui::ListItem* obj, int owned)
{
  return SWIG_Python_NewPointerObj(NULL, obj, SWIGTYPE_p_Addon__gui__ListItem,
                                   owned ? SWIG_POINTER_OWN : 0);
}
%}
