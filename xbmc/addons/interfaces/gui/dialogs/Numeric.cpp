/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Numeric.h"

#include "XBDateTime.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/Numeric.h"
#include "dialogs/GUIDialogNumeric.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIDialogNumeric::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric =
      new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogNumeric();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_verify_new_password =
      show_and_verify_new_password;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_verify_password =
      show_and_verify_password;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_verify_input = show_and_verify_input;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_get_time = show_and_get_time;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_get_date = show_and_get_date;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_get_ip_address =
      show_and_get_ip_address;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_get_number = show_and_get_number;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric->show_and_get_seconds = show_and_get_seconds;
}

void Interface_GUIDialogNumeric::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogNumeric;
}

bool Interface_GUIDialogNumeric::show_and_verify_new_password(UNIVERSALMEDIA_HANDLE universalmediacenterBase, char** password)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  std::string str;
  const bool bRet{CGUIDialogNumeric::ShowAndVerifyNewPassword(str)};
  if (bRet)
    *password = strdup(str.c_str());
  return bRet;
}

int Interface_GUIDialogNumeric::show_and_verify_password(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         const char* password,
                                                         const char* heading,
                                                         int retries)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return -1;
  }

  if (!password || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (password='{}', heading='{}') "
               "on addon '{}'",
               static_cast<const void*>(password), static_cast<const void*>(heading), addon->ID());
    return -1;
  }

  std::string pw(password);
  return CGUIDialogNumeric::ShowAndVerifyPassword(pw, heading, retries);
}

bool Interface_GUIDialogNumeric::show_and_verify_input(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                       const char* verify_in,
                                                       char** verify_out,
                                                       const char* heading,
                                                       bool verify_input)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  if (!verify_in || !verify_out || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (verify_in='{}', "
               "verify_out='{}', heading='{}') on addon '{}'",
               static_cast<const void*>(verify_in), static_cast<void*>(verify_out),
               static_cast<const void*>(heading), addon->ID());
    return false;
  }

  std::string str = verify_in;
  if (CGUIDialogNumeric::ShowAndVerifyInput(str, heading, verify_input) ==
      InputVerificationResult::SUCCESS)
  {
    *verify_out = strdup(str.c_str());
    return true;
  }
  return false;
}

bool Interface_GUIDialogNumeric::show_and_get_time(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   tm* time,
                                                   const char* heading)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  if (!time || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (time='{}', heading='{}') on "
               "addon '{}'",
               static_cast<void*>(time), static_cast<const void*>(heading), addon->ID());
    return false;
  }

  UNIVERSAL MEDIA CENTER::TIME::SystemTime systemTime;
  CDateTime dateTime(*time);
  dateTime.GetAsSystemTime(systemTime);
  if (CGUIDialogNumeric::ShowAndGetTime(systemTime, heading))
  {
    dateTime = systemTime;
    dateTime.GetAsTm(*time);
    return true;
  }
  return false;
}

bool Interface_GUIDialogNumeric::show_and_get_date(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                   tm* date,
                                                   const char* heading)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  if (!date || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (date='{}', heading='{}') on "
               "addon '{}'",
               static_cast<void*>(date), static_cast<const void*>(heading), addon->ID());
    return false;
  }

  UNIVERSAL MEDIA CENTER::TIME::SystemTime systemTime;
  CDateTime dateTime(*date);
  dateTime.GetAsSystemTime(systemTime);
  if (CGUIDialogNumeric::ShowAndGetDate(systemTime, heading))
  {
    dateTime = systemTime;
    dateTime.GetAsTm(*date);
    return true;
  }
  return false;
}

bool Interface_GUIDialogNumeric::show_and_get_ip_address(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         const char* ip_address_in,
                                                         char** ip_address_out,
                                                         const char* heading)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  if (!ip_address_in || !ip_address_out || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (ip_address_in='{}', "
               "ip_address_out='{}', heading='{}') on addon '{}'",
               static_cast<const void*>(ip_address_in), static_cast<void*>(ip_address_out),
               static_cast<const void*>(heading), addon->ID());
    return false;
  }

  std::string strIP = ip_address_in;
  const bool bRet{CGUIDialogNumeric::ShowAndGetIPAddress(strIP, heading)};
  if (bRet)
    *ip_address_out = strdup(strIP.c_str());
  return bRet;
}

bool Interface_GUIDialogNumeric::show_and_get_number(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                     const char* number_in,
                                                     char** number_out,
                                                     const char* heading,
                                                     unsigned int auto_close_ms)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  if (!number_in || !number_out || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (number_in='{}', "
               "number_out='{}', heading='{}') on addon '{}'",
               static_cast<const void*>(number_in), static_cast<void*>(number_out),
               static_cast<const void*>(heading), addon->ID());
    return false;
  }

  std::string str = number_in;
  const bool bRet{CGUIDialogNumeric::ShowAndGetNumber(str, heading, auto_close_ms)};
  if (bRet)
    *number_out = strdup(str.c_str());
  return bRet;
}

bool Interface_GUIDialogNumeric::show_and_get_seconds(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                      const char* time_in,
                                                      char** time_out,
                                                      const char* heading)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return false;
  }

  if (!time_in || !time_out || !heading)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (time_in='{}', time_out='{}', "
               "heading='{}') on addon '{}'",
               static_cast<const void*>(time_in), static_cast<void*>(time_out),
               static_cast<const void*>(heading), addon->ID());
    return false;
  }

  std::string str = time_in;
  const bool bRet{CGUIDialogNumeric::ShowAndGetSeconds(str, heading)};
  if (bRet)
    *time_out = strdup(str.c_str());
  return bRet;
}

} /* namespace ADDON */
