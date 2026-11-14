/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Network.h"

#include "ServiceBroker.h"
#include "URL.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/Network.h"
#include "network/DNSNameCache.h"
#include "network/Network.h"
#include "utils/SystemInfo.h"
#include "utils/URIUtils.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_Network::Init(AddonGlobalInterface *addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_network = new AddonToUniversal Media CenterFuncTable_universalmediacenter_network();

  addonInterface->toUniversal Media Center->universalmediacenter_network->wake_on_lan = wake_on_lan;
  addonInterface->toUniversal Media Center->universalmediacenter_network->get_ip_address = get_ip_address;
  addonInterface->toUniversal Media Center->universalmediacenter_network->get_hostname = get_hostname;
  addonInterface->toUniversal Media Center->universalmediacenter_network->get_user_agent = get_user_agent;
  addonInterface->toUniversal Media Center->universalmediacenter_network->is_local_host = is_local_host;
  addonInterface->toUniversal Media Center->universalmediacenter_network->is_host_on_lan = is_host_on_lan;
  addonInterface->toUniversal Media Center->universalmediacenter_network->dns_lookup = dns_lookup;
  addonInterface->toUniversal Media Center->universalmediacenter_network->url_encode = url_encode;
}

void Interface_Network::DeInit(AddonGlobalInterface* addonInterface)
{
  if (addonInterface->toUniversal Media Center) /* <-- needed as long as the old addon way is used */
  {
    delete addonInterface->toUniversal Media Center->universalmediacenter_network;
    addonInterface->toUniversal Media Center->universalmediacenter_network = nullptr;
  }
}

bool Interface_Network::wake_on_lan(void* universalmediacenterBase, const char* mac)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !mac)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', mac='{}')", universalmediacenterBase,
               static_cast<const void*>(mac));
    return false;
  }

  return CServiceBroker::GetNetwork().WakeOnLan(mac);
}

char* Interface_Network::get_ip_address(void* universalmediacenterBase)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}')", universalmediacenterBase);
    return nullptr;
  }

  std::string titleIP;
  CNetworkInterface* iface = CServiceBroker::GetNetwork().GetFirstConnectedInterface();
  if (iface)
    titleIP = iface->GetCurrentIPAddress();
  else
    titleIP = "127.0.0.1";

  if (titleIP.empty())
    return nullptr;

  return strdup(titleIP.c_str());
}

char* Interface_Network::get_hostname(void* universalmediacenterBase)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}')", universalmediacenterBase);
    return nullptr;
  }

  std::string hostname;
  if (!CServiceBroker::GetNetwork().GetHostName(hostname))
    return nullptr;

  if (hostname.empty())
    return nullptr;

  return strdup(hostname.c_str());
}

char* Interface_Network::get_user_agent(void* universalmediacenterBase)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}')", universalmediacenterBase);
    return nullptr;
  }

  const std::string string{CSysInfo::GetUserAgent()};
  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

bool Interface_Network::is_local_host(void* universalmediacenterBase, const char* hostname)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !hostname)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', hostname='{}')", universalmediacenterBase,
               static_cast<const void*>(hostname));
    return false;
  }

  return CServiceBroker::GetNetwork().IsLocalHost(hostname);
}

bool Interface_Network::is_host_on_lan(void* universalmediacenterBase, const char* hostname, bool offLineCheck)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !hostname)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', hostname='{}')", universalmediacenterBase,
               static_cast<const void*>(hostname));
    return false;
  }

  //! TODO change to use the LanCheckMode enum class on the API signature
  return URIUtils::IsHostOnLAN(hostname, offLineCheck ? LanCheckMode::ANY_PRIVATE_SUBNET
                                                      : LanCheckMode::ONLY_LOCAL_SUBNET);
}

char* Interface_Network::dns_lookup(void* universalmediacenterBase, const char* url, bool* ret)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url || !ret)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', url='{}', ret='{}')", universalmediacenterBase,
               static_cast<const void*>(url), static_cast<void*>(ret));
    return nullptr;
  }

  std::string string;
  *ret = CServiceBroker::GetDNSNameCache()->Lookup(url, string);
  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

char* Interface_Network::url_encode(void* universalmediacenterBase, const char* url)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', url='{}')", universalmediacenterBase,
               static_cast<const void*>(url));
    return nullptr;
  }

  const std::string string{CURL::Encode(url)};
  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

} /* namespace ADDON */
