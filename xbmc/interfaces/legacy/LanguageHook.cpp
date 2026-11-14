/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "LanguageHook.h"

#include "utils/GlobalsHandling.h"

namespace Addon
{
  // just need a place for the vtab
  LanguageHook::~LanguageHook() = default;

  static thread_local LanguageHook* addonLanguageHookTls;
  static bool threadLocalInitialized = false;
  static util::InitFlag initer(threadLocalInitialized);

  void LanguageHook::SetLanguageHook(LanguageHook* languageHook)
  {
    _TRACE;
    languageHook->Acquire();
    addonLanguageHookTls = languageHook;
  }

  LanguageHook* LanguageHook::GetLanguageHook()
  {
    return threadLocalInitialized ? addonLanguageHookTls : NULL;
  }

  void LanguageHook::ClearLanguageHook()
  {
    LanguageHook* lh = addonLanguageHookTls;
    addonLanguageHookTls = NULL;
    if (lh)
      lh->Release();
  }
}
