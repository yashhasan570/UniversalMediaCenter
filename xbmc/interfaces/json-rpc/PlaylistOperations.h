/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "FileItemHandler.h"
#include "JSONRPC.h"

class CFileItemList;
class CVariant;

namespace UNIVERSAL MEDIA CENTER::PLAYLIST
{
enum class Id;
} // namespace UNIVERSAL MEDIA CENTER::PLAYLIST

namespace JSONRPC
{
  class CPlaylistOperations : public CFileItemHandler
  {
  public:
    static JSONRPC_STATUS GetPlaylists(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSONRPC_STATUS GetProperties(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);

    static JSONRPC_STATUS GetItems(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSONRPC_STATUS Add(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSONRPC_STATUS Remove(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSONRPC_STATUS Insert(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSONRPC_STATUS Clear(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
    static JSONRPC_STATUS Swap(const std::string &method, ITransportLayer *transport, IClient *client, const CVariant &parameterObject, CVariant &result);
  private:
    static UNIVERSAL MEDIA CENTER::PLAYLIST::Id GetPlaylist(const CVariant& playlist);
    static JSONRPC_STATUS GetPropertyValue(UNIVERSAL MEDIA CENTER::PLAYLIST::Id playlistId,
                                           const std::string& property,
                                           CVariant& result);
    static bool CheckMediaParameter(UNIVERSAL MEDIA CENTER::PLAYLIST::Id playlistId, const CVariant& itemObject);
    static bool HandleItemsParameter(UNIVERSAL MEDIA CENTER::PLAYLIST::Id playlistId,
                                     const CVariant& itemParam,
                                     CFileItemList& items);
  };
}
