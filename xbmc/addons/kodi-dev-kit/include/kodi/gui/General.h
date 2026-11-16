/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../AddonBase.h"
#include "../c-api/gui/general.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{

//==============================================================================
/// @addtogroup cpp_universalmediacenter_gui_general
/// Permits the use of the required functions of the add-on to Universal Media Center.
///
/// These are pure functions them no other initialization need.
///
/// It has the header @ref universalmediacenter/gui/General.h "#include <universalmediacenter/gui/General.h>" be included
/// to enjoy it.
///

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Performs a graphical lock of rendering engine.
///
inline void ATTR_DLL_LOCAL Lock()
{
  using namespace ::universalmediacenter::addon;
  CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->lock();
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Performs a graphical unlock of previous locked rendering engine.
///
inline void ATTR_DLL_LOCAL Unlock()
{
  using namespace ::universalmediacenter::addon;
  CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->unlock();
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Return the the current screen height with pixel.
///
/// @return Screen height with pixel
///
inline int ATTR_DLL_LOCAL GetScreenHeight()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_screen_height(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Return the the current screen width with pixel.
///
/// @return Screen width with pixel
///
inline int ATTR_DLL_LOCAL GetScreenWidth()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_screen_width(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Return the the current screen rendering resolution.
///
/// @return Current screen rendering resolution
///
inline int ATTR_DLL_LOCAL GetVideoResolution()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_video_resolution(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Returns the id for the current 'active' dialog as an integer.
///
/// @return The currently active dialog Id
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// ..
/// int wid = universalmediacenter::gui::GetCurrentWindowDialogId();
/// ..
/// ~~~~~~~~~~~~~
///
inline int ATTR_DLL_LOCAL GetCurrentWindowDialogId()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_current_window_dialog_id(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Returns the id for the current 'active' window as an integer.
///
/// @return The currently active window Id
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// ..
/// int wid = universalmediacenter::gui::GetCurrentWindowId();
/// ..
/// ~~~~~~~~~~~~~
///
inline int ATTR_DLL_LOCAL GetCurrentWindowId()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_current_window_id(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief To get hardware specific device context interface.
///
/// @return A pointer to the used device with @ref cpp_universalmediacenter_Defs_HardwareContext "universalmediacenter::HardwareContext"
///
/// @warning This function is only be supported under Windows, on all other
/// OS it return `nullptr`!
///
/// @note Returned Windows class pointer is `ID3D11DeviceContext1`.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <d3d11_1.h>
/// ..
/// ID3D11DeviceContext1* context = static_cast<ID3D11DeviceContext1*>(universalmediacenter::gui::GetHWContext());
/// ..
/// ~~~~~~~~~~~~~
///
inline universalmediacenter::HardwareContext GetHWContext()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_hw_context(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_general
/// @brief Get Adjust refresh rate setting status.
///
/// @return The Adjust refresh rate setting status
///
inline AdjustRefreshRateStatus ATTR_DLL_LOCAL GetAdjustRefreshRateStatus()
{
  using namespace ::universalmediacenter::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->general->get_adjust_refresh_rate_status(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------

} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
