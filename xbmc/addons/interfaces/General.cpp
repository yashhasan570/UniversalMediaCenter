/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "General.h"

#include "CompileInfo.h"
#include "ServiceBroker.h"
#include "addons/AddonManager.h"
#include "addons/AddonVersion.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/General.h"
#include "application/ApplicationComponents.h"
#include "application/ApplicationPowerHandling.h"
#include "dialogs/GUIDialogKaiToast.h"
#include "input/keyboard/KeyboardLayout.h"
#include "input/keyboard/KeyboardLayoutManager.h"
#include "language/LangInfo.h"
#include "settings/Settings.h"
#include "settings/SettingsComponent.h"
#include "utils/CharsetConverter.h"
#include "utils/Digest.h"
#include "utils/LangCodeExpander.h"
#include "utils/MemUtils.h"
#include "utils/StringUtils.h"
#include "utils/log.h"

#include <algorithm>
#include <limits>
#include <string.h>

using namespace universalmediacenter; // addon-dev-kit namespace
using namespace UNIVERSAL MEDIA CENTER;
using UTILITY::CDigest;

namespace ADDON
{

void Interface_General::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter = static_cast<AddonToUniversal Media CenterFuncTable_universalmediacenter*>(malloc(sizeof(AddonToUniversal Media CenterFuncTable_universalmediacenter)));

  addonInterface->toUniversal Media Center->universalmediacenter->unknown_to_utf8 = unknown_to_utf8;
  addonInterface->toUniversal Media Center->universalmediacenter->get_language = get_language;
  addonInterface->toUniversal Media Center->universalmediacenter->queue_notification = queue_notification;
  addonInterface->toUniversal Media Center->universalmediacenter->get_md5 = get_md5;
  addonInterface->toUniversal Media Center->universalmediacenter->get_region = get_region;
  addonInterface->toUniversal Media Center->universalmediacenter->get_free_mem = get_free_mem;
  addonInterface->toUniversal Media Center->universalmediacenter->get_global_idle_time = get_global_idle_time;
  addonInterface->toUniversal Media Center->universalmediacenter->is_addon_available = is_addon_available;
  addonInterface->toUniversal Media Center->universalmediacenter->universalmediacenter_version = universalmediacenter_version;
  addonInterface->toUniversal Media Center->universalmediacenter->get_current_skin_id = get_current_skin_id;
  addonInterface->toUniversal Media Center->universalmediacenter->get_keyboard_layout = get_keyboard_layout;
  addonInterface->toUniversal Media Center->universalmediacenter->change_keyboard_layout = change_keyboard_layout;
}

void Interface_General::DeInit(AddonGlobalInterface* addonInterface)
{
  if (addonInterface->toUniversal Media Center && /* <-- needed as long as the old addon way is used */
      addonInterface->toUniversal Media Center->universalmediacenter)
  {
    free(addonInterface->toUniversal Media Center->universalmediacenter);
    addonInterface->toUniversal Media Center->universalmediacenter = nullptr;
  }
}

char* Interface_General::unknown_to_utf8(void* universalmediacenterBase, const char* source, bool* ret, bool failOnBadChar)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !source || !ret)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', source='{}', ret='{}')", universalmediacenterBase,
               static_cast<const void*>(source), static_cast<void*>(ret));
    return nullptr;
  }

  std::string string;
  *ret = CCharsetConverter::unknownToUTF8(source, string, failOnBadChar);
  return strdup(string.c_str());
}

char* Interface_General::get_language(void* universalmediacenterBase, int format, bool region)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}')", universalmediacenterBase);
    return nullptr;
  }

  // The addon enum and the expander enum name the same three formats with the same values, and
  // anything else has always been served as the English name
  CLangCodeExpander::LANGFORMATS langFormat{CLangCodeExpander::ENGLISH_NAME};
  switch (format)
  {
    case LANG_FMT_ISO_639_1:
      langFormat = CLangCodeExpander::ISO_639_1;
      break;
    case LANG_FMT_ISO_639_2:
      langFormat = CLangCodeExpander::ISO_639_2;
      break;
    case LANG_FMT_ENGLISH_NAME:
    default:
      break;
  }

  return strdup(g_langInfo.GetLanguageAs(langFormat, region).c_str());
}

bool Interface_General::queue_notification(void* universalmediacenterBase, int type, const char* header,
                                           const char* message, const char* imageFile,
                                           unsigned int displayTime, bool withSound,
                                           unsigned int messageTime)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !message)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', message='{}')", universalmediacenterBase,
               static_cast<const void*>(message));
    return false;
  }

  std::string usedHeader;
  if (header && strlen(header) > 0)
    usedHeader = header;
  else
    usedHeader = addon->Name();

  QueueMsg qtype = static_cast<QueueMsg>(type);

  if (qtype != QUEUE_OWN_STYLE)
  {
    CGUIDialogKaiToast::eMessageType usedType;
    switch (qtype)
    {
    case QueueMsg::QUEUE_WARNING:
      usedType = CGUIDialogKaiToast::Warning;
      withSound = true;
      CLog::LogF(LOGDEBUG, "{} - Warning Message: '{}'", addon->Name(), message);
      break;
    case QueueMsg::QUEUE_ERROR:
      usedType = CGUIDialogKaiToast::Error;
      withSound = true;
      CLog::LogF(LOGDEBUG, "{} - Error Message : '{}'", addon->Name(), message);
      break;
    case QueueMsg::QUEUE_INFO:
    default:
      usedType = CGUIDialogKaiToast::Info;
      withSound = false;
      CLog::LogF(LOGDEBUG, "{} - Info Message : '{}'", addon->Name(), message);
      break;
    }

    if (imageFile && strlen(imageFile) > 0)
    {
      CLog::LogF(LOGERROR,
                 "To use given image file '{}' must be type value set to "
                 "'QUEUE_OWN_STYLE'",
                 imageFile);
    }

    CGUIDialogKaiToast::QueueNotification(usedType, usedHeader, message, 3000, withSound);
  }
  else
  {
    CGUIDialogKaiToast::QueueNotification(imageFile, usedHeader, message, displayTime, withSound, messageTime);
  }
  return true;
}

void Interface_General::get_md5(void* universalmediacenterBase, const char* text, char* md5)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !text)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', text='{}')", universalmediacenterBase,
               static_cast<const void*>(text));
    return;
  }

  std::string md5Int = CDigest::Calculate(CDigest::Type::MD5, std::string(text));
  strncpy(md5, md5Int.c_str(), 40);
}

char* Interface_General::get_region(void* universalmediacenterBase, const char* id)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !id)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', id='{}')", universalmediacenterBase,
               static_cast<const void*>(id));
    return nullptr;
  }

  std::string result;
  if (StringUtils::CompareNoCase(id, "datelong") == 0)
  {
    result = g_langInfo.GetDateFormat(true);
    StringUtils::Replace(result, "DDDD", "%A");
    StringUtils::Replace(result, "MMMM", "%B");
    StringUtils::Replace(result, "D", "%d");
    StringUtils::Replace(result, "YYYY", "%Y");
  }
  else if (StringUtils::CompareNoCase(id, "dateshort") == 0)
  {
    result = g_langInfo.GetDateFormat(false);
    StringUtils::Replace(result, "MM", "%m");
    StringUtils::Replace(result, "DD", "%d");
#ifdef TARGET_WINDOWS
    StringUtils::Replace(result, "M", "%#m");
    StringUtils::Replace(result, "D", "%#d");
#else
    StringUtils::Replace(result, "M", "%-m");
    StringUtils::Replace(result, "D", "%-d");
#endif
    StringUtils::Replace(result, "YYYY", "%Y");
  }
  else if (StringUtils::CompareNoCase(id, "tempunit") == 0)
    result = g_langInfo.GetTemperatureUnitString();
  else if (StringUtils::CompareNoCase(id, "speedunit") == 0)
    result = g_langInfo.GetSpeedUnitString();
  else if (StringUtils::CompareNoCase(id, "time") == 0)
  {
    result = g_langInfo.GetTimeFormat();
    StringUtils::Replace(result, "H", "%H");
    StringUtils::Replace(result, "h", "%I");
    StringUtils::Replace(result, "mm", "%M");
    StringUtils::Replace(result, "ss", "%S");
    StringUtils::Replace(result, "xx", "%p");
  }
  else if (StringUtils::CompareNoCase(id, "meridiem") == 0)
    result = StringUtils::Format("{}/{}", g_langInfo.GetMeridiemSymbol(MeridiemSymbol::AM),
                                 g_langInfo.GetMeridiemSymbol(MeridiemSymbol::PM));
  else
  {
    CLog::LogF(LOGERROR, "Add-on '{}' requests invalid id '{}'", addon->Name(), id);
    return nullptr;
  }

  return strdup(result.c_str());
}

void Interface_General::get_free_mem(void* universalmediacenterBase, long* free, long* total, bool as_bytes)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !free || !total)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', free='{}', total='{}')", universalmediacenterBase,
               static_cast<void*>(free), static_cast<void*>(total));
    return;
  }

  UNIVERSAL MEDIA CENTER::MEMORY::MemoryStatus stat{};
  UNIVERSAL MEDIA CENTER::MEMORY::GetMemoryStatus(&stat);
  if (stat.totalPhys == 0)
    return;

  if (!as_bytes)
  {
    stat.availPhys /= 1024 * 1024;
    stat.totalPhys /= 1024 * 1024;
  }
  *free = static_cast<long>(std::min<uint64_t>(stat.availPhys, std::numeric_limits<long>::max()));
  *total = static_cast<long>(std::min<uint64_t>(stat.totalPhys, std::numeric_limits<long>::max()));
}

int Interface_General::get_global_idle_time(void* universalmediacenterBase)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}')", universalmediacenterBase);
    return -1;
  }

  auto& components = CServiceBroker::GetAppComponents();
  const auto appPower = components.GetComponent<CApplicationPowerHandling>();
  return appPower->GlobalIdleTime();
}

bool Interface_General::is_addon_available(void* universalmediacenterBase,
                                           const char* id,
                                           char** version,
                                           bool* enabled)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !id || !version || !enabled)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', id='{}', version='{}', enabled='{}')", universalmediacenterBase,
               static_cast<const void*>(id), static_cast<void*>(version),
               static_cast<void*>(enabled));
    return false;
  }

  AddonPtr addonInfo;
  if (!CServiceBroker::GetAddonMgr().GetAddon(id, addonInfo, OnlyEnabled::CHOICE_NO))
    return false;

  *version = strdup(addonInfo->Version().asString().c_str());
  *enabled = !CServiceBroker::GetAddonMgr().IsAddonDisabled(id);
  return true;
}

void Interface_General::universalmediacenter_version(void* universalmediacenterBase, char** compile_name, int* major, int* minor, char** revision, char** tag, char** tagversion)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !compile_name || !major || !minor || !revision || !tag || !tagversion)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', compile_name='{}', major='{}', "
               "minor='{}', revision='{}', tag='{}', tagversion='{}')",
               universalmediacenterBase, static_cast<void*>(compile_name), static_cast<void*>(major),
               static_cast<void*>(minor), static_cast<void*>(revision), static_cast<void*>(tag),
               static_cast<void*>(tagversion));
    return;
  }

  *compile_name = strdup(CCompileInfo::GetAppName());
  *major = CCompileInfo::GetMajor();
  *minor = CCompileInfo::GetMinor();
  *revision = strdup(CCompileInfo::GetSCMID());
  const std::string tagStr{CCompileInfo::GetSuffix()};
  if (StringUtils::StartsWithNoCase(tagStr, "alpha"))
  {
    *tag = strdup("alpha");
    *tagversion = strdup(StringUtils::Mid(tagStr, 5).c_str());
  }
  else if (StringUtils::StartsWithNoCase(tagStr, "beta"))
  {
    *tag = strdup("beta");
    *tagversion = strdup(StringUtils::Mid(tagStr, 4).c_str());
  }
  else if (StringUtils::StartsWithNoCase(tagStr, "rc"))
  {
    *tag = strdup("releasecandidate");
    *tagversion = strdup(StringUtils::Mid(tagStr, 2).c_str());
  }
  else if (tagStr.empty())
    *tag = strdup("stable");
  else
    *tag = strdup("prealpha");
}

char* Interface_General::get_current_skin_id(void* universalmediacenterBase)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}')", universalmediacenterBase);
    return nullptr;
  }

  return strdup(CServiceBroker::GetSettingsComponent()->GetSettings()->GetString(CSettings::SETTING_LOOKANDFEEL_SKIN).c_str());
}

bool Interface_General::get_keyboard_layout(void* universalmediacenterBase, char** layout_name, int modifier_key, AddonKeyboardKeyTable* c_layout)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !c_layout || !layout_name)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', c_layout='{}', layout_name='{}')", universalmediacenterBase,
               static_cast<void*>(c_layout), static_cast<void*>(layout_name));
    return false;
  }

  const std::string activeLayout{CServiceBroker::GetSettingsComponent()->GetSettings()->GetString(
      CSettings::SETTING_LOCALE_ACTIVEKEYBOARDLAYOUT)};

  KEYBOARD::CKeyboardLayout layout;
  if (!CServiceBroker::GetKeyboardLayoutManager()->GetLayout(activeLayout, layout))
    return false;

  *layout_name = strdup(layout.GetName().c_str());

  unsigned int modifiers = KEYBOARD::CKeyboardLayout::ModifierKeyNone;
  if (modifier_key & STD_KB_MODIFIER_KEY_SHIFT)
    modifiers |= KEYBOARD::CKeyboardLayout::ModifierKeyShift;
  if (modifier_key & STD_KB_MODIFIER_KEY_SYMBOL)
    modifiers |= KEYBOARD::CKeyboardLayout::ModifierKeySymbol;

  for (unsigned int row = 0; row < STD_KB_BUTTONS_MAX_ROWS; row++)
  {
    for (unsigned int column = 0; column < STD_KB_BUTTONS_PER_ROW; column++)
    {
      const std::string label{layout.GetCharAt(row, column, modifiers)};
      c_layout->keys[row][column] = strdup(label.c_str());
    }
  }

  return true;
}

bool Interface_General::change_keyboard_layout(void* universalmediacenterBase, char** layout_name)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !layout_name)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', layout_name='{}')", universalmediacenterBase,
               static_cast<void*>(layout_name));
    return false;
  }

  std::vector<KEYBOARD::CKeyboardLayout> layouts;
  unsigned int currentLayout = 0;

  const KEYBOARD::KeyboardLayouts& keyboardLayouts{
      CServiceBroker::GetKeyboardLayoutManager()->GetLayouts()};
  const std::shared_ptr<CSettings> settings{CServiceBroker::GetSettingsComponent()->GetSettings()};
  const std::vector<CVariant> layoutNames{
      settings->GetList(CSettings::SETTING_LOCALE_KEYBOARDLAYOUTS)};
  const std::string activeLayout{
      settings->GetString(CSettings::SETTING_LOCALE_ACTIVEKEYBOARDLAYOUT)};

  for (const auto& layoutName : layoutNames)
  {
    const auto keyboardLayout = keyboardLayouts.find(layoutName.asString());
    if (keyboardLayout != keyboardLayouts.end())
    {
      layouts.emplace_back(keyboardLayout->second);
      if (layoutName.asString() == activeLayout)
        currentLayout = static_cast<unsigned int>(layouts.size() - 1);
    }
  }

  currentLayout++;
  if (currentLayout >= layouts.size())
    currentLayout = 0;
  KEYBOARD::CKeyboardLayout layout =
      layouts.empty() ? KEYBOARD::CKeyboardLayout() : layouts[currentLayout];
  CServiceBroker::GetSettingsComponent()->GetSettings()->SetString(CSettings::SETTING_LOCALE_ACTIVEKEYBOARDLAYOUT, layout.GetName());

  *layout_name = strdup(layout.GetName().c_str());
  return true;
}

} /* namespace ADDON */
