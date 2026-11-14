/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "WasmWebApis.h"

#include "TitanWebApis.h"
#include "TizenWebApis.h"
#include "utils/JSONVariantParser.h"
#include "utils/Variant.h"

#include <cstdlib>

#include <emscripten/em_asm.h>

namespace UNIVERSAL MEDIA CENTER::PLATFORM::WASM
{
WebApiProvider CWasmWebApis::GetProvider()
{
  // The launcher selects the provider and finishes SDK initialization before Universal Media Center starts.
  static const WebApiProvider provider = []
  {
    // clang-format off
    const int selected = MAIN_THREAD_EM_ASM_INT(({
      const provider = Module.universalmediacenter && Module.universalmediacenter.webApiProvider;
      if (provider === 'tizen') return 1;
      if (provider === 'titan') return 2;
      return 0;
    }));
    // clang-format on
    switch (selected)
    {
      case 1:
        return WebApiProvider::TIZEN;
      case 2:
        return WebApiProvider::TITAN;
      default:
        return WebApiProvider::NONE;
    }
  }();
  return provider;
}

WasmDeviceInfo CWasmWebApis::GetDeviceInfo()
{
  static const WasmDeviceInfo info = []
  {
    switch (GetProvider())
    {
      case WebApiProvider::TIZEN:
        return CTizenWebApis::GetDeviceInfo();
      case WebApiProvider::TITAN:
        return CTitanWebApis::GetDeviceInfo();
      default:
        return WasmDeviceInfo{};
    }
  }();
  return info;
}

bool ParseOwnedJson(void* ptr, CVariant& out)
{
  if (!ptr)
    return false;

  const bool ok = CJSONVariantParser::Parse(static_cast<const char*>(ptr), out);
  std::free(ptr);
  return ok && out.isObject();
}
} // namespace UNIVERSAL MEDIA CENTER::PLATFORM::WASM
