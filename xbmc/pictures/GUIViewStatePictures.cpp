/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GUIViewStatePictures.h"

#include "FileItem.h"
#include "FileItemList.h"
#include "ServiceBroker.h"
#include "guilib/WindowIDs.h"
#include "settings/MediaSourceSettings.h"
#include "settings/Settings.h"
#include "settings/SettingsComponent.h"
#include "utils/FileExtensionProvider.h"
#include "view/ViewState.h"
#include "view/ViewStateNames.h"
#include "view/ViewStateSettings.h"

using namespace XFILE;
using namespace ADDON;
using UNIVERSAL MEDIA CENTER::MEDIA::MediaSection;

CGUIViewStateWindowPictures::CGUIViewStateWindowPictures(const CFileItemList& items) : CGUIViewState(items)
{
  if (items.IsVirtualDirectoryRoot())
  {
    AddSortMethod(SortBy::LABEL, 551, LABEL_MASKS());
    AddSortMethod(SortBy::DRIVE_TYPE, 564, LABEL_MASKS());
    SetSortMethod(SortBy::LABEL);

    SetViewAsControl(DEFAULT_VIEW_LIST);

    SetSortOrder(SortOrder::ASCENDING);
  }
  else
  {
    AddSortMethod(SortBy::LABEL, 551,
                  LABEL_MASKS("%L", "%I", "%L", "")); // Filename, Size | Foldername, empty
    AddSortMethod(SortBy::SIZE, 553,
                  LABEL_MASKS("%L", "%I", "%L", "%I")); // Filename, Size | Foldername, Size
    AddSortMethod(SortBy::DATE, 552,
                  LABEL_MASKS("%L", "%J", "%L", "%J")); // Filename, Date | Foldername, Date
    AddSortMethod(SortBy::DATE_TAKEN, 577,
                  LABEL_MASKS("%L", "%t", "%L", "%J")); // Filename, DateTaken | Foldername, Date
    AddSortMethod(SortBy::FILE, 561,
                  LABEL_MASKS("%L", "%I", "%L", "")); // Filename, Size | FolderName, empty

    const CViewState* viewState =
        CViewStateSettings::GetInstance().Get(UNIVERSAL MEDIA CENTER::VIEW::STATE::PICTURES);
    SetSortMethod(viewState->m_sortDescription);
    SetViewAsControl(viewState->m_viewMode);
    SetSortOrder(viewState->m_sortDescription.sortOrder);
  }
  LoadViewState(items.GetPath(), WINDOW_PICTURES);
}

void CGUIViewStateWindowPictures::SaveViewState()
{
  SaveViewToDb(m_items.GetPath(), WINDOW_PICTURES,
               CViewStateSettings::GetInstance().Get(UNIVERSAL MEDIA CENTER::VIEW::STATE::PICTURES));
}

std::optional<UNIVERSAL MEDIA CENTER::MEDIA::MediaSection> CGUIViewStateWindowPictures::GetLockType()
{
  return UNIVERSAL MEDIA CENTER::MEDIA::MediaSection::PICTURES;
}

std::string CGUIViewStateWindowPictures::GetExtensions()
{
  std::string extensions = CServiceBroker::GetFileExtensionProvider().GetPictureExtensions();
  if (CServiceBroker::GetSettingsComponent()->GetSettings()->GetBool(CSettings::SETTING_PICTURES_SHOWVIDEOS))
    extensions += "|" + CServiceBroker::GetFileExtensionProvider().GetVideoExtensions();

  return extensions;
}

std::vector<CMediaSource>& CGUIViewStateWindowPictures::GetSources()
{
  return CMediaSourceSettings::GetInstance().GetSources(MediaSection::PICTURES);
}

