/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://Universal Media Center.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* AddonClass lifetime.

   Without this, SWIG emits a plain `delete` in the destructor wrapper, which
   bypasses AddonClass's reference count entirely: dropping a python object
   while Universal Media Center still holds a reference is a use-after-free, and an object handed
   back from a getter is never freed at all.

   Every class wrapped by these modules derives from Addon::AddonClass
   (verified against the headers), so the features are declared globally rather
   than repeated per class. %feature("ref") is emitted wherever SWIG takes
   ownership of a pointer, %feature("unref") in the destructor wrapper.

   Registration with the language hook is not optional bookkeeping: it is what
   gates queued callback delivery through PythonCallbackHandler::isStateOk. */

%{
#include "interfaces/legacy/AddonClass.h"
#include "interfaces/legacy/Window.h"
#include "interfaces/legacy/Exception.h"
#include "interfaces/legacy/LanguageHook.h"
#include "interfaces/python/LanguageHook.h"
#include "interfaces/python/PythonToCppException.h"
#include "commons/Exception.h"
#include "utils/log.h"

namespace
{
[[maybe_unused]] inline void UniversalMediaCenter*wig_acquire(Addon::AddonClass* c)
{
  if (!c)
    return;
  c->Acquire();
  Addon::AddonClass::Ref<Addon::Python::PythonLanguageHook> lh =
      Addon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp);
  if (lh.isNotNull())
    lh->RegisterAddonClassInstance(c);
}

/* Windows must tear down before release: the shipped cleanForDealloc(Window*)
   calls dispose() then Release(). dispose() cannot run from the destructor. */
[[maybe_unused]] inline void UniversalMediaCenter*wig_releaseWindow(Addon::gui::Window* c)
{
  if (!c)
    return;
  Addon::AddonClass::Ref<Addon::Python::PythonLanguageHook> lh =
      Addon::AddonClass::Ref<Addon::AddonClass>(c->GetLanguageHook());
  if (lh.isNull())
    lh = Addon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp);
  if (lh.isNotNull())
    lh->UnregisterAddonClassInstance(c);
  c->dispose();
  c->Release();
}

[[maybe_unused]] inline void UniversalMediaCenter*wig_release(Addon::AddonClass* c)
{
  if (!c)
    return;
  Addon::AddonClass::Ref<Addon::Python::PythonLanguageHook> lh =
      Addon::AddonClass::Ref<Addon::AddonClass>(c->GetLanguageHook());
  if (lh.isNull())
    lh = Addon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp);
  if (lh.isNotNull())
    lh->UnregisterAddonClassInstance(c);
  c->Release();
}
} // namespace
%}

%feature("ref")   "UniversalMediaCenter*wig_acquire($this);"
%feature("unref") "UniversalMediaCenter*wig_release($this);"

/* Every wrapped call runs under SetLanguageHookGuard. AddonClass constructors
   read the hook from that TLS slot, so without it addon.Addon() cannot
   resolve its own id and throws "No valid addon id could be obtained"; the
   no-argument DelayedCallGuard in the legacy free functions reads the same slot.

   The catch clauses are equally load-bearing: a Universal Media Center API call that throws
   XbmcCommons::Exception would otherwise unwind out of a CPython wrapper as an
   uncaught C++ exception rather than becoming a python exception. */
%exception {
  try {
    Addon::SetLanguageHookGuard slhg(
        Addon::Python::PythonLanguageHook::GetIfExists(PyThreadState_Get()->interp).get());
    $action
  } catch (const Addon::WrongTypeException& e) {
    CLog::Log(LOGERROR, "EXCEPTION: {}", e.GetExMessage());
    SWIG_exception_fail(SWIG_TypeError, e.GetExMessage());
  } catch (const XbmcCommons::Exception& e) {
    CLog::Log(LOGERROR, "EXCEPTION: {}", e.GetExMessage());
    SWIG_exception_fail(SWIG_RuntimeError, e.GetExMessage());
  } catch (...) {
    CLog::Log(LOGERROR, "EXCEPTION: Unknown exception thrown from the call \"$symname\"");
    SWIG_exception_fail(SWIG_RuntimeError, "Unknown exception thrown from the call \"$symname\"");
  }
}

/* ---- ownership of returned objects ---------------------------------- */
/* --- callee allocates: caller owns --- */
%newobject Addon::gui::ListItem::getVideoInfoTag;
%newobject Addon::gui::ListItem::getMusicInfoTag;
%newobject Addon::gui::ListItem::getPictureInfoTag;
%newobject Addon::gui::ListItem::getGameInfoTag;
%newobject Addon::gui::WindowXML::getListItem;

%newobject Addon::::Player::getVideoInfoTag;
%newobject Addon::::Player::getMusicInfoTag;
%newobject Addon::::Player::getRadioRDSInfoTag;
%newobject Addon::::Player::getGameInfoTag;
%newobject Addon::::Player::getPlayingItem;
%newobject Addon::::Player::getContentGeometry;
%newobject Addon::::InfoTagVideo::getContentGeometry;

%newobject Addon::addon::Addon::getSettings;

%newobject Addon::wsgi::WsgiInputStream::begin;
%newobject Addon::wsgi::WsgiInputStream::end;

/* --- borrowed: %newobject here would be a double free ---
   Window::getControl        - the control is held by Window::vecControls, a
                               vector<Ref<Control>>, on both the cache-hit and
                               the freshly-allocated path (Window.cpp)
   ControlList::getSelectedItem, ControlList::getListItem
                             - return pListItem.get() from a Ref member
   ControlList::getSpinControl - returns a member pointer                    */

/* ---- director callbacks --------------------------------------------- */
/* A python exception raised inside a director callback must not escape as
   Swig::DirectorMethodException: nothing in Universal Media Center catches that, so it would
   reach std::terminate and abort the application. */
%{
#include "interfaces/python/PythonToCppException.h"
%}

%feature("director:except") %{
  if ($error != NULL) {
    throw PythonBindings::PythonToCppException();
  }
%}
