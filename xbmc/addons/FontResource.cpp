/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */
#include "FontResource.h"

#include "addons/addoninfo/AddonInfo.h"
#include "addons/addoninfo/AddonType.h"
#include "filesystem/SpecialProtocol.h"
#include "utils/FileUtils.h"

namespace ADDON
{

CFontResource::CFontResource(const AddonInfoPtr& addonInfo)
  : CResource(addonInfo, AddonType::RESOURCE_FONT)
{
}

bool CFontResource::GetFont(const std::string& file, std::string& path) const
{
  std::string result = CSpecialProtocol::TranslatePathConvertCase(Path()+"/resources/"+file);
  if (CFileUtils::Exists(result))
  {
    path = result;
    return true;
  }

  return false;
}

}
