/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "OK.h"

#include "addons/binary-addons/AddonDll.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/OK.h"
#include "messaging/helpers/DialogOKHelper.h"
#include "utils/Variant.h"
#include "utils/log.h"

using namespace UNIVERSAL MEDIA CENTER::MESSAGING;

namespace ADDON
{

void Interface_GUIDialogOK::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogOK = new AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogOK();

  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogOK->show_and_get_input_single_text =
      show_and_get_input_single_text;
  addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogOK->show_and_get_input_line_text =
      show_and_get_input_line_text;
}

void Interface_GUIDialogOK::DeInit(AddonGlobalInterface* addonInterface)
{
  delete addonInterface->toUniversal Media Center->universalmediacenter_gui->dialogOK;
}

void Interface_GUIDialogOK::show_and_get_input_single_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                           const char* heading,
                                                           const char* text)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !heading || !text)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', heading='{}', text='{}')", universalmediacenterBase,
               static_cast<const void*>(heading), static_cast<const void*>(text));
    return;
  }

  HELPERS::ShowOKDialogText(CVariant{heading}, CVariant{text});
}

void Interface_GUIDialogOK::show_and_get_input_line_text(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                                         const char* heading,
                                                         const char* line0,
                                                         const char* line1,
                                                         const char* line2)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !heading || !line0 || !line1 || !line2)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', heading='{}', line0='{}', "
               "line1='{}', line2='{}')",
               universalmediacenterBase, static_cast<const void*>(heading), static_cast<const void*>(line0),
               static_cast<const void*>(line1), static_cast<const void*>(line2));
    return;
  }
  HELPERS::ShowOKDialogLines(CVariant{heading}, CVariant{line0}, CVariant{line1}, CVariant{line2});
}

} /* namespace ADDON */
