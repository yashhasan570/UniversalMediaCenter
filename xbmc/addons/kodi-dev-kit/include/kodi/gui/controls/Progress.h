/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../c-api/gui/controls/progress.h"
#include "../Window.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace controls
{

//==============================================================================
/// @defgroup cpp_universalmediacenter_gui_windows_controls_CProgress Control Progress
/// @ingroup cpp_universalmediacenter_gui_windows_controls
/// @brief @cpp_class{ universalmediacenter::gui::controls::CProgress }
/// **Window control to show the progress of a particular operation**\n
/// The progress control is used to show the progress of an item that may take
/// a long time, or to show how far through a movie you are.
///
/// You can choose  the position, size, and look of the progress control.
///
/// It has the header @ref Progress.h "#include <universalmediacenter/gui/controls/Progress.h>"
/// be included to enjoy it.
///
/// Here you find the needed skin part for a @ref Progress_Control "progress control".
///
/// @note The call of the control is only possible from the corresponding
/// window as its class and identification number is required.
///
class ATTR_DLL_LOCAL CProgress : public CAddonGUIControlBase
{
public:
  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CProgress
  /// @brief Construct a new control.
  ///
  /// @param[in] window Related window control class
  /// @param[in] controlId Used skin xml control id
  ///
  CProgress(CWindow* window, int controlId) : CAddonGUIControlBase(window)
  {
    m_controlHandle = m_interface->universalmediacenter_gui->window->get_control_progress(
        m_interface->universalmediacenterBase, m_Window->GetControlHandle(), controlId);
    if (!m_controlHandle)
      universalmediacenter::Log(ADDON_LOG_FATAL,
                "universalmediacenter::gui::controls::CProgress can't create control class from Universal Media Center !!!");
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CProgress
  /// @brief Destructor.
  ///
  ~CProgress() override = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CProgress
  /// @brief Set the control on window to visible.
  ///
  /// @param[in] visible If true visible, otherwise hidden
  ///
  void SetVisible(bool visible)
  {
    m_interface->universalmediacenter_gui->control_progress->set_visible(m_interface->universalmediacenterBase, m_controlHandle,
                                                         visible);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CProgress
  /// @brief To set Percent position of control.
  ///
  /// @param[in] percent The percent position to use
  ///
  void SetPercentage(float percent)
  {
    m_interface->universalmediacenter_gui->control_progress->set_percentage(m_interface->universalmediacenterBase, m_controlHandle,
                                                            percent);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CProgress
  /// @brief Get the active percent position of progress bar.
  ///
  /// @return Progress position as percent
  ///
  float GetPercentage() const
  {
    return m_interface->universalmediacenter_gui->control_progress->get_percentage(m_interface->universalmediacenterBase,
                                                                   m_controlHandle);
  }
  //----------------------------------------------------------------------------
};

} /* namespace controls */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
