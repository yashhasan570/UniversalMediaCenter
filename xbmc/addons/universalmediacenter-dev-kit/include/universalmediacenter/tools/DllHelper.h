/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#ifdef __cplusplus

#include <string>

#include <dlfcn.h>
#include <universalmediacenter/AddonBase.h>
#include <universalmediacenter/Filesystem.h>

//==============================================================================
/// @ingroup cpp_universalmediacenter_tools_CDllHelper
/// @brief Macro to translate the given pointer value name of functions to
/// requested function name.
///
/// @note This should always be used and does the work of
/// @ref tools::CDllHelper::RegisterSymbol().
///
#define REGISTER_DLL_SYMBOL(functionPtr) \
  tools::CDllHelper::RegisterSymbol(functionPtr, #functionPtr)
//------------------------------------------------------------------------------

namespace universalmediacenter
{
namespace tools
{

//==============================================================================
/// @defgroup cpp_universalmediacenter_tools_CDllHelper class CDllHelper
/// @ingroup cpp_universalmediacenter_tools
/// @brief **Class to help with load of shared library functions**\n
/// You can add them as parent to your class and to help with load of shared
/// library functions.
///
/// @note To use on Windows must you also include [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
/// on your addon!\n\n
/// Furthermore, this allows the use of Android where the required library is
/// copied to an EXE usable folder.
///
///
/// ----------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
///
/// #include <universalmediacenter/tools/DllHelper.h>
///
/// ...
/// class CMyInstance : public addon::CInstanceAudioDecoder,
///                     private tools::CDllHelper
/// {
/// public:
///   CMyInstance(UNIVERSALMEDIA_HANDLE instance, const std::string& universalmediacenterVersion);
///   bool Start();
///
///   ...
///
///   // The pointers for on shared library exported functions
///   int (*Init)();
///   void (*Cleanup)();
///   int (*GetLength)();
/// };
///
/// CMyInstance::CMyInstance(UNIVERSALMEDIA_HANDLE instance, const std::string& universalmediacenterVersion)
///   : CInstanceAudioDecoder(instance, universalmediacenterVersion)
/// {
/// }
///
/// bool CMyInstance::Start()
/// {
///   std::string lib = GetAddonPath("myLib.so");
///   if (!LoadDll(lib)) return false;
///   if (!REGISTER_DLL_SYMBOL(Init)) return false;
///   if (!REGISTER_DLL_SYMBOL(Cleanup)) return false;
///   if (!REGISTER_DLL_SYMBOL(GetLength)) return false;
///
///   Init();
///   return true;
/// }
/// ...
/// ~~~~~~~~~~~~~
///
///@{
class ATTR_DLL_LOCAL CDllHelper
{
public:
  //============================================================================
  /// @ingroup cpp_universalmediacenter_tools_CDllHelper
  /// @brief Class constructor.
  ///
  CDllHelper() = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_tools_CDllHelper
  /// @brief Class destructor.
  ///
  virtual ~CDllHelper()
  {
    if (m_dll)
      dlclose(m_dll);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_tools_CDllHelper
  /// @brief Function to load requested library.
  ///
  /// @param[in] path The path with filename of shared library to load
  /// @return true if load was successful done
  ///
  bool LoadDll(std::string path)
  {
#if defined(TARGET_ANDROID)
    if (vfs::FileExists(path))
    {
      // Check already defined for "altbinaddons", if yes no copy necassary.
      std::string altbinaddons =
          vfs::TranslateSpecialProtocol("special://altbinaddons/");
      if (path.compare(0, altbinaddons.length(), altbinaddons) != 0)
      {
        bool doCopy = true;
        std::string dstfile = altbinaddons + vfs::GetFileName(path);

        vfs::FileStatus dstFileStat;
        if (vfs::StatFile(dstfile, dstFileStat))
        {
          vfs::FileStatus srcFileStat;
          if (vfs::StatFile(path, srcFileStat))
          {
            if (dstFileStat.GetSize() == srcFileStat.GetSize() &&
                dstFileStat.GetModificationTime() > srcFileStat.GetModificationTime())
              doCopy = false;
          }
        }

        if (doCopy)
        {
          Log(ADDON_LOG_DEBUG, "Caching '%s' to '%s'", path.c_str(), dstfile.c_str());
          if (!vfs::CopyFile(path, dstfile))
          {
            Log(ADDON_LOG_ERROR, "Failed to cache '%s' to '%s'", path.c_str(),
                      dstfile.c_str());
            return false;
          }
        }

        path = dstfile;
      }
    }
    else
    {
      return false;
    }
#endif

    m_dll = dlopen(path.c_str(), RTLD_LOCAL | RTLD_LAZY);
    if (m_dll == nullptr)
    {
      Log(ADDON_LOG_ERROR, "Unable to load %s", dlerror());
      return false;
    }
    return true;
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_tools_CDllHelper
  /// @brief Function to register requested library symbol.
  ///
  /// @warning This function should not be used, use instead the macro
  /// @ref REGISTER_DLL_SYMBOL to register the symbol pointer.
  ///
  ///
  /// Use this always via Macro, e.g.:
  /// ~~~~~~~~~~~~~{.cpp}
  /// if (!REGISTER_DLL_SYMBOL(Init))
  ///   return false;
  /// ~~~~~~~~~~~~~
  ///
  template<typename T>
  bool RegisterSymbol(T& functionPtr, const char* strFunctionPtr)
  {
    functionPtr = reinterpret_cast<T>(dlsym(m_dll, strFunctionPtr));
    if (functionPtr == nullptr)
    {
      Log(ADDON_LOG_ERROR, "Unable to assign function %s", dlerror());
      return false;
    }
    return true;
  }
  //----------------------------------------------------------------------------

private:
  void* m_dll = nullptr;
};
///@}
//------------------------------------------------------------------------------

} /* namespace tools */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
