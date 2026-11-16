/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "network/NetworkFileItemClassify.h"

#include "FileItem.h"
#include "utils/ItemProperties.h"
#include "utils/URIUtils.h"

namespace UNIVERSAL MEDIA CENTER::NETWORK
{

bool IsInternetStream(const CFileItem& item)
{
  if (item.HasProperty(ITEM::PROPERTY::IS_HTTP_DIRECTORY))
    return false;

  return URIUtils::IsInternetStream(item.GetDynURL());
}

bool IsRemote(const CFileItem& item)
{
  return URIUtils::IsRemote(item.GetPath());
}

bool IsStreamedFilesystem(const CFileItem& item)
{
  return URIUtils::IsStreamedFilesystem(item.GetDynPath());
}

} // namespace UNIVERSAL MEDIA CENTER::NETWORK
