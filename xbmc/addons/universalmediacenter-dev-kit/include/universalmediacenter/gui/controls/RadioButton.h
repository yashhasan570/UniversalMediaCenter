/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../c-api/gui/controls/radio_button.h"
#include "../Window.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace controls
{

//==============================================================================
/// @defgroup cpp__windows_controls_CRadioButton Control Radio Button
/// @ingroup cpp__windows_controls
/// @brief @cpp_class{ gui::controls::CRadioButton }
/// **Window control for a radio button (as used for on/off settings)**\n
/// The radio button control is used for creating push button on/off settings
/// in Universal Media Center.
///
/// You can choose the position, size, and look of the button. When the user
/// clicks on the radio button, the state will change, toggling the extra
/// textures (textureradioon and textureradiooff). Used for settings
/// controls.
///
/// It has the header @ref RadioButton.h "#include <universalmediacenter/gui/controls/RadioButton.h>"
/// be included to enjoy it.
///
/// Here you find the needed skin part for a @ref Radio_button_control "radio button control".
///
/// @note The call of the control is only possible from the corresponding
/// window as its class and identification number is required.
///
///
/// --------------------------------------------------------------------------
/// **Example:**
/// ~~~~~~~~~~~~cpp
/// #include <universalmediacenter/gui/Window.h>
///
/// #define MY_RADIO_BUTTON_CONTROL 1
///
/// class CMyWindow : public gui::CWindow
/// {
/// public:
///   CMyWindow()
///
///   void ShowWindow();
///
///   bool OnInit() override;
///   bool OnClick(int controlId) override;
///
/// private:
///   gui::controls::CSpin m_myRadioButtonControl;
/// };
///
/// CMyWindow::CMyWindow()
///   : gui::CWindow("my_skin.xml", "skin.estuary", true, false),
///     m_myRadioButtonControl(this, MY_RADIO_BUTTON_CONTROL)
/// {
/// }
///
/// void CMyWindow::ShowWindow()
/// {
///   gui::CWindow::DoModal();
/// }
///
/// bool CMyWindow::OnInit()
/// {
///   m_myRadioButtonControl.SetSelected(false); // can also on skin set to default
///   return true;
/// }
///
/// bool CMyWindow::OnClick(int controlId)
/// {
///   if (controlId == MY_RADIO_BUTTON_CONTROL)
///   {
///     bool selected = m_myRadioButtonControl.IsSelected();
///     ...
///     }
///     return true;
///   }
///   return false;
/// }
/// ~~~~~~~~~~~~
///
class ATTR_DLL_LOCAL CRadioButton : public CAddonGUIControlBase
{
public:
  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief Construct a new control.
  ///
  /// @param[in] window Related window control class
  /// @param[in] controlId  Used skin xml control id
  ///
  CRadioButton(CWindow* window, int controlId) : CAddonGUIControlBase(window)
  {
    m_controlHandle = m_interface->->window->get_control_radio_button(
        m_interface->universalmediacenterBase, m_Window->GetControlHandle(), controlId);
    if (!m_controlHandle)
      Log(ADDON_LOG_FATAL,
                "gui::controls::CRadioButton can't create control class from Universal Media Center !!!");
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief Destructor.
  ///
  ~CRadioButton() override = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton.
  /// @brief Set the control on window to visible.
  ///
  /// @param[in] visible If true visible, otherwise hidden
  ///
  void SetVisible(bool visible)
  {
    m_interface->->control_radio_button->set_visible(m_interface->universalmediacenterBase, m_controlHandle,
                                                             visible);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief Set's the control's enabled/disabled state.
  ///
  /// @param[in] enabled If true enabled, otherwise disabled
  ///
  void SetEnabled(bool enabled)
  {
    m_interface->->control_radio_button->set_enabled(m_interface->universalmediacenterBase, m_controlHandle,
                                                             enabled);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief To set the text string on radio button.
  ///
  /// @param[in] label Text to show
  ///
  void SetLabel(const std::string& label)
  {
    m_interface->->control_radio_button->set_label(m_interface->universalmediacenterBase, m_controlHandle,
                                                           label.c_str());
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief Get the used text from control.
  ///
  /// @return Text shown
  ///
  std::string GetLabel() const
  {
    std::string label;
    char* ret = m_interface->->control_radio_button->get_label(m_interface->universalmediacenterBase,
                                                                       m_controlHandle);
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
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief To set radio button condition to on or off.
  ///
  /// @param[in] selected true set radio button to selection on, otherwise off
  ///
  void SetSelected(bool selected)
  {
    m_interface->->control_radio_button->set_selected(m_interface->universalmediacenterBase,
                                                              m_controlHandle, selected);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CRadioButton
  /// @brief Get the current selected condition of radio button.
  ///
  /// @return Selected condition
  ///
  bool IsSelected() const
  {
    return m_interface->->control_radio_button->is_selected(m_interface->universalmediacenterBase,
                                                                    m_controlHandle);
  }
  //----------------------------------------------------------------------------
};

} /* namespace controls */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
