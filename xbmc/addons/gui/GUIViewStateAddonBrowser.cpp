/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GUIViewStateAddonBrowser.h"

#include "FileItem.h"
#include "FileItemList.h"
#include "filesystem/AddonsPaths.h"
#include "filesystem/File.h"
#include "guilib/WindowIDs.h"
#include "utils/ContentNames.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "view/ViewState.h"
#include "windowing/GraphicContext.h"

using namespace XFILE;
using namespace ADDON;

CGUIViewStateAddonBrowser::CGUIViewStateAddonBrowser(const CFileItemList& items)
  : CGUIViewState(items)
{
  if (URIUtils::PathEquals(items.GetPath(), UNIVERSAL MEDIA CENTER::ADDONS::ROOT))
  {
    AddSortMethod(SortBy::NONE, 551, LABEL_MASKS("%F", "", "%L", ""));
    SetSortMethod(SortBy::NONE);
  }
  else if (URIUtils::PathEquals(items.GetPath(), UNIVERSAL MEDIA CENTER::ADDONS::RECENTLY_UPDATED, true))
  {
    AddSortMethod(SortBy::LAST_UPDATED, 12014, LABEL_MASKS("%L", "%v", "%L", "%v"),
                  SortAttributeIgnoreFolders, SortOrder::DESCENDING);
  }
  else
  {
    AddSortMethod(SortBy::LABEL, SortAttributeIgnoreFolders, 551,
                  LABEL_MASKS("%L", "%s", "%L", "%s"));

    if (StringUtils::StartsWith(items.GetPath(), UNIVERSAL MEDIA CENTER::ADDONS::SOURCES))
      AddSortMethod(SortBy::LAST_USED, 12012, LABEL_MASKS("%L", "%u", "%L", "%u"),
                    SortAttributeIgnoreFolders, SortOrder::DESCENDING); //Label, Last used

    if (StringUtils::StartsWith(items.GetPath(), UNIVERSAL MEDIA CENTER::ADDONS::USER) &&
        items.GetContent() == UNIVERSAL MEDIA CENTER::MEDIA::CONTENT::ADDONS)
      AddSortMethod(SortBy::INSTALL_DATE, 12013, LABEL_MASKS("%L", "%i", "%L", "%i"),
                    SortAttributeIgnoreFolders, SortOrder::DESCENDING);

    SetSortMethod(SortBy::LABEL);
  }
  SetViewAsControl(DEFAULT_VIEW_AUTO);

  LoadViewState(items.GetPath(), WINDOW_ADDON_BROWSER);
}

void CGUIViewStateAddonBrowser::SaveViewState()
{
  SaveViewToDb(m_items.GetPath(), WINDOW_ADDON_BROWSER);
}

std::string CGUIViewStateAddonBrowser::GetExtensions()
{
  return "";
}
