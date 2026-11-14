/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../c-api/gui/controls/button.h"
#include "../Window.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace controls
{

//==============================================================================
/// @defgroup cpp__windows_controls_CButton Control Button
/// @ingroup cpp__windows_controls
/// @brief @cpp_class{ gui::controls::CButton }
/// **Standard push button control for window**\n
/// The button control is used for creating push buttons in Universal Media Center.
///
/// You can choose the position, size, and look of the button, as well as
/// choosing what action(s) should be performed when pushed.
///
/// It has the header @ref Button.h "#include <universalmediacenter/gui/controls/Button.h>"
/// be included to enjoy it.
///
/// Here you find the needed skin part for a @ref skin_Button_control "button control"
///
/// @note The call of the control is only possible from the corresponding
/// window as its class and identification number is required.
///
class ATTR_DLL_LOCAL CButton : public CAddonGUIControlBase
{
public:
  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief Construct a new control.
  ///
  /// @param[in] window Related window control class
  /// @param[in] controlId Used skin xml control id
  ///
  CButton(CWindow* window, int controlId) : CAddonGUIControlBase(window)
  {
    m_controlHandle = m_interface->->window->get_control_button(
        m_interface->universalmediacenterBase, m_Window->GetControlHandle(), controlId);
    if (!m_controlHandle)
      Log(ADDON_LOG_FATAL, "gui::CButton can't create control class from Universal Media Center !!!");
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief Destructor.
  ///
  ~CButton() override = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief Set the control on window to visible.
  ///
  /// @param[in] visible If true visible, otherwise hidden
  ///
  void SetVisible(bool visible)
  {
    m_interface->->control_button->set_visible(m_interface->universalmediacenterBase, m_controlHandle,
                                                       visible);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief Set's the control's enabled/disabled state.
  ///
  /// @param[in] enabled If true enabled, otherwise disabled
  ///
  void SetEnabled(bool enabled)
  {
    m_interface->->control_button->set_enabled(m_interface->universalmediacenterBase, m_controlHandle,
                                                       enabled);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief To set the text string on button.
  ///
  /// @param[in] label Text to show
  ///
  void SetLabel(const std::string& label)
  {
    m_interface->->control_button->set_label(m_interface->universalmediacenterBase, m_controlHandle,
                                                     label.c_str());
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief Get the used text from button.
  ///
  /// @return Text shown
  ///
  std::string GetLabel() const
  {
    std::string label;
    char* ret =
        m_interface->->control_button->get_label(m_interface->universalmediacenterBase, m_controlHandle);
    if (ret != nullptr)
    {
      if (std::strlen(ret))
        label = ret;
      m_interface->free_string(m_interface->universalmediacenterBase, ret);
    }
    return label;
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief If two labels are used for button becomes it set with them.
  ///
  /// @param[in] label Text for second label
  ///
  void SetLabel2(const std::string& label)
  {
    m_interface->->control_button->set_label2(m_interface->universalmediacenterBase, m_controlHandle,
                                                      label.c_str());
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CButton
  /// @brief Get the second label if present.
  ///
  /// @return Second label
  ///
  std::string GetLabel2() const
  {
    std::string label;
    char* ret =
        m_interface->->control_button->get_label2(m_interface->universalmediacenterBase, m_controlHandle);
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
