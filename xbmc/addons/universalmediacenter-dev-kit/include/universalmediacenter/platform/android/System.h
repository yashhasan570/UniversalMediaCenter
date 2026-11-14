/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/*---AUTO_GEN_PARSE<$$CORE_SYSTEM_NAME:android>---*/

#pragma once

#include "../../AddonBase.h"
#include "../../c-api/platform/android/system.h"

#ifdef __cplusplus
namespace universalmediacenter
{
namespace platform
{

//==============================================================================
/// @defgroup cpp_universalmediacenter_platform_CInterfaceAndroidSystem class CInterfaceAndroidSystem
/// @ingroup cpp_universalmediacenter_platform
/// @brief **Android platform specific functions**\n
/// C++ class to query Android specific things in Universal Media Center.
///
/// It has the header is @ref System.h "#include <universalmediacenter/platform/android/System.h>".
///
/// ----------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/platform/android/System.h>
///
/// #if defined(ANDROID)
/// platform::CInterfaceAndroidSystem system;
/// if (system.GetSDKVersion() >= 23)
/// {
///   ...
/// }
/// #endif
/// ~~~~~~~~~~~~~
///
class ATTR_DLL_LOCAL CInterfaceAndroidSystem
{
public:
  CInterfaceAndroidSystem()
    : m_interface(static_cast<AddonToUniversal Media CenterFuncTable_android_system*>(addon::GetInterface(
          INTERFACE_ANDROID_SYSTEM_NAME, INTERFACE_ANDROID_SYSTEM_VERSION)))
  {
  }

  //============================================================================
  /// @ingroup cpp_universalmediacenter_platform_CInterfaceAndroidSystem
  /// @brief Request an JNI env pointer for the calling thread.
  ///
  /// JNI env has to be controlled by universalmediacenter because of the underlying
  /// threading concep.
  ///
  /// @return JNI env pointer for the calling thread
  ///
  inline void* GetJNIEnv()
  {
    if (m_interface)
      return m_interface->get_jni_env();

    return nullptr;
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_platform_CInterfaceAndroidSystem
  /// @brief Request the android sdk version to e.g. initialize <b>`JNIBase`</b>.
  ///
  /// @return Android SDK version
  ///
  inline int GetSDKVersion()
  {
    if (m_interface)
      return m_interface->get_sdk_version();

    return 0;
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_platform_CInterfaceAndroidSystem
  /// @brief Request the android main class name using the internal slash notation
  /// format e.g. <b>`org//universalmediacenter`</b>.
  ///
  /// @return package class name
  ///
  inline std::string GetClassName()
  {
    if (m_interface)
      return m_interface->get_class_name();

    return std::string();
  }
  //----------------------------------------------------------------------------

private:
  AddonToUniversal Media CenterFuncTable_android_system* m_interface;
};
//------------------------------------------------------------------------------

} /* namespace platform */
} /* namespace universalmediacenter */
#endif /* __cplusplus */
