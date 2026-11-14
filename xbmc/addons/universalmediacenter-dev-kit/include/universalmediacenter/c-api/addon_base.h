/*
 *  Copyright (C) 2005-2019 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDON_BASE_H
#define C_API_ADDON_BASE_H

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef TARGET_WINDOWS
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __declspec
#define __declspec(X)
#endif
#endif

// Generic helper definitions for smallest possible alignment
//@{
#undef ATTR_PACKED
#undef PRAGMA_PACK_BEGIN
#undef PRAGMA_PACK_END

#if defined(__GNUC__)
#define ATTR_PACKED __attribute__((packed))
#define PRAGMA_PACK 0
#endif

#if !defined(ATTR_PACKED)
#define ATTR_PACKED
#define PRAGMA_PACK 1
#endif
//@}

// Generic helper definitions for inline function support
//@{
#ifdef _MSC_VER
#define ATTR_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define ATTR_FORCEINLINE inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
#if __has_attribute(__always_inline__)
#define ATTR_FORCEINLINE inline __attribute__((__always_inline__))
#else
#define ATTR_FORCEINLINE inline
#endif
#else
#define ATTR_FORCEINLINE inline
#endif
//@}

// Generic helper definitions for shared library support
//@{
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#define ATTR_DLL_IMPORT __declspec(dllimport)
#define ATTR_DLL_EXPORT __declspec(dllexport)
#define ATTR_DLL_LOCAL
#ifdef _WIN64
#define ATTR_APIENTRY __stdcall
#else
#define ATTR_APIENTRY __cdecl
#endif
#else
#if __GNUC__ >= 4
#define ATTR_DLL_IMPORT __attribute__((visibility("default")))
#define ATTR_DLL_EXPORT __attribute__((visibility("default")))
#ifndef SWIG
#define ATTR_DLL_LOCAL __attribute__((visibility("hidden")))
#else
#define ATTR_DLL_LOCAL
#endif
#else
#define ATTR_DLL_IMPORT
#define ATTR_DLL_EXPORT
#define ATTR_DLL_LOCAL
#endif
#define ATTR_APIENTRY
#endif

#ifndef ATTR_APIENTRYP
#define ATTR_APIENTRYP ATTR_APIENTRY*
#endif
//@}

#ifdef _WIN32 // windows
#if !defined(_SSIZE_T_DEFINED) && !defined(HAVE_SSIZE_T)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#define _SSIZE_T_DEFINED
#endif // !_SSIZE_T_DEFINED
#ifndef SSIZE_MAX
#define SSIZE_MAX INTPTR_MAX
#endif // !SSIZE_MAX
#else // Linux, Mac, FreeBSD
#include <sys/types.h>
#endif // TARGET_POSIX

/*
 * To have a on add-on and universalmediacenter itself handled string always on known size!
 */
#define ADDON_STANDARD_STRING_LENGTH 1024
#define ADDON_STANDARD_STRING_LENGTH_SMALL 256

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* UNIVERSALMEDIA_ADDON_HDL;
  typedef void* UNIVERSALMEDIA_ADDON_BACKEND_HDL;
  typedef void* UNIVERSALMEDIA_ADDON_INSTANCE_HDL;
  typedef void* UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL;

  // Hardware specific device context interface
  typedef void* ADDON_HARDWARE_CONTEXT;

  typedef void* UNIVERSALMEDIA_ADDON_FUNC_DUMMY;

  //============================================================================
  /// @ingroup cpp_addonbase_Defs
  /// @defgroup cpp_addonbase_Defs_ADDON_STATUS enum ADDON_STATUS
  /// @brief <b>Return value of functions in @ref cpp_addonbase "addon::CAddonBase"
  /// and associated classes</b>\n
  /// With this Universal Media Center can do any follow-up work or add-on e.g. declare it as defective.
  ///
  ///@{
  typedef enum ADDON_STATUS
  {
    /// @brief For everything OK and no error
    ADDON_STATUS_OK,

    /// @brief A needed connection was lost
    ADDON_STATUS_LOST_CONNECTION,

    /// @brief Addon needs a restart inside Universal Media Center
    ADDON_STATUS_NEED_RESTART,

    /// @brief Necessary settings are not yet set
    ADDON_STATUS_NEED_SETTINGS,

    /// @brief Unknown and incomprehensible error
    ADDON_STATUS_UNKNOWN,

    /// @brief Permanent failure, like failing to resolve methods
    ADDON_STATUS_PERMANENT_FAILURE,

    /* internal used return error if function becomes not used from child on
    * addon */
    ADDON_STATUS_NOT_IMPLEMENTED
  } ADDON_STATUS;
  ///@}
  //----------------------------------------------------------------------------

  //============================================================================
  /// @defgroup cpp_universalmediacenter_Defs_ADDON_LOG enum ADDON_LOG
  /// @ingroup cpp_universalmediacenter_Defs
  /// @brief **Log file type definitions**\n
  /// These define the types of log entries given with @ref Log() to Universal Media Center.
  ///
  /// -------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <universalmediacenter/General.h>
  ///
  /// Log(ADDON_LOG_ERROR, "%s: There is an error occurred!", __func__);
  ///
  /// ~~~~~~~~~~~~~
  ///
  ///@{
  typedef enum ADDON_LOG
  {
    /// @brief **0** : To include debug information in the log file.
    ADDON_LOG_DEBUG = 0,

    /// @brief **1** : To include information messages in the log file.
    ADDON_LOG_INFO = 1,

    /// @brief **2** : To write warnings in the log file.
    ADDON_LOG_WARNING = 2,

    /// @brief **3** : To report error messages in the log file.
    ADDON_LOG_ERROR = 3,

    /// @brief **4** : To notify fatal unrecoverable errors, which can may also indicate
    /// upcoming crashes.
    ADDON_LOG_FATAL = 4
  } ADDON_LOG;
  ///@}
  //----------------------------------------------------------------------------

  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_STRING_V1)(
      const UNIVERSALMEDIA_ADDON_INSTANCE_HDL hdl, const char* name, const char* value);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_BOOLEAN_V1)(
      const UNIVERSALMEDIA_ADDON_INSTANCE_HDL hdl, const char* name, bool value);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_INTEGER_V1)(
      const UNIVERSALMEDIA_ADDON_INSTANCE_HDL hdl, const char* name, int value);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_FLOAT_V1)(
      const UNIVERSALMEDIA_ADDON_INSTANCE_HDL hdl, const char* name, float value);

  typedef struct UNIVERSALMEDIA_ADDON_INSTANCE_FUNC
  {
    PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_STRING_V1 instance_setting_change_string;
    PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_BOOLEAN_V1 instance_setting_change_boolean;
    PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_INTEGER_V1 instance_setting_change_integer;
    PFN_UNIVERSALMEDIA_ADDON_INSTANCE_SETTING_CHANGE_FLOAT_V1 instance_setting_change_float;
  } UNIVERSALMEDIA_ADDON_INSTANCE_FUNC;

  typedef struct UNIVERSALMEDIA_ADDON_INSTANCE_FUNC_CB
  {
    char* (*get_instance_user_path)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl);
    bool (*is_instance_setting_using_default)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                              const char* id);

    bool (*get_instance_setting_bool)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                      const char* id,
                                      bool* value);
    bool (*get_instance_setting_int)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                     const char* id,
                                     int* value);
    bool (*get_instance_setting_float)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                       const char* id,
                                       float* value);
    bool (*get_instance_setting_string)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                        const char* id,
                                        char** value);

    bool (*set_instance_setting_bool)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                      const char* id,
                                      bool value);
    bool (*set_instance_setting_int)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                     const char* id,
                                     int value);
    bool (*set_instance_setting_float)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                       const char* id,
                                       float value);
    bool (*set_instance_setting_string)(const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL hdl,
                                        const char* id,
                                        const char* value);
  } UNIVERSALMEDIA_ADDON_INSTANCE_FUNC_CB;

  typedef int UNIVERSALMEDIA_ADDON_INSTANCE_TYPE;

  typedef struct UNIVERSALMEDIA_ADDON_INSTANCE_INFO
  {
    UNIVERSALMEDIA_ADDON_INSTANCE_TYPE type;
    uint32_t number;
    const char* id;
    const char* version;
    UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL universalmediacenter;
    UNIVERSALMEDIA_ADDON_INSTANCE_HDL parent;
    bool first_instance;

    struct UNIVERSALMEDIA_ADDON_INSTANCE_FUNC_CB* functions;
  } UNIVERSALMEDIA_ADDON_INSTANCE_INFO;

  typedef struct UNIVERSALMEDIA_ADDON_INSTANCE_STRUCT
  {
    const UNIVERSALMEDIA_ADDON_INSTANCE_INFO* info;

    UNIVERSALMEDIA_ADDON_INSTANCE_HDL hdl;
    struct UNIVERSALMEDIA_ADDON_INSTANCE_FUNC* functions;
    union
    {
      UNIVERSALMEDIA_ADDON_FUNC_DUMMY dummy;
      struct AddonInstance_AudioDecoder* audiodecoder;
      struct AddonInstance_AudioEncoder* audioencoder;
      struct AddonInstance_ImageDecoder* imagedecoder;
      struct AddonInstance_Game* game;
      struct AddonInstance_InputStream* inputstream;
      struct AddonInstance_Peripheral* peripheral;
      struct AddonInstance_PVR* pvr;
      struct AddonInstance_Screensaver* screensaver;
      struct AddonInstance_ShaderPreset* shaderpreset;
      struct AddonInstance_VFSEntry* vfs;
      struct AddonInstance_VideoCodec* videocodec;
      struct AddonInstance_Visualization* visualization;
    };
  } UNIVERSALMEDIA_ADDON_INSTANCE_STRUCT;

  /*! @brief Standard undefined pointer handle */
  typedef void* UNIVERSALMEDIA_HANDLE;

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_addon
  {
    char* (*get_addon_path)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl);
    char* (*get_lib_path)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl);
    char* (*get_user_path)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl);
    char* (*get_temp_path)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl);

    char* (*get_localized_string)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, long label_id);

    bool (*open_settings_dialog)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl);
    bool (*is_setting_using_default)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id);

    bool (*get_setting_bool)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, bool* value);
    bool (*get_setting_int)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, int* value);
    bool (*get_setting_float)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, float* value);
    bool (*get_setting_string)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, char** value);

    bool (*set_setting_bool)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, bool value);
    bool (*set_setting_int)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, int value);
    bool (*set_setting_float)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, float value);
    bool (*set_setting_string)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id, const char* value);

    char* (*get_addon_info)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* id);

    char* (*get_type_version)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, int type);
    void* (*get_interface)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const char* name, const char* version);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_addon;

  /*!
   * @brief Callback function tables from addon to Universal Media Center
   * Set complete from Universal Media Center!
   */
  typedef struct AddonToUniversal Media CenterFuncTable_Addon
  {
    // Pointer inside Universal Media Center, used on callback functions to give related handle
    // class, for this ADDON::CAddonDll inside Universal Media Center.
    UNIVERSALMEDIA_ADDON_BACKEND_HDL universalmediacenterBase;

    void (*free_string)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, char* str);
    void (*free_string_array)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, char** arr, int numElements);
    void (*addon_log_msg)(const UNIVERSALMEDIA_ADDON_BACKEND_HDL hdl, const int loglevel, const char* msg);

    struct AddonToUniversal Media CenterFuncTable_universalmediacenter* universalmediacenter;
    struct AddonToUniversal Media CenterFuncTable_universalmediacenter_addon* universalmediacenter_addon;
    struct AddonToUniversal Media CenterFuncTable_universalmediacenter_audioengine* universalmediacenter_audioengine;
    struct AddonToUniversal Media CenterFuncTable_universalmediacenter_filesystem* universalmediacenter_filesystem;
    struct AddonToUniversal Media CenterFuncTable_* ;
    struct AddonToUniversal Media CenterFuncTable_universalmediacenter_network* universalmediacenter_network;
  } AddonToUniversal Media CenterFuncTable_Addon;

  typedef ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_CREATE_V1)(
      const UNIVERSALMEDIA_ADDON_INSTANCE_BACKEND_HDL first_instance, UNIVERSALMEDIA_ADDON_HDL* hdl);
  typedef void(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_DESTROY_V1)(const UNIVERSALMEDIA_ADDON_HDL hdl);
  typedef ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_CREATE_INSTANCE_V1)(
      const UNIVERSALMEDIA_ADDON_HDL hdl, struct UNIVERSALMEDIA_ADDON_INSTANCE_STRUCT* instance);
  typedef void(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_DESTROY_INSTANCE_V1)(
      const UNIVERSALMEDIA_ADDON_HDL hdl, struct UNIVERSALMEDIA_ADDON_INSTANCE_STRUCT* instance);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_STRING_V1)(
      const UNIVERSALMEDIA_ADDON_HDL hdl, const char* name, const char* value);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_BOOLEAN_V1)(
      const UNIVERSALMEDIA_ADDON_HDL hdl, const char* name, bool value);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_INTEGER_V1)(
      const UNIVERSALMEDIA_ADDON_HDL hdl, const char* name, int value);
  typedef enum ADDON_STATUS(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_FLOAT_V1)(
      const UNIVERSALMEDIA_ADDON_HDL hdl, const char* name, float value);

  /*!
   * @brief Function tables from Universal Media Center to addon
   */
  typedef struct Universal Media CenterToAddonFuncTable_Addon
  {
    PFN_UNIVERSALMEDIA_ADDON_CREATE_V1 create;
    PFN_UNIVERSALMEDIA_ADDON_DESTROY_V1 destroy;
    PFN_UNIVERSALMEDIA_ADDON_CREATE_INSTANCE_V1 create_instance;
    PFN_UNIVERSALMEDIA_ADDON_DESTROY_INSTANCE_V1 destroy_instance;
    PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_STRING_V1 setting_change_string;
    PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_BOOLEAN_V1 setting_change_boolean;
    PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_INTEGER_V1 setting_change_integer;
    PFN_UNIVERSALMEDIA_ADDON_SETTING_CHANGE_FLOAT_V1 setting_change_float;
  } Universal Media CenterToAddonFuncTable_Addon;

  /*!
   * @brief Main structure passed from universalmediacenter to addon with basic information needed to
   * create add-on.
   */
  typedef struct AddonGlobalInterface
  {
    // Pointer of first created instance, used in case this add-on goes with single way
    // Set from Universal Media Center!
    struct UNIVERSALMEDIA_ADDON_INSTANCE_STRUCT* firstUniversal Media CenterInstance;

    // Pointer to master base class inside add-on
    // Set from addon header (addon::CAddonBase)!
    UNIVERSALMEDIA_ADDON_HDL addonBase;

    // Pointer to a instance used on single way (together with this class)
    // Set from addon header (addon::IAddonInstance)!
    UNIVERSALMEDIA_ADDON_INSTANCE_HDL globalSingleInstance;

    // Callback function tables from addon to Universal Media Center
    // Set from Universal Media Center!
    AddonToUniversal Media CenterFuncTable_Addon* toUniversal Media Center;

    // Function tables from Universal Media Center to addon
    // Set from addon header!
    Universal Media CenterToAddonFuncTable_Addon* toAddon;
  } AddonGlobalInterface;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !C_API_ADDON_BASE_H */
