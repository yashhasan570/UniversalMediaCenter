/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GUIViewStatePrograms.h"

#include "FileItemList.h"
#include "ServiceBroker.h"
#include "guilib/WindowIDs.h"
#include "settings/MediaSourceSettings.h"
#include "settings/Settings.h"
#include "settings/SettingsComponent.h"
#include "utils/DefaultArt.h"
#include "view/ViewState.h"
#include "view/ViewStateNames.h"
#include "view/ViewStateSettings.h"

#ifdef TARGET_ANDROID
#include "guilib/TextureManager.h"
#include "resources/LocalizeStrings.h"
#include "resources/ResourcesComponent.h"
#endif

using namespace XFILE;
using UNIVERSAL MEDIA CENTER::MEDIA::MediaSection;

CGUIViewStateWindowPrograms::CGUIViewStateWindowPrograms(const CFileItemList& items) : CGUIViewState(items)
{
  AddSortMethod(SortBy::LABEL, 551,
                LABEL_MASKS("%K", "%I", "%L", ""), // Title, Size | Foldername, empty
                CServiceBroker::GetSettingsComponent()->GetSettings()->GetBool(
                    CSettings::SETTING_FILELISTS_IGNORETHEWHENSORTING)
                    ? SortAttributeIgnoreArticle
                    : SortAttributeNone);

  const CViewState* viewState = CViewStateSettings::GetInstance().Get(UNIVERSAL MEDIA CENTER::VIEW::STATE::PROGRAMS);
  SetSortMethod(viewState->m_sortDescription);
  SetViewAsControl(viewState->m_viewMode);
  SetSortOrder(viewState->m_sortDescription.sortOrder);

  LoadViewState(items.GetPath(), WINDOW_PROGRAMS);
}

void CGUIViewStateWindowPrograms::SaveViewState()
{
  SaveViewToDb(m_items.GetPath(), WINDOW_PROGRAMS,
               CViewStateSettings::GetInstance().Get(UNIVERSAL MEDIA CENTER::VIEW::STATE::PROGRAMS));
}

std::optional<UNIVERSAL MEDIA CENTER::MEDIA::MediaSection> CGUIViewStateWindowPrograms::GetLockType()
{
  return UNIVERSAL MEDIA CENTER::MEDIA::MediaSection::PROGRAMS;
}

std::string CGUIViewStateWindowPrograms::GetExtensions()
{
  return ".cut";
}

std::vector<CMediaSource>& CGUIViewStateWindowPrograms::GetSources()
{
#if defined(TARGET_ANDROID)
  {
    CMediaSource source;
    source.strPath = "androidapp://sources/apps/";
    source.strName = CServiceBroker::GetResourcesComponent().GetLocalizeStrings().Get(20244);
    if (CServiceBroker::GetGUI()->GetTextureManager().HasTexture(UNIVERSAL MEDIA CENTER::ART::DEFAULT::PROGRAM))
      source.m_strThumbnailImage = UNIVERSAL MEDIA CENTER::ART::DEFAULT::PROGRAM;
    source.m_iDriveType = SourceType::LOCAL;
    source.m_ignore = true;
    m_sources.emplace_back(std::move(source));
  }
#endif

  std::vector<CMediaSource>& programSources =
      CMediaSourceSettings::GetInstance().GetSources(MediaSection::PROGRAMS);
  AddOrReplace(programSources, CGUIViewState::GetSources());
  return programSources;
}

