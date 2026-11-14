/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Image.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/kodi-dev-kit/include/kodi/gui/controls/Image.h"
#include "guilib/GUIImage.h"
#include "utils/log.h"

using namespace KODI;

namespace ADDON
{

void Interface_GUIControlImage::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->kodi_gui->control_image =
      new AddonToUniversal Media CenterFuncTable_kodi_gui_control_image();

  addonInterface->toUniversal Media Center->kodi_gui->control_image->set_visible = set_visible;
  addonInterface->toUniversal Media Center->kodi_gui->control_image->set_filename = set_filename;
  addonInterface->toUniversal Media Center->kodi_gui->control_image->set_color_diffuse = set_color_diffuse;
}

void Interface_GUIControlImage::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->kodi_gui->control_image;
}

void Interface_GUIControlImage::set_visible(KODI_HANDLE kodiBase,
                                            KODI_GUI_CONTROL_HANDLE handle,
                                            bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(kodiBase);
  auto* control = static_cast<CGUIImage*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (kodiBase='{}', handle='{}') "
               "on addon '{}'",
               kodiBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetVisible(visible);
}

void Interface_GUIControlImage::set_filename(KODI_HANDLE kodiBase,
                                             KODI_GUI_CONTROL_HANDLE handle,
                                             const char* filename,
                                             bool use_cache)
{
  const auto* addon = static_cast<const CAddonDll*>(kodiBase);
  auto* control = static_cast<CGUIImage*>(handle);
  if (!addon || !control || !filename)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (kodiBase='{}', handle='{}', "
               "filename='{}') on addon '{}'",
               kodiBase, handle, static_cast<const void*>(filename),
               addon ? addon->ID() : "unknown");
    return;
  }

  control->SetFileName(filename, false, use_cache);
}

void Interface_GUIControlImage::set_color_diffuse(KODI_HANDLE kodiBase,
                                                  KODI_GUI_CONTROL_HANDLE handle,
                                                  uint32_t colorDiffuse)
{
  const auto* addon = static_cast<const CAddonDll*>(kodiBase);
  auto* control = static_cast<CGUIImage*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (kodiBase='{}', handle='{}') "
               "on addon '{}'",
               kodiBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetColorDiffuse(GUILIB::GUIINFO::CGUIInfoColor(colorDiffuse));
}

} /* namespace ADDON */
