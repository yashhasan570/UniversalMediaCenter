/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../AddonBase.h"
#include "../../c-api/gui/dialogs/keyboard.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace dialogs
{

//================================================================================
/// @defgroup cpp__dialogs_Keyboard Dialog Keyboard
/// @ingroup cpp__dialogs
/// @brief @cpp_namespace{ gui::dialogs::Keyboard }
/// **Keyboard dialogs**\n
/// The functions listed below have to be permitted by the user for the
/// representation of a keyboard around an input.
///
/// The class supports several kinds, from an easy text choice up to the
/// passport Word production and their confirmation for add-on.
///
/// It has the header @ref Keyboard.h "#include <universalmediacenter/gui/dialogs/Keyboard.h>"
/// be included to enjoy it.
///
namespace Keyboard
{
//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Show keyboard with initial value `text` and replace with  result
/// string.
///
/// @param[in,out] text Overwritten with user input if return=true.
/// @param[in] heading String shown on dialog title.
/// @param[in] allowEmptyResult Whether a blank password is valid or not.
/// @param[in] hiddenInput [opt] The inserted input is not shown as text.
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/gui/dialogs/Keyboard.h>
///
/// // The example shows the display of keyboard call dialog at Universal Media Center from the add-on.
/// // Below all values are set, however, can last two (hidden input = false and autoCloseMs = 0)
/// // to be released if not needed.
/// std::string text = "Please change me to them want you want"; // It can be leaved empty or a entry text added
/// bool bRet = ::gui::dialogs::Keyboard::ShowAndGetInput(text,
///                                                      "Demonstration text entry",
///                                                      true,
///                                                      false,
///                                                      0);
/// fprintf(stderr, "Written keyboard input is : '%s' and was %s\n",
///                   text.c_str(), bRet ? "OK" : "Canceled");
/// ~~~~~~~~~~~~~
///
inline bool ATTR_DLL_LOCAL ShowAndGetInput(std::string& text,
                                           const std::string& heading,
                                           bool allowEmptyResult,
                                           bool hiddenInput = false,
                                           unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret =
      CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->show_and_get_input_with_head(
          CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, text.c_str(), &retString, heading.c_str(),
          allowEmptyResult, hiddenInput, autoCloseMs);
  if (retString != nullptr)
  {
    text = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief The example shows the display of keyboard  call dialog  at  Universal Media Center
/// from the add-on.
///
/// @param[out] text Overwritten with user input if return=true.
/// @param[in] allowEmptyResult If set to true keyboard can also exited without
///                             entered text.
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndGetInput(std::string& text,
                                           bool allowEmptyResult,
                                           unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->show_and_get_input(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, text.c_str(), &retString, allowEmptyResult,
      autoCloseMs);
  if (retString != nullptr)
  {
    text = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Shows keyboard and prompts for a password. Differs from
/// `ShowAndVerifyNewPassword()` in that no second verification.
///
/// @param[in,out] newPassword Overwritten with user input if return=true.
/// @param[in] heading String shown on dialog title.
/// @param[in] allowEmptyResult  Whether a blank password is valid or not.
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndGetNewPassword(std::string& newPassword,
                                                 const std::string& heading,
                                                 bool allowEmptyResult,
                                                 unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard
                 ->show_and_get_new_password_with_head(
                     CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, newPassword.c_str(), &retString,
                     heading.c_str(), allowEmptyResult, autoCloseMs);
  if (retString != nullptr)
  {
    newPassword = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Shows keyboard and prompts for a password. Differs from
/// `ShowAndVerifyNewPassword()` in that no second verification.
///
/// @param[in,out] newPassword Overwritten with user input if return=true.
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndGetNewPassword(std::string& newPassword,
                                                 unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->show_and_get_new_password(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, newPassword.c_str(), &retString, autoCloseMs);
  if (retString != nullptr)
  {
    newPassword = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Show keyboard twice to get and confirm a user-entered password
/// string.
///
/// @param[out] newPassword Overwritten with user input if return=true.
/// @param[in] heading String shown on dialog title.
/// @param[in] allowEmptyResult
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <universalmediacenter/General.h>
/// #include <universalmediacenter/gui/dialogs/Keyboard.h>
///
/// // The example below shows the complete use of keyboard dialog for password
/// // check. If only one check from add-on needed can be function with retries
/// // set to '0' called alone.
/// //
/// // The use of MD5 translated password is always required for the check on Universal Media Center!
///
/// int maxretries = 3;
/// // Password names need to be send as md5 sum to universalmediacenter.
/// std::string password;
/// GetMD5("universalmediacenter", password);
///
/// // To the loop about password checks.
/// int ret;
/// for (unsigned int i = 0; i < maxretries; i++)
/// {
///   // Ask the user about the password.
///   ret = ::gui::dialogs::Keyboard::ShowAndVerifyPassword(password, "Demo password call for PW 'universalmediacenter'", i, 0);
///   if (ret == 0)
///   {
///     fprintf(stderr, "Password successfully confirmed after '%i' tries\n", i+1);
///     break;
///   }
///   else if (ret < 0)
///   {
///     fprintf(stderr, "Canceled editing on try '%i'\n", i+1);
///     break;
///   }
///   else // if (ret > 0)
///   {
///     fprintf(stderr, "Wrong password entered on try '%i'\n", i+1);
///   }
/// }
/// ~~~~~~~~~~~~~
///
inline bool ATTR_DLL_LOCAL ShowAndVerifyNewPassword(std::string& newPassword,
                                                    const std::string& heading,
                                                    bool allowEmptyResult,
                                                    unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard
                 ->show_and_verify_new_password_with_head(
                     CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, &retString, heading.c_str(),
                     allowEmptyResult, autoCloseMs);
  if (retString != nullptr)
  {
    newPassword = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Show keyboard twice to get and confirm a user-entered password
/// string.
///
/// @param[out] newPassword Overwritten with user input if return=true.
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndVerifyNewPassword(std::string& newPassword,
                                                    unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret =
      CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->show_and_verify_new_password(
          CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, &retString, autoCloseMs);
  if (retString != nullptr)
  {
    newPassword = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Show keyboard and verify user input against `password`.
///
/// @param[in,out] password Value to compare against user input.
/// @param[in] heading String shown on dialog title.
/// @param[in] retries If greater than 0, shows "Incorrect password, %d retries
///                    left" on dialog line 2, else line 2 is blank.
/// @param[in] autoCloseMs [opt] To close the dialog after a specified time, in
///                        milliseconds, default is 0 which keeps the dialog
///                        open indefinitely.
/// @return 0 if successful display and user input. 1 if unsuccessful input.
///         -1 if no user input or canceled editing.
///
inline int ATTR_DLL_LOCAL ShowAndVerifyPassword(std::string& password,
                                                const std::string& heading,
                                                int retries,
                                                unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  int ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->show_and_verify_password(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, password.c_str(), &retString, heading.c_str(),
      retries, autoCloseMs);
  if (retString != nullptr)
  {
    password = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Shows a filter related keyboard.
///
/// @param[in,out] text Overwritten with user input if return=true.
/// @param[in] searching Use dialog for search and send our search  message in
///                      safe way (only the active window needs it)
///  - header name if true is "Enter search string"
///  - header name if false is "Enter value"
/// @param autoCloseMs [opt] To close the dialog after a specified time, in
///                    milliseconds, default is 0 which keeps the dialog open
///                    indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndGetFilter(std::string& text,
                                            bool searching,
                                            unsigned int autoCloseMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->show_and_get_filter(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, text.c_str(), &retString, searching,
      autoCloseMs);
  if (retString != nullptr)
  {
    text = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Send a text to a visible keyboard.
///
/// @param[in] text Overwritten with user input if return=true.
/// @param[in] closeKeyboard [opt] The open dialog is if also closed on 'true'.
/// @return true if successful done, false if unsuccessful or keyboard not
///         present.
///
inline bool ATTR_DLL_LOCAL SendTextToActiveKeyboard(const std::string& text,
                                                    bool closeKeyboard = false)
{
  using namespace ::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->send_text_to_active_keyboard(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, text.c_str(), closeKeyboard);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Keyboard
/// @brief Check for visible keyboard on GUI.
///
/// @return true if keyboard present, false if not present
///
inline bool ATTR_DLL_LOCAL IsKeyboardActivated()
{
  using namespace ::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->->dialogKeyboard->is_keyboard_activated(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase);
}
//------------------------------------------------------------------------------
}; // namespace Keyboard

} /* namespace dialogs */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
