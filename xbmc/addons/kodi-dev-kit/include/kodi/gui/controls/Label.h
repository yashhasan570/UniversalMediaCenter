/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../c-api/gui/controls/label.h"
#include "../Window.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace controls
{

//==============================================================================
/// @defgroup cpp_universalmediacenter_gui_windows_controls_CLabel Control Label
/// @ingroup cpp_universalmediacenter_gui_windows_controls
/// @brief @cpp_class{ universalmediacenter::gui::controls::CLabel }
/// **Window control used to show some lines of text**\n
/// The label control is used for displaying text in Universal Media Center. You can choose
/// the font, size, colour, location and contents of the text to be displayed.
///
/// It has the header @ref Label.h "#include <universalmediacenter/gui/controls/Label.h>"
/// be included to enjoy it.
///
/// Here you find the needed skin part for a @ref Label_Control "label control".
///
/// @note The call of the control is only possible from the corresponding
/// window as its class and identification number is required.
///
class ATTR_DLL_LOCAL CLabel : public CAddonGUIControlBase
{
public:
  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CLabel
  /// @brief Construct a new control.
  ///
  /// @param[in] window Related window control class
  /// @param[in] controlId Used skin xml control id
  ///
  CLabel(CWindow* window, int controlId) : CAddonGUIControlBase(window)
  {
    m_controlHandle = m_interface->universalmediacenter_gui->window->get_control_label(
        m_interface->universalmediacenterBase, m_Window->GetControlHandle(), controlId);
    if (!m_controlHandle)
      universalmediacenter::Log(ADDON_LOG_FATAL,
                "universalmediacenter::gui::controls::CLabel can't create control class from Universal Media Center !!!");
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CLabel
  /// @brief Destructor.
  ///
  ~CLabel() override = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CLabel
  /// @brief Set the control on window to visible.
  ///
  /// @param[in] visible If true visible, otherwise hidden
  ///
  void SetVisible(bool visible)
  {
    m_interface->universalmediacenter_gui->control_label->set_visible(m_interface->universalmediacenterBase, m_controlHandle,
                                                      visible);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CLabel
  /// @brief To set the text string on label.
  ///
  /// @param[in] text Text to show
  ///
  void SetLabel(const std::string& text)
  {
    m_interface->universalmediacenter_gui->control_label->set_label(m_interface->universalmediacenterBase, m_controlHandle,
                                                    text.c_str());
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp_universalmediacenter_gui_windows_controls_CLabel
  /// @brief Get the used text from control.
  ///
  /// @return Used text on label control
  ///
  std::string GetLabel() const
  {
    std::string label;
    char* ret =
        m_interface->universalmediacenter_gui->control_label->get_label(m_interface->universalmediacenterBase, m_controlHandle);
    if (ret != nullptr)
    {
      if (std::strlen(ret))
        label = ret;
      m_interface->free_string(m_interface->universalmediacenterBase, ret);
    }
    return label;
  }
  //----------------------------------------------------------------------------
};

} /* namespace controls */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
