/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../AddonBase.h"
#include "../c-api/addon-instance/screensaver.h"
#include "../gui/renderHelper.h"

#ifdef __cplusplus
namespace universalmediacenter
{
namespace addon
{

//==============================================================================
/// @addtogroup cpp_universalmediacenter_addon_screensaver
/// @brief \cpp_class{ universalmediacenter::addon::CInstanceScreensaver }
/// **Screensaver add-on instance**
///
/// A screensaver is a Universal Media Center addon that fills the screen with moving images or
/// patterns when the computer is not in use. Initially designed to prevent
/// phosphor burn-in on CRT and plasma computer monitors (hence the name),
/// screensavers are now used primarily for entertainment, security or to
/// display system status information.
///
/// Include the header @ref Screensaver.h "#include <universalmediacenter/addon-instance/ScreenSaver.h>"
/// to use this class.
///
/// This interface allows the creating of screensavers for Universal Media Center, based upon
/// **DirectX** or/and **OpenGL** rendering with `C++` code.
///
/// The interface is small and easy usable. It has three functions:
///
/// * <b><c>Start()</c></b> - Called on creation
/// * <b><c>Render()</c></b> - Called at render time
/// * <b><c>Stop()</c></b> - Called when the screensaver has no work
///
/// Additionally, there are several @ref cpp_universalmediacenter_addon_screensaver_CB "other functions"
/// available in which the child class can ask about the current hardware,
/// including the device, display and several other parts.
///
/// ----------------------------------------------------------------------------
///
/// Here is an example of what the <b>`addon.xml.in`</b> would look like for an
/// screensaver addon:
///
/// ~~~~~~~~~~~~~{.xml}
/// <?xml version="1.0" encoding="UTF-8"?>
/// <addon
///   id="screensaver.myspecialnamefor"
///   version="1.0.0"
///   name="My special screensaver addon"
///   provider-name="Your Name">
///   <requires>@ADDON_DEPENDS@</requires>
///   <extension
///     point="xbmc.ui.screensaver"
///     library_@PLATFORM@="@LIBRARY_FILENAME@"/>
///   <extension point="xbmc.addon.metadata">
///     <summary lang="en_GB">My screensaver addon</summary>
///     <description lang="en_GB">My screensaver addon description</description>
///     <platform>@PLATFORM@</platform>
///   </extension>
/// </addon>
/// ~~~~~~~~~~~~~
///
/// Description to screensaver related addon.xml values:
/// | Name                          | Description
/// |:------------------------------|----------------------------------------
/// | <b>`point`</b>                | Addon type specification<br>At all addon types and for this kind always <b>"xbmc.ui.screensaver"</b>.
/// | <b>`library_@PLATFORM@`</b>   | Sets the used library name, which is automatically set by cmake at addon build.
///
/// @remark For more detailed description of the <b>`addon.xml`</b>, see also https://universalmediacenter.wiki/view/Addon.xml.
///
///
/// --------------------------------------------------------------------------
///
/// **Here is an example of the minimum required code to start a screensaver:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/addon-instance/Screensaver.h>
///
/// class CMyScreenSaver : public universalmediacenter::addon::CAddonBase,
///                        public universalmediacenter::addon::CInstanceScreensaver
/// {
/// public:
///   CMyScreenSaver();
///
///   bool Start() override;
///   void Render() override;
/// };
///
/// CMyScreenSaver::CMyScreenSaver()
/// {
///   ...
/// }
///
/// bool CMyScreenSaver::Start()
/// {
///   ...
///   return true;
/// }
///
/// void CMyScreenSaver::Render()
/// {
///   ...
/// }
///
/// ADDONCREATOR(CMyScreenSaver)
/// ~~~~~~~~~~~~~
///
///
/// --------------------------------------------------------------------------
///
///
/// **Here is another example where the screensaver is used together with
/// other instance types:**
///
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/addon-instance/Screensaver.h>
///
/// class CMyScreenSaver : public universalmediacenter::addon::CInstanceScreensaver
/// {
/// public:
///   CMyScreenSaver(const universalmediacenter::addon::IInstanceInfo& instance);
///
///   bool Start() override;
///   void Render() override;
/// };
///
/// CMyScreenSaver::CMyScreenSaver(const universalmediacenter::addon::IInstanceInfo& instance)
///   : CInstanceScreensaver(instance)
/// {
///   ...
/// }
///
/// bool CMyScreenSaver::Start()
/// {
///   ...
///   return true;
/// }
///
/// void CMyScreenSaver::Render()
/// {
///   ...
/// }
///
///
/// //----------------------------------------------------------------------
///
/// class CMyAddon : public universalmediacenter::addon::CAddonBase
/// {
/// public:
///   CMyAddon() = default;
///   ADDON_STATUS CreateInstance(const universalmediacenter::addon::IInstanceInfo& instance,
///                               UNIVERSALMEDIA_ADDON_INSTANCE_HDL& hdl) override;
/// };
///
/// // If you use only one instance in your add-on, can be instanceType and
/// // instanceID ignored
/// ADDON_STATUS CMyAddon::CreateInstance(const universalmediacenter::addon::IInstanceInfo& instance,
///                                       UNIVERSALMEDIA_ADDON_INSTANCE_HDL& hdl)
/// {
///   if (instance.IsType(ADDON_INSTANCE_SCREENSAVER))
///   {
///     universalmediacenter::Log(ADDON_LOG_INFO, "Creating my Screensaver");
///     hdl = new CMyScreenSaver(instance, version);
///     return ADDON_STATUS_OK;
///   }
///   else if (...)
///   {
///     ...
///   }
///   return ADDON_STATUS_UNKNOWN;
/// }
///
/// ADDONCREATOR(CMyAddon)
/// ~~~~~~~~~~~~~
///
/// The destruction of the example class `CMyScreenSaver` is called from
/// Universal Media Center's header. Manually deleting the add-on instance is not required.
///
class ATTR_DLL_LOCAL CInstanceScreensaver : public IAddonInstance
{
public:
  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief Screensaver class constructor.
  ///
  /// Used by an add-on that only supports screensavers.
  ///
  CInstanceScreensaver()
    : IAddonInstance(IInstanceInfo(CPrivateBase::m_interface->firstUniversal Media CenterInstance))
  {
    if (CPrivateBase::m_interface->globalSingleInstance != nullptr)
      throw std::logic_error("universalmediacenter::addon::CInstanceScreensaver: Creation of more as one in single "
                             "instance way is not allowed!");

    SetAddonStruct(CPrivateBase::m_interface->firstUniversal Media CenterInstance);
    CPrivateBase::m_interface->globalSingleInstance = this;
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief Screensaver class constructor used to support multiple instance
  /// types.
  ///
  /// @param[in] instance The instance value given to
  ///                     <b>`universalmediacenter::addon::CAddonBase::CreateInstance(...)`</b>.
  /// @param[in] universalmediacenterVersion [opt] Version used in Universal Media Center for this instance, to
  ///                        allow compatibility to older Universal Media Center versions.
  ///
  /// @note Recommended to set <b>`universalmediacenterVersion`</b>.
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Here's example about the use of this:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// class CMyScreenSaver : public universalmediacenter::addon::CInstanceScreensaver
  /// {
  /// public:
  ///   CMyScreenSaver(UNIVERSALMEDIA_HANDLE instance, const std::string& universalmediacenterVersion)
  ///     : universalmediacenter::addon::CInstanceScreensaver(instance, universalmediacenterVersion)
  ///   {
  ///      ...
  ///   }
  ///
  ///   ...
  /// };
  ///
  /// ADDON_STATUS CMyAddon::CreateInstance(int instanceType,
  ///                                       const std::string& instanceID,
  ///                                       UNIVERSALMEDIA_HANDLE instance,
  ///                                       const std::string& version,
  ///                                       UNIVERSALMEDIA_HANDLE& addonInstance)
  /// {
  ///   universalmediacenter::Log(ADDON_LOG_INFO, "Creating my screensaver");
  ///   addonInstance = new CMyScreenSaver(instance, version);
  ///   return ADDON_STATUS_OK;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  explicit CInstanceScreensaver(const IInstanceInfo& instance) : IAddonInstance(instance)
  {
    if (CPrivateBase::m_interface->globalSingleInstance != nullptr)
      throw std::logic_error("universalmediacenter::addon::CInstanceScreensaver: Creation of multiple together "
                             "with single instance way is not allowed!");

    SetAddonStruct(instance);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief Destructor.
  ///
  ~CInstanceScreensaver() override = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief Used to notify the screensaver that it has been started.
  ///
  /// @return true if the screensaver was started successfully, false otherwise
  ///
  virtual bool Start() { return true; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief Used to inform the screensaver that the rendering control was
  /// stopped.
  ///
  virtual void Stop() {}
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief Used to indicate when the add-on should render
  ///
  virtual void Render() {}
  //----------------------------------------------------------------------------

  //============================================================================
  /// @defgroup cpp_universalmediacenter_addon_screensaver_CB Information functions
  /// @ingroup cpp_universalmediacenter_addon_screensaver
  /// @brief **To get info about the device, display and several other parts**
  ///
  ///@{

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver_CB
  /// @brief Device that represents the display adapter.
  ///
  /// @return A pointer to the device
  ///
  /// @note This is only available on **DirectX**, It us unused (`nullptr`) on
  /// **OpenGL**
  ///
  /// This value can also be becomed by @ref universalmediacenter::gui::GetHWContext() and is
  /// recommended to use.
  ///
  ///-------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <d3d11_1.h>
  /// ..
  /// // Note: Device() there is used inside addon child class about
  /// // universalmediacenter::addon::CInstanceVisualization
  /// ID3D11DeviceContext1* context = static_cast<ID3D11DeviceContext1*>(universalmediacenter::addon::CInstanceVisualization::Device());
  /// ..
  /// ~~~~~~~~~~~~~
  ///
  inline universalmediacenter::HardwareContext Device() { return m_props.device; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver_CB
  /// @brief Returns the X position of the rendering window.
  ///
  /// @return The X position, in pixels
  ///
  inline int X() { return m_props.x; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver_CB
  /// @brief Returns the Y position of the rendering window.
  ///
  /// @return The Y position, in pixels
  ///
  inline int Y() { return m_props.y; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver_CB
  /// @brief Returns the width of the rendering window.
  ///
  /// @return The width, in pixels
  ///
  inline int Width() { return m_props.width; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver_CB
  /// @brief Returns the height of the rendering window.
  ///
  /// @return The height, in pixels
  ///
  inline int Height() { return m_props.height; }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_addon_screensaver_CB
  /// @brief Pixel aspect ratio (often abbreviated PAR) is a ratio that
  /// describes how the width of a pixel compares to the height of that pixel.
  ///
  /// @return The pixel aspect ratio used by the display
  ///
  inline float PixelRatio() { return m_props.pixelRatio; }
  //----------------------------------------------------------------------------

  ///@}

private:
  void SetAddonStruct(UNIVERSALMEDIA_ADDON_INSTANCE_STRUCT* instance)
  {
    instance->hdl = this;
    instance->screensaver->toAddon->start = ADDON_start;
    instance->screensaver->toAddon->stop = ADDON_stop;
    instance->screensaver->toAddon->render = ADDON_render;

    instance->screensaver->toUniversal Media Center->get_properties(instance->info->universalmediacenter, &m_props);
  }

  inline static bool ADDON_start(const UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL hdl)
  {
    CInstanceScreensaver* thisClass = static_cast<CInstanceScreensaver*>(hdl);
    thisClass->m_renderHelper = universalmediacenter::gui::GetRenderHelper();
    return thisClass->Start();
  }

  inline static void ADDON_stop(const UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL hdl)
  {
    CInstanceScreensaver* thisClass = static_cast<CInstanceScreensaver*>(hdl);
    thisClass->Stop();
    thisClass->m_renderHelper = nullptr;
  }

  inline static void ADDON_render(const UNIVERSALMEDIA_ADDON_SCREENSAVER_HDL hdl)
  {
    CInstanceScreensaver* thisClass = static_cast<CInstanceScreensaver*>(hdl);

    if (!thisClass->m_renderHelper)
      return;
    thisClass->m_renderHelper->Begin();
    thisClass->Render();
    thisClass->m_renderHelper->End();
  }

  /*
   * Background render helper holds here and in addon base.
   * In addon base also to have for the others, and stored here for the worst
   * case where this class is independent from base and base becomes closed
   * before.
   *
   * This is on Universal Media Center with GL unused and the calls to there are empty (no work)
   * On Universal Media Center with Direct X where angle is present becomes this used.
   */
  std::shared_ptr<universalmediacenter::gui::IRenderHelper> m_renderHelper;

  UNIVERSALMEDIA_ADDON_SCREENSAVER_PROPS m_props = {};
};

} /* namespace addon */
} /* namespace universalmediacenter */
#endif /* __cplusplus */
