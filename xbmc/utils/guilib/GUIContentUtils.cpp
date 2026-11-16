/*
 *  Copyright (C) 2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GUIContentUtils.h"

#include "FileItem.h"
#include "ServiceBroker.h"
#include "addons/gui/GUIDialogAddonInfo.h"
#include "music/dialogs/GUIDialogMusicInfo.h"
#include "pvr/PVRManager.h"
#include "pvr/guilib/PVRGUIActionsUtils.h"
#include "video/VideoInfoTag.h"
#include "video/dialogs/GUIDialogVideoInfo.h"

using namespace UNIVERSAL MEDIA CENTER::UTILS::GUILIB;

bool CGUIContentUtils::HasInfoForItem(const CFileItem& item)
{
  if (item.HasVideoInfoTag() && !item.HasPVRRecordingInfoTag())
  {
    switch (item.GetVideoInfoTag()->GetMediaType())
    {
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO:
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MOVIE:
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::VIDEO_COLLECTION:
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::TV_SHOW:
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::SEASON:
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::EPISODE:
      case UNIVERSAL MEDIA CENTER::MEDIA::TYPE::MUSIC_VIDEO:
        return true;
      default:
        return false;
    }
  }

  return item.HasMusicInfoTag() || item.HasAddonInfo() ||
         CServiceBroker::GetPVRManager().Get<PVR::GUI::Utils>().HasInfoForItem(item);
}

bool CGUIContentUtils::ShowInfoForItem(const CFileItem& item)
{
  if (item.HasAddonInfo())
  {
    return CGUIDialogAddonInfo::ShowForItem(std::make_shared<CFileItem>(item));
  }
  else if (CServiceBroker::GetPVRManager().Get<PVR::GUI::Utils>().HasInfoForItem(item))
  {
    return CServiceBroker::GetPVRManager().Get<PVR::GUI::Utils>().OnInfo(item);
  }
  else if (item.HasVideoInfoTag())
  {
    CGUIDialogVideoInfo::ShowFor(item);
    return true;
  }
  else if (item.HasMusicInfoTag())
  {
    CGUIDialogMusicInfo::ShowFor(std::make_shared<CFileItem>(item).get());
    return true;
  }
  return false;
}
