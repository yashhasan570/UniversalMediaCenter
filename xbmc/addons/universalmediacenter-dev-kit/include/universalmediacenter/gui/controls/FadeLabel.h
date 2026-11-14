/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../c-api/gui/controls/fade_label.h"
#include "../Window.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace controls
{

//==============================================================================
/// @defgroup cpp__windows_controls_CFadeLabel Control Fade Label
/// @ingroup cpp__windows_controls
/// @brief @cpp_class{ gui::controls::CFadeLabel }
/// **Window control used to show multiple pieces of text in the same position,
/// by fading from one to the other**\n
/// The fade label control is used for displaying multiple pieces of text in
/// the same space in Universal Media Center.
///
/// You can choose the font, size, colour, location and contents of the text to
/// be displayed. The first piece of information to display fades in over 50
/// frames, then scrolls off to the left. Once it is finished scrolling off
/// screen, the second piece of information fades in and the process repeats.
/// A fade label control is not supported in a list container.
///
/// It has the header @ref FadeLabel.h "#include <universalmediacenter/gui/controls/FadeLabel.h>"
/// be included to enjoy it.
///
/// Here you find the needed skin part for a @ref Fade_Label_Control "fade label control".
///
/// @note The call of the control is only possible from the corresponding
/// window as its class and identification number is required.
///
class ATTR_DLL_LOCAL CFadeLabel : public CAddonGUIControlBase
{
public:
  //============================================================================
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief Construct a new control.
  ///
  /// @param[in] window Related window control class
  /// @param[in] controlId Used skin xml control id
  ///
  CFadeLabel(CWindow* window, int controlId) : CAddonGUIControlBase(window)
  {
    m_controlHandle = m_interface->->window->get_control_fade_label(
        m_interface->universalmediacenterBase, m_Window->GetControlHandle(), controlId);
    if (!m_controlHandle)
      Log(ADDON_LOG_FATAL,
                "gui::controls::CFadeLabel can't create control class from Universal Media Center !!!");
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief Destructor.
  ///
  ~CFadeLabel() override = default;
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief Set the control on window to visible.
  ///
  /// @param[in] visible If true visible, otherwise hidden
  ///
  void SetVisible(bool visible)
  {
    m_interface->->control_fade_label->set_visible(m_interface->universalmediacenterBase, m_controlHandle,
                                                           visible);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief To add additional text string on fade label.
  ///
  /// @param[in] label Text to show
  ///
  void AddLabel(const std::string& label)
  {
    m_interface->->control_fade_label->add_label(m_interface->universalmediacenterBase, m_controlHandle,
                                                         label.c_str());
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief Get the used text from button.
  ///
  /// @return Text shown
  ///
  std::string GetLabel() const
  {
    std::string label;
    char* ret = m_interface->->control_fade_label->get_label(m_interface->universalmediacenterBase,
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
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief To enable or disable scrolling on fade label.
  ///
  /// @param[in] scroll To enable scrolling set to true, otherwise is disabled
  ///
  void SetScrolling(bool scroll)
  {
    m_interface->->control_fade_label->set_scrolling(m_interface->universalmediacenterBase, m_controlHandle,
                                                             scroll);
  }
  //----------------------------------------------------------------------------

  //============================================================================
  /// @ingroup cpp__windows_controls_CFadeLabel
  /// @brief To reset al inserted labels.
  ///
  void Reset()
  {
    m_interface->->control_fade_label->reset(m_interface->universalmediacenterBase, m_controlHandle);
  }
  //----------------------------------------------------------------------------
};

} /* namespace controls */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
