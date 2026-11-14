/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Image.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/controls/Image.h"
#include "guilib/GUIImage.h"
#include "utils/log.h"

using namespace UNIVERSAL MEDIA CENTER;

namespace ADDON
{

void Interface_GUIControlImage::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->->control_image =
      new AddonToUniversal Media CenterFuncTable__control_image();

  addonInterface->toUniversal Media Center->->control_image->set_visible = set_visible;
  addonInterface->toUniversal Media Center->->control_image->set_filename = set_filename;
  addonInterface->toUniversal Media Center->->control_image->set_color_diffuse = set_color_diffuse;
}

void Interface_GUIControlImage::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->->control_image;
}

void Interface_GUIControlImage::set_visible(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                            UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                            bool visible)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIImage*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetVisible(visible);
}

void Interface_GUIControlImage::set_filename(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                             UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                             const char* filename,
                                             bool use_cache)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIImage*>(handle);
  if (!addon || !control || !filename)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}', "
               "filename='{}') on addon '{}'",
               universalmediacenterBase, handle, static_cast<const void*>(filename),
               addon ? addon->ID() : "unknown");
    return;
  }

  control->SetFileName(filename, false, use_cache);
}

void Interface_GUIControlImage::set_color_diffuse(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                  UNIVERSALMEDIA_GUI_CONTROL_HANDLE handle,
                                                  uint32_t colorDiffuse)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  auto* control = static_cast<CGUIImage*>(handle);
  if (!addon || !control)
  {
    CLog::LogF(LOGERROR,
               "Invalid handler data (universalmediacenterBase='{}', handle='{}') "
               "on addon '{}'",
               universalmediacenterBase, handle, addon ? addon->ID() : "unknown");
    return;
  }

  control->SetColorDiffuse(GUILIB::GUIINFO::CGUIInfoColor(colorDiffuse));
}

} /* namespace ADDON */
