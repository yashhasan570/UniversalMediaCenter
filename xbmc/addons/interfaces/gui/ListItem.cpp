/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "ListItem.h"

#include "FileItem.h"
#include "General.h"
#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/ListItem.h"
#include "utils/StringUtils.h"
#include "utils/Variant.h"
#include "utils/log.h"

namespace ADDON
{

void Interface_GUIListItem::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->->listItem = new AddonToUniversal Media CenterFuncTable__listItem();

  addonInterface->toUniversal Media Center->->listItem->create = create;
  addonInterface->toUniversal Media Center->->listItem->destroy = destroy;
  addonInterface->toUniversal Media Center->->listItem->get_label = get_label;
  addonInterface->toUniversal Media Center->->listItem->set_label = set_label;
  addonInterface->toUniversal Media Center->->listItem->get_label2 = get_label2;
  addonInterface->toUniversal Media Center->->listItem->set_label2 = set_label2;
  addonInterface->toUniversal Media Center->->listItem->get_art = get_art;
  addonInterface->toUniversal Media Center->->listItem->set_art = set_art;
  addonInterface->toUniversal Media Center->->listItem->get_path = get_path;
  addonInterface->toUniversal Media Center->->listItem->set_path = set_path;
  addonInterface->toUniversal Media Center->->listItem->get_property = get_property;
  addonInterface->toUniversal Media Center->->listItem->set_property = set_property;
  addonInterface->toUniversal Media Center->->listItem->select = select;
  addonInterface->toUniversal Media Center->->listItem->is_selected = is_selected;
}

void Interface_GUIListItem::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->->listItem;
}

UNIVERSALMEDIA_GUI_LISTITEM_HANDLE Interface_GUIListItem::create(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                       const char* label,
                                                       const char* label2,
                                                       const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return nullptr;
  }

  auto* fileItem{new CFileItem()};
  auto* item{new std::shared_ptr<CFileItem>(fileItem)};
  if (label)
    item->get()->SetLabel(label);
  if (label2)
    item->get()->SetLabel2(label2);
  if (path)
    item->get()->SetPath(path);

  return item;
}

void Interface_GUIListItem::destroy(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon)
  {
    CLog::LogF(LOGERROR, "Invalid data");
    return;
  }

  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (item)
    delete item;
}

char* Interface_GUIListItem::get_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') on "
               "addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return nullptr;
  }

  Interface_GUIGeneral::lock();
  char* ret = strdup(item->get()->GetLabel().c_str());
  Interface_GUIGeneral::unlock();
  return ret;
}

void Interface_GUIListItem::set_label(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                      UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                      const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return;
  }

  Interface_GUIGeneral::lock();
  item->get()->SetLabel(label);
  Interface_GUIGeneral::unlock();
}

char* Interface_GUIListItem::get_label2(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') on "
               "addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return nullptr;
  }

  Interface_GUIGeneral::lock();
  char* ret = strdup(item->get()->GetLabel2().c_str());
  Interface_GUIGeneral::unlock();
  return ret;
}

void Interface_GUIListItem::set_label2(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                       UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                       const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(label), addon ? addon->ID() : "unknown");
    return;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return;
  }

  Interface_GUIGeneral::lock();
  item->get()->SetLabel2(label);
  Interface_GUIGeneral::unlock();
}

char* Interface_GUIListItem::get_art(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                     UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                     const char* type)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !type)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', type='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(type), addon ? addon->ID() : "unknown");
    return nullptr;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return nullptr;
  }

  Interface_GUIGeneral::lock();
  char* ret = strdup(item->get()->GetArt(type).c_str());
  Interface_GUIGeneral::unlock();
  return ret;
}

void Interface_GUIListItem::set_art(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                    const char* type,
                                    const char* label)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !type || !label)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', type= "
               "'{}', label='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(type), static_cast<const void*>(label),
               addon ? addon->ID() : "unknown");
    return;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return;
  }

  Interface_GUIGeneral::lock();
  item->get()->SetArt(type, label);
  Interface_GUIGeneral::unlock();
}

char* Interface_GUIListItem::get_path(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') on "
               "addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return nullptr;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return nullptr;
  }

  Interface_GUIGeneral::lock();
  char* ret = strdup(item->get()->GetPath().c_str());
  Interface_GUIGeneral::unlock();
  return ret;
}


void Interface_GUIListItem::set_path(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                     UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                     const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !path)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', path='{}', "
               "handle='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(path), addon ? addon->ID() : "unknown");
    return;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return;
  }

  Interface_GUIGeneral::lock();
  item->get()->SetPath(path);
  Interface_GUIGeneral::unlock();
}

void Interface_GUIListItem::set_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                         UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                         const char* key,
                                         const char* value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !key || !value)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "key='{}', value='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(key), static_cast<const void*>(value),
               addon ? addon->ID() : "unknown");
    return;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return;
  }

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  item->get()->SetProperty(lowerKey, CVariant(value));
  Interface_GUIGeneral::unlock();
}

char* Interface_GUIListItem::get_property(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                          UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                          const char* key)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item || !key)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "key='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(key), addon ? addon->ID() : "unknown");
    return nullptr;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return nullptr;
  }

  std::string lowerKey = key;
  StringUtils::ToLower(lowerKey);

  Interface_GUIGeneral::lock();
  char* ret = strdup(item->get()->GetProperty(lowerKey).asString().c_str());
  Interface_GUIGeneral::unlock();

  return ret;
}

void Interface_GUIListItem::select(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                   UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle,
                                   bool select)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') on "
               "addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return;
  }

  Interface_GUIGeneral::lock();
  item->get()->Select(select);
  Interface_GUIGeneral::unlock();
}

bool Interface_GUIListItem::is_selected(UNIVERSALMEDIA_HANDLE universalmediacenterBase, UNIVERSALMEDIA_GUI_LISTITEM_HANDLE handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  const auto* item = static_cast<const std::shared_ptr<CFileItem>*>(handle);
  if (!addon || !item)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') on "
               "addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return false;
  }

  if (!item->get())
  {
    CLog::LogF(LOGERROR, "Empty list item called on addon '{}'", addon->ID());
    return false;
  }

  Interface_GUIGeneral::lock();
  const bool ret = item->get()->IsSelected();
  Interface_GUIGeneral::unlock();

  return ret;
}

} /* namespace ADDON */
