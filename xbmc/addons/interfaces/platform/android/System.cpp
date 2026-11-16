/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "System.h"

#include "CompileInfo.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/interfaces/AddonBase.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/platform/android/System.h"

#include "platform/android/activity/XBMCApp.h"

static AddonToUniversal Media CenterFuncTable_android_system function_table;

namespace ADDON
{

void Interface_Android::Register()
{
  function_table.get_jni_env = get_jni_env;
  function_table.get_sdk_version = get_sdk_version;
  function_table.get_class_name = get_class_name;
  Interface_Base::RegisterInterface(Get);
}

void* Interface_Android::Get(const std::string &name, const std::string &version)
{
  if (name == INTERFACE_ANDROID_SYSTEM_NAME
  && version >= INTERFACE_ANDROID_SYSTEM_VERSION_MIN
  && version <= INTERFACE_ANDROID_SYSTEM_VERSION)
    return &function_table;

  return nullptr;
};

void* Interface_Android::get_jni_env()
{
  return xbmc_jnienv();
}

int Interface_Android::get_sdk_version()
{
  return CXBMCApp::Get().GetSDKVersion();
}

const char *Interface_Android::get_class_name()
{
  return CCompileInfo::GetClass();
}


} //namespace ADDON
