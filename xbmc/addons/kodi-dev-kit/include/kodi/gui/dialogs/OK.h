/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../AddonBase.h"
#include "../../c-api/gui/dialogs/ok.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace dialogs
{

//==============================================================================
/// @defgroup cpp_universalmediacenter_gui_dialogs_OK Dialog OK
/// @ingroup cpp_universalmediacenter_gui_dialogs
/// @{
/// @brief @cpp_namespace{ universalmediacenter::gui::dialogs::OK }
/// **OK dialog**\n
/// The functions listed below permit the call of a dialogue of information, a
/// confirmation of the user by press from OK required.
///
/// It has the header @ref OK.h "#include <universalmediacenter/gui/dialogs/OK.h>"
/// be included to enjoy it.
///
namespace OK
{
//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_dialogs_OK
/// @brief Use dialog to inform user with text and confirmation with OK with
/// continued string.
///
/// @param[in] heading Dialog heading.
/// @param[in] text Multi-line text.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/gui/dialogs/OK.h>
/// ...
/// universalmediacenter::gui::dialogs::OK::ShowAndGetInput("Test dialog", "Hello World!\nI'm a call from add-on\n :) :D");
/// ~~~~~~~~~~~~~
///
inline void ATTR_DLL_LOCAL ShowAndGetInput(const std::string& heading, const std::string& text)
{
  using namespace ::universalmediacenter::addon;
  CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->dialogOK->show_and_get_input_single_text(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, heading.c_str(), text.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp_universalmediacenter_gui_dialogs_OK
/// @brief Use dialog to inform user with text and confirmation with OK with
/// strings separated to the lines.
///
/// @param[in] heading Dialog heading.
/// @param[in] line0 Line #1 text.
/// @param[in] line1 Line #2 text.
/// @param[in] line2 Line #3 text.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/gui/dialogs/OK.h>
/// ...
/// universalmediacenter::gui::dialogs::OK::ShowAndGetInput("Test dialog", "Hello World!", "I'm a call from add-on", " :) :D");
/// ~~~~~~~~~~~~~
///
inline void ATTR_DLL_LOCAL ShowAndGetInput(const std::string& heading,
                                           const std::string& line0,
                                           const std::string& line1,
                                           const std::string& line2)
{
  using namespace ::universalmediacenter::addon;
  CPrivateBase::m_interface->toUniversal Media Center->universalmediacenter_gui->dialogOK->show_and_get_input_line_text(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, heading.c_str(), line0.c_str(), line1.c_str(),
      line2.c_str());
}
//------------------------------------------------------------------------------
} // namespace OK
/// @}

} /* namespace dialogs */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
