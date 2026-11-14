/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */


#include "LanguageHook.h"

#include "CallbackHandler.h"
#include "PyContext.h"
#include "ServiceBroker.h"
#include "XBPython.h"
#include "interfaces/legacy/AddonUtils.h"
#include "utils/log.h"

#include <mutex>

namespace Addon
{
  namespace Python
  {
    static AddonClass::Ref<PythonLanguageHook> instance;

    static CCriticalSection hooksMutex;
    static std::map<PyInterpreterState*,AddonClass::Ref<PythonLanguageHook> > hooks;

    // vtab instantiation
    PythonLanguageHook::~PythonLanguageHook()
    {
      _TRACE;
      Addon::LanguageHook::deallocating();
    }

    void PythonLanguageHook::MakePendingCalls()
    {
      _TRACE;
      PythonCallbackHandler::makePendingCalls();
    }

    void PythonLanguageHook::DelayedCallOpen()
    {
      _TRACE;
      PyGILLock::releaseGil();
    }

    void PythonLanguageHook::DelayedCallClose()
    {
      _TRACE;
      PyGILLock::acquireGil();
    }

    void PythonLanguageHook::RegisterMe()
    {
      _TRACE;
      std::unique_lock lock(hooksMutex);
      hooks[m_interp] = AddonClass::Ref<PythonLanguageHook>(this);
    }

    void PythonLanguageHook::UnregisterMe()
    {
      _TRACE;
      std::unique_lock lock(hooksMutex);
      hooks.erase(m_interp);
    }

    static AddonClass::Ref<Addon::Python::PythonLanguageHook> g_languageHook;

    // Ok ... we're going to get it even if it doesn't exist. If it doesn't exist then
    // we're going to assume we're not in control of the interpreter. This (apparently)
    // can be the case. E.g. Libspotify manages to call into a script using a ctypes
    // extension but under the control of an Interpreter we know nothing about. In
    // cases like this we're going to use a global interpreter
    AddonClass::Ref<PythonLanguageHook> PythonLanguageHook::GetIfExists(PyInterpreterState* interp)
    {
      _TRACE;
      std::unique_lock lock(hooksMutex);
      std::map<PyInterpreterState*,AddonClass::Ref<PythonLanguageHook> >::iterator iter = hooks.find(interp);
      if (iter != hooks.end())
        return iter->second;

      // if we got here then we need to use the global one.
      if (g_languageHook.isNull())
        g_languageHook = new Addon::Python::PythonLanguageHook();

      return g_languageHook;
    }

    bool PythonLanguageHook::IsAddonClassInstanceRegistered(AddonClass* obj)
    {
      for (const auto& iter : hooks)
      {
        if (iter.second->HasRegisteredAddonClassInstance(obj))
          return true;
      }
      return false;
    }

    /**
     * PythonCallbackHandler expects to be instantiated PER AddonClass instance
     *  that is to be used as a callback. This is why this cannot be instantiated
     *  once.
     *
     * There is an expectation that this method is called from the Python thread
     *  that instantiated an AddonClass that has the potential for a callback.
     *
     * See RetardedAsyncCallbackHandler for more details.
     * See PythonCallbackHandler for more details
     * See PythonCallbackHandler::PythonCallbackHandler for more details
     */
    Addon::CallbackHandler* PythonLanguageHook::GetCallbackHandler()
    {
      _TRACE;
      return new PythonCallbackHandler();
    }

    String PythonLanguageHook::GetAddonId()
    {
      _TRACE;

      // Get a reference to the main module
      // and global dictionary
      PyObject* main_module = PyImport_AddModule("__main__");
      if (!main_module)
      {
        CLog::Log(LOGDEBUG, "PythonLanguageHook::{}: __main__ returns null", __FUNCTION__);
        return "";
      }
      PyObject* global_dict = PyModule_GetDict(main_module);
      // Extract a reference to the function "func_name"
      // from the global dictionary
      PyObject* pyid = PyDict_GetItemString(global_dict, "__addonid__");
      if (pyid)
        return PyUnicode_AsUTF8(pyid);
      return "";
    }

    String PythonLanguageHook::GetAddonVersion()
    {
      _TRACE;
      // Get a reference to the main module
      // and global dictionary
      PyObject* main_module = PyImport_AddModule("__main__");
      if (!main_module)
      {
        CLog::Log(LOGDEBUG, "PythonLanguageHook::{}: __main__ returns null", __FUNCTION__);
        return "";
      }
      PyObject* global_dict = PyModule_GetDict(main_module);
      // Extract a reference to the function "func_name"
      // from the global dictionary
      PyObject* pyversion = PyDict_GetItemString(global_dict, "__apiversion__");
      if (pyversion)
        return PyUnicode_AsUTF8(pyversion);
      return "";
    }

    long PythonLanguageHook::GetInvokerId()
    {
      _TRACE;

      // Get a reference to the main module
      // and global dictionary
      PyObject* main_module = PyImport_AddModule("__main__");
      if (!main_module)
      {
        CLog::Log(LOGDEBUG, "PythonLanguageHook::{}: __main__ returns null", __FUNCTION__);
        return -1;
      }
      PyObject* global_dict = PyModule_GetDict(main_module);
      // Extract a reference to the function "func_name"
      // from the global dictionary
      PyObject* pyid = PyDict_GetItemString(global_dict, "__invokerid__");
      if (pyid)
        return PyLong_AsLong(pyid);
      return -1;
    }

    void PythonLanguageHook::RegisterPlayerCallback(IPlayerCallback* player)
    {
      _TRACE;
      CServiceBroker::GetXBPython().RegisterPythonPlayerCallBack(player);
    }
    void PythonLanguageHook::UnregisterPlayerCallback(IPlayerCallback* player)
    {
      _TRACE;
      CServiceBroker::GetXBPython().UnregisterPythonPlayerCallBack(player);
    }
    void PythonLanguageHook::RegisterMonitorCallback(Addon::::Monitor* monitor)
    {
      _TRACE;
      CServiceBroker::GetXBPython().RegisterPythonMonitorCallBack(monitor);
    }
    void PythonLanguageHook::UnregisterMonitorCallback(Addon::::Monitor* monitor)
    {
      _TRACE;
      CServiceBroker::GetXBPython().UnregisterPythonMonitorCallBack(monitor);
    }

    bool PythonLanguageHook::WaitForEvent(CEvent& hEvent, unsigned int milliseconds)
    {
      _TRACE;
      return CServiceBroker::GetXBPython().WaitForEvent(hEvent, milliseconds);
    }

    void PythonLanguageHook::RegisterAddonClassInstance(AddonClass* obj)
    {
      _TRACE;
      std::unique_lock l(*this);
      obj->Acquire();
      currentObjects.insert(obj);
    }

    void PythonLanguageHook::UnregisterAddonClassInstance(AddonClass* obj)
    {
      _TRACE;
      std::unique_lock l(*this);
      if (currentObjects.erase(obj) > 0)
        obj->Release();
    }

    bool PythonLanguageHook::HasRegisteredAddonClassInstance(AddonClass* obj)
    {
      _TRACE;
      std::unique_lock l(*this);
      return currentObjects.contains(obj);
    }
  }
}
