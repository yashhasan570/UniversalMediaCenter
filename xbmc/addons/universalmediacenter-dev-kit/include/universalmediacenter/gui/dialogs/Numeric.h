/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "../../AddonBase.h"
#include "../../c-api/gui/dialogs/numeric.h"

#ifdef __cplusplus

namespace universalmediacenter
{
namespace gui
{
namespace dialogs
{

//==============================================================================
/// @defgroup cpp__dialogs_Numeric Dialog Numeric
/// @ingroup cpp__dialogs
/// @{
/// @brief @cpp_namespace{ gui::dialogs::Numeric }
/// **Numeric dialogs**\n
/// The functions listed below have to be permitted by the user for the
/// representation of a numeric keyboard around an input.
///
/// The class supports several kinds, from an easy number choice up to the
/// passport Word production and their confirmation for add-on.
///
/// It has the header @ref Numeric.h "#include <universalmediacenter/gui/dialogs/Numeric.h>"
/// be included to enjoy it.
///
namespace Numeric
{
//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to get numeric new password
///
/// @param[out] newPassword String to preload into the keyboard accumulator.
///                         Overwritten with user input if return=true.
///                         Returned in MD5 format.
/// @return true if successful display and user input entry/re-entry. false if
///         unsuccessful display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndVerifyNewPassword(std::string& newPassword)
{
  using namespace ::addon;
  char* pw = nullptr;
  bool ret =
      CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_verify_new_password(
          CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, &pw);
  if (pw != nullptr)
  {
    newPassword = pw;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, pw);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
///
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to verify numeric password.
///
/// @param[in] password             Password to compare with user input, need
///                                 in MD5 format.
/// @param[in] heading              Heading to display
/// @param[in] retries              If greater than 0, shows "Incorrect
///                                 password, %d retries left" on dialog
///                                 line 2, else line 2 is blank.
/// @return                         Possible values:
///                                 - 0 if successful display and user input.
///                                 - 1 if unsuccessful input.
///                                 - -1 if no user input or canceled editing.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <stdio.h>      // fprintf
/// #include <universalmediacenter/General.h>
/// #include <universalmediacenter/gui/dialogs/Numeric.h>
///
/// // The example below shows the complete use of keyboard dialog for password
/// // check. If only one check from add-on needed can be function with retries
/// // set to '0' called alone.
/// //
/// // The use of MD5 translated password is always required for the check on Universal Media Center!
///
/// int maxretries = 3;
///
/// // Password names need to be send as md5 sum to universalmediacenter.
/// std::string password = GetMD5("1234");
///
/// // To the loop about password checks.
/// int ret;
/// for (unsigned int i = 0; i < maxretries; i++)
/// {
///   // Ask the user about the password.
///   ret = gui::dialogs::Numeric::ShowAndVerifyPassword(password, "Demo numeric password call for PW '1234'", i);
///   if (ret == 0)
///   {
///     fprintf(stderr, "Numeric password successfully confirmed after '%i' tries\n", i+1);
///     break;
///   }
///   else if (ret < 0)
///   {
///     fprintf(stderr, "Canceled editing on try '%i'\n", i+1);
///     break;
///   }
///   else // if (ret > 0)
///   {
///     fprintf(stderr, "Wrong numeric password entered on try '%i'\n", i+1);
///   }
/// }
/// ~~~~~~~~~~~~~
///
inline int ATTR_DLL_LOCAL ShowAndVerifyPassword(const std::string& password,
                                                const std::string& heading,
                                                int retries)
{
  using namespace ::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_verify_password(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, password.c_str(), heading.c_str(), retries);
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to verify numeric password
///
/// @param[in,out] toVerify Value to compare against user input.
/// @param[in] heading Heading to display
/// @param[in] verifyInput If set as true we verify the users input versus
///                        toVerify.
/// @return true if successful display and user input. false if unsuccessful
/// display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndVerifyInput(std::string& toVerify,
                                              const std::string& heading,
                                              bool verifyInput)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_verify_input(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, toVerify.c_str(), &retString, heading.c_str(),
      verifyInput);
  if (retString != nullptr)
  {
    toVerify = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to get time value.
///
/// @param[out] time Overwritten with user input if return=true and time
///                  inserted.
/// @param[in] heading Heading to display.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <stdio.h>      // printf
/// #include <time.h>       // time_t, struct tm, time, localtime, strftime
/// #include <universalmediacenter/gui/dialogs/Numeric.h>
///
/// time_t rawtime;
/// struct tm * timeinfo;
/// char buffer [10];
///
/// time (&rawtime);
/// timeinfo = localtime(&rawtime);
/// bool bRet = gui::dialogs::Numeric::ShowAndGetTime(*timeinfo, "Selected time test call");
/// strftime(buffer, sizeof(buffer), "%H:%M.", timeinfo);
/// printf("Selected time it's %s and was on Dialog %s\n", buffer, bRet ? "OK" : "Canceled");
/// ~~~~~~~~~~~~~
///
inline bool ATTR_DLL_LOCAL ShowAndGetTime(tm& time, const std::string& heading)
{
  using namespace ::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_get_time(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, &time, heading.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to get date value.
///
/// @param[in,out] date Overwritten with user input if return=true and date
///                     inserted.
/// @param[in] heading Heading to display
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <stdio.h>      // printf
/// #include <time.h>       // time_t, struct tm, time, localtime, strftime
/// #include <universalmediacenter/gui/dialogs/Numeric.h>
///
/// time_t rawtime;
/// struct tm * timeinfo;
/// char buffer [20];
///
/// time (&rawtime);
/// timeinfo = localtime(&rawtime);
/// bool bRet = gui::dialogs::Numeric::ShowAndGetDate(*timeinfo, "Selected date test call");
/// strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
/// printf("Selected date it's %s and was on Dialog %s\n", buffer, bRet ? "OK" : "Canceled");
/// ~~~~~~~~~~~~~
///
inline bool ATTR_DLL_LOCAL ShowAndGetDate(tm& date, const std::string& heading)
{
  using namespace ::addon;
  return CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_get_date(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, &date, heading.c_str());
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to get a IP
///
/// @param[in,out] ipAddress Overwritten with user input if return=true and
///                          IP address inserted.
/// @param[in] heading Heading to display.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndGetIPAddress(std::string& ipAddress, const std::string& heading)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_get_ip_address(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, ipAddress.c_str(), &retString, heading.c_str());
  if (retString != nullptr)
  {
    ipAddress = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Use dialog to get normal number.
///
/// @param[in,out] input Overwritten with user input if return=true and time
///                      in seconds inserted
/// @param[in] heading Heading to display
/// @param[in] autoCloseTimeoutMs [opt] To close the dialog after a specified
///                               time, in milliseconds, default is 0
///                               which keeps the dialog open
///                                 indefinitely.
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
///   #include <stdio.h>      // printf
///   #include <stdlib.h>     // strtoull (C++11)
///   #include <universalmediacenter/gui/dialogs/Numeric.h>
///
///   std::string number;
///   bool bRet = gui::dialogs::Numeric::ShowAndGetNumber(number, "Number test call");
///   printf("Written number input is : %llu and was %s\n",
///                  strtoull(number.c_str(), nullptr, 0), bRet ? "OK" : "Canceled");
/// ~~~~~~~~~~~~~
///
inline bool ATTR_DLL_LOCAL ShowAndGetNumber(std::string& input,
                                            const std::string& heading,
                                            unsigned int autoCloseTimeoutMs = 0)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_get_number(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, input.c_str(), &retString, heading.c_str(),
      autoCloseTimeoutMs);
  if (retString != nullptr)
  {
    input = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------

//==============================================================================
/// @ingroup cpp__dialogs_Numeric
/// @brief Show numeric keypad to get seconds.
///
/// @param[in,out] time Overwritten with user input if return=true and time
///                     in seconds inserted.
/// @param[in] heading Heading to display
/// @return true if successful display and user input. false if unsuccessful
///         display, no user input, or canceled editing.
///
inline bool ATTR_DLL_LOCAL ShowAndGetSeconds(std::string& time, const std::string& heading)
{
  using namespace ::addon;
  char* retString = nullptr;
  bool ret = CPrivateBase::m_interface->toUniversal Media Center->->dialogNumeric->show_and_get_seconds(
      CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase, time.c_str(), &retString, heading.c_str());
  if (retString != nullptr)
  {
    time = retString;
    CPrivateBase::m_interface->toUniversal Media Center->free_string(CPrivateBase::m_interface->toUniversal Media Center->universalmediacenterBase,
                                                   retString);
  }
  return ret;
}
//------------------------------------------------------------------------------
}; // namespace Numeric
/// @}

} /* namespace dialogs */
} /* namespace gui */
} /* namespace universalmediacenter */

#endif /* __cplusplus */
