/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Filesystem.h"

#include "FileItem.h"
#include "FileItemList.h"
#include "Util.h"
#include "addons/binary-addons/AddonDll.h"
#include "filesystem/CurlFile.h"
#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "filesystem/SpecialProtocol.h"
#include "platform/Filesystem.h"
#include "utils/Crc32.h"
#include "utils/HttpHeader.h"
#include "utils/StringUtils.h"
#include "utils/URIUtils.h"
#include "utils/log.h"

#include <vector>

#if defined(TARGET_WINDOWS)
#ifndef S_IFLNK
#define S_IFLNK 0120000
#endif
#ifndef S_ISBLK
#define S_ISBLK(m) (0)
#endif
#ifndef S_ISSOCK
#define S_ISSOCK(m) (0)
#endif
#ifndef S_ISLNK
#define S_ISLNK(m) ((m & S_IFLNK) != 0)
#endif
#ifndef S_ISCHR
#define S_ISCHR(m) ((m & _S_IFCHR) != 0)
#endif
#ifndef S_ISDIR
#define S_ISDIR(m) ((m & _S_IFDIR) != 0)
#endif
#ifndef S_ISFIFO
#define S_ISFIFO(m) ((m & _S_IFIFO) != 0)
#endif
#ifndef S_ISREG
#define S_ISREG(m) ((m & _S_IFREG) != 0)
#endif
#endif

using namespace universalmediacenter; // addon-dev-kit namespace
using namespace XFILE;

namespace ADDON
{

void Interface_Filesystem::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem = new AddonToUniversal Media CenterFuncTable_universalmediacenter_filesystem();

  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->can_open_directory = can_open_directory;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->create_directory = create_directory;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->directory_exists = directory_exists;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->remove_directory = remove_directory;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->remove_directory_recursive = remove_directory_recursive;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_directory = get_directory;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->free_directory = free_directory;

  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->file_exists = file_exists;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->stat_file = stat_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->delete_file = delete_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->rename_file = rename_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->copy_file = copy_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_file_md5 = get_file_md5;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_cache_thumb_name = get_cache_thumb_name;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->make_legal_filename = make_legal_filename;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->make_legal_path = make_legal_path;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->translate_special_protocol = translate_special_protocol;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_disk_space = get_disk_space;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->is_internet_stream = is_internet_stream;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->is_on_lan = is_on_lan;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->is_remote = is_remote;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->is_local = is_local;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->is_url = is_url;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_http_header = get_http_header;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_mime_type = get_mime_type;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_content_type = get_content_type;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_cookies = get_cookies;

  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->http_header_create = http_header_create;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->http_header_free = http_header_free;

  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->open_file = open_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->open_file_for_write = open_file_for_write;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->read_file = read_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->read_file_string = read_file_string;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->write_file = write_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->flush_file = flush_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->seek_file = seek_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->truncate_file = truncate_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_file_position = get_file_position;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_file_length = get_file_length;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_file_download_speed = get_file_download_speed;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->close_file = close_file;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_file_chunk_size = get_file_chunk_size;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->io_control_get_seek_possible =
      io_control_get_seek_possible;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->io_control_get_cache_status =
      io_control_get_cache_status;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->io_control_set_cache_rate = io_control_set_cache_rate;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->io_control_set_retry = io_control_set_retry;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->get_property_values = get_property_values;

  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->curl_create = curl_create;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->curl_add_option = curl_add_option;
  addonInterface->toUniversal Media Center->universalmediacenter_filesystem->curl_open = curl_open;
}

void Interface_Filesystem::DeInit(AddonGlobalInterface* addonInterface)
{
  if (addonInterface->toUniversal Media Center) /* <-- Safe check, needed so long old addon way is present */
  {
    delete addonInterface->toUniversal Media Center->universalmediacenter_filesystem;
    addonInterface->toUniversal Media Center->universalmediacenter_filesystem = nullptr;
  }
}

unsigned int Interface_Filesystem::TranslateFileReadBitsToUniversal Media Center(unsigned int addonFlags)
{
  unsigned int universalmediacenterFlags = 0;

  if (addonFlags & ADDON_READ_TRUNCATED)
    universalmediacenterFlags |= READ_TRUNCATED;
  if (addonFlags & ADDON_READ_CHUNKED)
    CLog::LogF(LOGWARNING, "Detected use of deprecated 'ADDON_READ_CHUNKED' flag");
  if (addonFlags & ADDON_READ_CACHED)
    universalmediacenterFlags |= READ_CACHED;
  if (addonFlags & ADDON_READ_NO_CACHE)
    universalmediacenterFlags |= READ_NO_CACHE;
  if (addonFlags & ADDON_READ_BITRATE)
    universalmediacenterFlags |= READ_BITRATE;
  if (addonFlags & ADDON_READ_MULTI_STREAM)
    universalmediacenterFlags |= READ_MULTI_STREAM;
  if (addonFlags & ADDON_READ_AUDIO_VIDEO)
    universalmediacenterFlags |= READ_AUDIO_VIDEO;
  if (addonFlags & ADDON_READ_AFTER_WRITE)
    universalmediacenterFlags |= READ_AFTER_WRITE;
  if (addonFlags & ADDON_READ_REOPEN)
    universalmediacenterFlags |= READ_REOPEN;
  if (addonFlags & ADDON_READ_NO_BUFFER)
    universalmediacenterFlags |= READ_NO_BUFFER;

  return universalmediacenterFlags;
}

bool Interface_Filesystem::can_open_directory(void* universalmediacenterBase, const char* url)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', url='{}')", universalmediacenterBase,
               static_cast<const void*>(url));
    return false;
  }

  CFileItemList items;
  return CDirectory::GetDirectory(url, items, "", DIR_FLAG_DEFAULTS | DIR_FLAG_BYPASS_CACHE);
}

bool Interface_Filesystem::create_directory(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{}')", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return CDirectory::Create(path);
}

bool Interface_Filesystem::directory_exists(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{}')", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return CDirectory::Exists(path, false);
}

bool Interface_Filesystem::remove_directory(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{}')", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  // Empty directory
  CFileItemList fileItems;
  CDirectory::GetDirectory(path, fileItems, "", DIR_FLAG_NO_FILE_DIRS | DIR_FLAG_BYPASS_CACHE);
  for (int i = 0; i < fileItems.Size(); ++i)
    CFile::Delete(fileItems.Get(i)->GetPath());

  return CDirectory::Remove(path);
}

bool Interface_Filesystem::remove_directory_recursive(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{}')", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return CDirectory::RemoveRecursive(path);
}

namespace
{
void CFileItemListToVFSDirEntries(VFSDirEntry* entries, const CFileItemList& items)
{
  for (unsigned int i = 0; i < static_cast<unsigned int>(items.Size()); ++i)
  {
    const auto& item{items[i]};
    auto& entry{entries[i]};
    entry.label = strdup(item->GetLabel().c_str());
    entry.path = strdup(item->GetPath().c_str());
    entry.size = item->GetSize();
    entry.folder = item->IsFolder();
    item->GetDateTime().GetAsTime(entry.date_time);
  }
}
} // unnamed namespace

bool Interface_Filesystem::get_directory(void* universalmediacenterBase,
                                         const char* path,
                                         const char* mask,
                                         struct VFSDirEntry** items,
                                         unsigned int* num_items)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path || !mask || !items || !num_items)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', path='{}', mask='{}', "
               "items='{}', num_items='{}'",
               universalmediacenterBase, static_cast<const void*>(path), static_cast<const void*>(mask),
               static_cast<void*>(items), static_cast<void*>(num_items));
    return false;
  }

  CFileItemList fileItems;
  if (!CDirectory::GetDirectory(path, fileItems, mask,
                                DIR_FLAG_NO_FILE_DIRS | DIR_FLAG_BYPASS_CACHE))
    return false;

  if (!fileItems.IsEmpty())
  {
    *num_items = static_cast<unsigned int>(fileItems.Size());
    *items = new VFSDirEntry[fileItems.Size()];
    CFileItemListToVFSDirEntries(*items, fileItems);
  }
  else
  {
    *num_items = 0;
    *items = nullptr;
  }

  return true;
}

void Interface_Filesystem::free_directory(void* universalmediacenterBase,
                                          struct VFSDirEntry* items,
                                          unsigned int num_items)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !items)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', items='{}')", universalmediacenterBase,
               static_cast<void*>(items));
    return;
  }

  for (unsigned int i = 0; i < num_items; ++i)
  {
    free(items[i].label);
    free(items[i].path);
  }
  delete[] items;
}

//------------------------------------------------------------------------------

bool Interface_Filesystem::file_exists(void* universalmediacenterBase, const char* filename, bool useCache)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}')", universalmediacenterBase,
               static_cast<const void*>(filename));
    return false;
  }

  return CFile::Exists(filename, useCache);
}

bool Interface_Filesystem::stat_file(void* universalmediacenterBase,
                                     const char* filename,
                                     struct STAT_STRUCTURE* buffer)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename || !buffer)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}', buffer='{}')", universalmediacenterBase,
               static_cast<const void*>(filename), static_cast<void*>(buffer));
    return false;
  }

  struct __stat64 statBuffer;
  if (CFile::Stat(filename, &statBuffer) != 0)
    return false;

  buffer->deviceId = statBuffer.st_dev;
  buffer->fileSerialNumber = statBuffer.st_ino;
  buffer->size = statBuffer.st_size;
  buffer->accessTime = statBuffer.st_atime;
  buffer->modificationTime = statBuffer.st_mtime;
  buffer->statusTime = statBuffer.st_ctime;
  buffer->isDirectory = S_ISDIR(statBuffer.st_mode);
  buffer->isSymLink = S_ISLNK(statBuffer.st_mode);
  buffer->isBlock = S_ISBLK(statBuffer.st_mode);
  buffer->isCharacter = S_ISCHR(statBuffer.st_mode);
  buffer->isFifo = S_ISFIFO(statBuffer.st_mode);
  buffer->isRegular = S_ISREG(statBuffer.st_mode);
  buffer->isSocket = S_ISSOCK(statBuffer.st_mode);

  return true;
}

bool Interface_Filesystem::delete_file(void* universalmediacenterBase, const char* filename)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}')", universalmediacenterBase,
               static_cast<const void*>(filename));
    return false;
  }

  return CFile::Delete(filename);
}

bool Interface_Filesystem::rename_file(void* universalmediacenterBase,
                                       const char* filename,
                                       const char* newFileName)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename || !newFileName)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}', newFileName='{}')", universalmediacenterBase,
               static_cast<const void*>(filename), static_cast<const void*>(newFileName));
    return false;
  }

  return CFile::Rename(filename, newFileName);
}

bool Interface_Filesystem::copy_file(void* universalmediacenterBase, const char* filename, const char* dest)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename || !dest)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}', dest='{}')", universalmediacenterBase,
               static_cast<const void*>(filename), static_cast<const void*>(dest));
    return false;
  }

  return CFile::Copy(filename, dest);
}

char* Interface_Filesystem::get_file_md5(void* universalmediacenterBase, const char* filename)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{})", universalmediacenterBase,
               static_cast<const void*>(filename));
    return nullptr;
  }

  const std::string string{CUtil::GetFileDigest(filename, UNIVERSAL MEDIA CENTER::UTILITY::CDigest::Type::MD5)};
  return strdup(string.c_str());
}

char* Interface_Filesystem::get_cache_thumb_name(void* universalmediacenterBase, const char* filename)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{})", universalmediacenterBase,
               static_cast<const void*>(filename));
    return nullptr;
  }

  const auto crc = Crc32::ComputeFromLowerCase(filename);
  const std::string hex{StringUtils::Format("{:08x}.tbn", crc)};
  return strdup(hex.c_str());
}

char* Interface_Filesystem::make_legal_filename(void* universalmediacenterBase, const char* filename)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{})", universalmediacenterBase,
               static_cast<const void*>(filename));
    return nullptr;
  }

  const std::string string{CUtil::MakeLegalFileName(filename)};
  return strdup(string.c_str());
}

char* Interface_Filesystem::make_legal_path(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{})", universalmediacenterBase,
               static_cast<const void*>(path));
    return nullptr;
  }

  const std::string string{CUtil::MakeLegalPath(path)};
  return strdup(string.c_str());
}

char* Interface_Filesystem::translate_special_protocol(void* universalmediacenterBase, const char* strSource)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !strSource)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', strSource='{})", universalmediacenterBase,
               static_cast<const void*>(strSource));
    return nullptr;
  }

  return strdup(CSpecialProtocol::TranslatePath(strSource).c_str());
}

bool Interface_Filesystem::get_disk_space(
    void* universalmediacenterBase, const char* path, uint64_t* capacity, uint64_t* free, uint64_t* available)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path || !capacity || !free || !available)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', path='{}, capacity='{}, free='{}, "
               "available='{})",
               universalmediacenterBase, static_cast<const void*>(path), static_cast<void*>(capacity),
               static_cast<void*>(free), static_cast<void*>(available));
    return false;
  }

  using namespace UNIVERSAL MEDIA CENTER::PLATFORM::FILESYSTEM;

  std::error_code ec;
  const space_info freeSpace{space(CSpecialProtocol::TranslatePath(path), ec)};
  if (ec.value() != 0)
    return false;

  *capacity = freeSpace.capacity;
  *free = freeSpace.free;
  *available = freeSpace.available;
  return true;
}

bool Interface_Filesystem::is_internet_stream(void* universalmediacenterBase, const char* path, bool strictCheck)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{})", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return URIUtils::IsInternetStream(path, strictCheck);
}

bool Interface_Filesystem::is_on_lan(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{})", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return URIUtils::IsOnLAN(path);
}

bool Interface_Filesystem::is_remote(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{})", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return URIUtils::IsRemote(path);
}

bool Interface_Filesystem::is_local(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{})", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return CURL(path).IsLocal();
}

bool Interface_Filesystem::is_url(void* universalmediacenterBase, const char* path)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !path)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', path='{})", universalmediacenterBase,
               static_cast<const void*>(path));
    return false;
  }

  return URIUtils::IsURL(path);
}

bool Interface_Filesystem::get_mime_type(void* universalmediacenterBase,
                                         const char* url,
                                         char** content,
                                         const char* useragent)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url || !content || !useragent)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', url='{}', content='{}', "
               "useragent='{}')",
               universalmediacenterBase, static_cast<const void*>(url), static_cast<const void*>(content),
               static_cast<const void*>(useragent));
    return false;
  }

  std::string universalmediacenterContent;
  const bool ret{XFILE::CCurlFile::GetMimeType(CURL(url), universalmediacenterContent, useragent)};
  if (ret && !universalmediacenterContent.empty())
  {
    *content = strdup(universalmediacenterContent.c_str());
  }
  return ret;
}

bool Interface_Filesystem::get_content_type(void* universalmediacenterBase,
                                            const char* url,
                                            char** content,
                                            const char* useragent)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url || !content || !useragent)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', url='{}', content='{}', "
               "useragent='{}')",
               universalmediacenterBase, static_cast<const void*>(url), static_cast<const void*>(content),
               static_cast<const void*>(useragent));
    return false;
  }

  std::string universalmediacenterContent;
  const bool ret{XFILE::CCurlFile::GetContentType(CURL(url), universalmediacenterContent, useragent)};
  if (ret && !universalmediacenterContent.empty())
  {
    *content = strdup(universalmediacenterContent.c_str());
  }
  return ret;
}

bool Interface_Filesystem::get_cookies(void* universalmediacenterBase, const char* url, char** cookies)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url || !cookies)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', url='{}', cookies='{}')", universalmediacenterBase,
               static_cast<const void*>(url), static_cast<const void*>(cookies));
    return false;
  }

  std::string universalmediacenterCookies;
  const bool ret{XFILE::CCurlFile::GetCookies(CURL(url), universalmediacenterCookies)};
  if (ret && !universalmediacenterCookies.empty())
  {
    *cookies = strdup(universalmediacenterCookies.c_str());
  }
  return ret;
}

bool Interface_Filesystem::get_http_header(void* universalmediacenterBase,
                                           const char* url,
                                           struct UNIVERSALMEDIA_HTTP_HEADER* headers)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url || !headers || !headers->handle)
  {
    CLog::LogF(LOGERROR, "Invalid data pointer given");
    return false;
  }

  CHttpHeader* httpHeader = static_cast<CHttpHeader*>(headers->handle);
  return XFILE::CCurlFile::GetHttpHeader(CURL(url), *httpHeader);
}

//------------------------------------------------------------------------------

bool Interface_Filesystem::http_header_create(void* universalmediacenterBase, struct UNIVERSALMEDIA_HTTP_HEADER* headers)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !headers)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', headers='{}')", universalmediacenterBase,
               static_cast<const void*>(headers));
    return false;
  }

  headers->handle = new CHttpHeader;
  headers->get_value = http_header_get_value;
  headers->get_values = http_header_get_values;
  headers->get_header = http_header_get_header;
  headers->get_mime_type = http_header_get_mime_type;
  headers->get_charset = http_header_get_charset;
  headers->get_proto_line = http_header_get_proto_line;

  return true;
}

void Interface_Filesystem::http_header_free(void* universalmediacenterBase, struct UNIVERSALMEDIA_HTTP_HEADER* headers)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !headers)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', headers='{}')", universalmediacenterBase,
               static_cast<const void*>(headers));
    return;
  }

  delete static_cast<CHttpHeader*>(headers->handle);
  headers->handle = nullptr;
}

char* Interface_Filesystem::http_header_get_value(void* universalmediacenterBase, void* handle, const char* param)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !handle || !param)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', handle='{}', param='{}')", universalmediacenterBase, handle,
               static_cast<const void*>(param));
    return nullptr;
  }

  const std::string string{static_cast<CHttpHeader*>(handle)->GetValue(param)};

  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

char** Interface_Filesystem::http_header_get_values(void* universalmediacenterBase,
                                                    void* handle,
                                                    const char* param,
                                                    int* length)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !handle || !param || !length)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', handle='{}', param='{}', "
               "length='{}')",
               universalmediacenterBase, handle, static_cast<const void*>(param), static_cast<const void*>(length));
    return nullptr;
  }

  const std::vector<std::string> values{static_cast<CHttpHeader*>(handle)->GetValues(param)};
  *length = static_cast<int>(values.size());
  char** ret = static_cast<char**>(malloc(sizeof(char*) * values.size()));
  for (int i = 0; i < *length; ++i)
  {
    ret[i] = strdup(values[i].c_str());
  }
  return ret;
}

char* Interface_Filesystem::http_header_get_header(void* universalmediacenterBase, void* handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !handle)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', handle='{}')", universalmediacenterBase, handle);
    return nullptr;
  }

  const std::string string{static_cast<CHttpHeader*>(handle)->GetHeader()};

  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

char* Interface_Filesystem::http_header_get_mime_type(void* universalmediacenterBase, void* handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !handle)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', handle='{}')", universalmediacenterBase, handle);
    return nullptr;
  }

  const std::string string{static_cast<CHttpHeader*>(handle)->GetMimeType()};

  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

char* Interface_Filesystem::http_header_get_charset(void* universalmediacenterBase, void* handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !handle)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', handle='{}')", universalmediacenterBase, handle);
    return nullptr;
  }

  const std::string string{static_cast<CHttpHeader*>(handle)->GetCharset()};

  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

char* Interface_Filesystem::http_header_get_proto_line(void* universalmediacenterBase, void* handle)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !handle)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', handle='{}')", universalmediacenterBase, handle);
    return nullptr;
  }

  const std::string string{static_cast<CHttpHeader*>(handle)->GetProtoLine()};

  if (string.empty())
    return nullptr;

  return strdup(string.c_str());
}

//------------------------------------------------------------------------------

void* Interface_Filesystem::open_file(void* universalmediacenterBase, const char* filename, unsigned int flags)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}')", universalmediacenterBase,
               static_cast<const void*>(filename));
    return nullptr;
  }

  auto file{std::make_unique<CFile>()};
  if (!file->Open(filename, TranslateFileReadBitsToUniversal Media Center(flags)))
    return nullptr;

  return static_cast<void*>(file.release());
}

void* Interface_Filesystem::open_file_for_write(void* universalmediacenterBase,
                                                const char* filename,
                                                bool overwrite)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !filename)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', filename='{}')", universalmediacenterBase,
               static_cast<const void*>(filename));
    return nullptr;
  }

  auto file{std::make_unique<CFile>()};
  if (!file->OpenForWrite(filename, overwrite))
    return nullptr;

  return static_cast<void*>(file.release());
}

ssize_t Interface_Filesystem::read_file(void* universalmediacenterBase, void* file, void* ptr, size_t size)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file || !ptr)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}', ptr='{}')", universalmediacenterBase, file, ptr);
    return -1;
  }

  return static_cast<CFile*>(file)->Read(ptr, size);
}

bool Interface_Filesystem::read_file_string(void* universalmediacenterBase,
                                            void* file,
                                            char* szLine,
                                            int lineLength)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file || !szLine)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}', szLine=='{}')", universalmediacenterBase, file,
               static_cast<void*>(szLine));
    return false;
  }

  return static_cast<CFile*>(file)->ReadLine(szLine, lineLength).code !=
         CFile::ReadLineResult::FAILURE;
}

ssize_t Interface_Filesystem::write_file(void* universalmediacenterBase, void* file, const void* ptr, size_t size)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file || !ptr)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}', ptr='{}')", universalmediacenterBase, file, ptr);
    return -1;
  }

  return static_cast<CFile*>(file)->Write(ptr, size);
}

void Interface_Filesystem::flush_file(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return;
  }

  static_cast<CFile*>(file)->Flush();
}

int64_t Interface_Filesystem::seek_file(void* universalmediacenterBase, void* file, int64_t position, int whence)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return -1;
  }

  return static_cast<CFile*>(file)->Seek(position, whence);
}

int Interface_Filesystem::truncate_file(void* universalmediacenterBase, void* file, int64_t size)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return -1;
  }

  return static_cast<CFile*>(file)->Truncate(size);
}

int64_t Interface_Filesystem::get_file_position(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return -1;
  }

  return static_cast<CFile*>(file)->GetPosition();
}

int64_t Interface_Filesystem::get_file_length(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return -1;
  }

  return static_cast<CFile*>(file)->GetLength();
}

double Interface_Filesystem::get_file_download_speed(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return 0.0;
  }

  return static_cast<CFile*>(file)->GetDownloadSpeed();
}

void Interface_Filesystem::close_file(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return;
  }

  auto* f{static_cast<CFile*>(file)};
  f->Close();
  delete f;
}

int Interface_Filesystem::get_file_chunk_size(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return -1;
  }

  return static_cast<CFile*>(file)->GetChunkSize();
}

bool Interface_Filesystem::io_control_get_seek_possible(void* universalmediacenterBase, void* file)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return false;
  }

  return static_cast<CFile*>(file)->IoControl(IOControl::SEEK_POSSIBLE, nullptr) != 0;
}

bool Interface_Filesystem::io_control_get_cache_status(void* universalmediacenterBase,
                                                       void* file,
                                                       struct VFS_CACHE_STATUS_DATA* status)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file || !status)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}, status='{}')", universalmediacenterBase, file,
               static_cast<const void*>(status));
    return false;
  }

  SCacheStatus data = {};
  const int ret{static_cast<CFile*>(file)->IoControl(IOControl::CACHE_STATUS, &data)};
  if (ret >= 0)
  {
    status->forward = data.forward;
    status->maxrate = data.maxrate;
    status->currate = data.currate;
    status->lowrate = data.lowrate;
    return true;
  }
  return false;
}

bool Interface_Filesystem::io_control_set_cache_rate(void* universalmediacenterBase, void* file, uint32_t rate)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return false;
  }

  return static_cast<CFile*>(file)->IoControl(IOControl::CACHE_SETRATE, &rate) >= 0;
}

bool Interface_Filesystem::io_control_set_retry(void* universalmediacenterBase, void* file, bool retry)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return false;
  }

  return static_cast<CFile*>(file)->IoControl(IOControl::SET_RETRY, &retry) >= 0;
}

char** Interface_Filesystem::get_property_values(
    void* universalmediacenterBase, void* file, int type, const char* name, int* numValues)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file || !name || !numValues)
  {
    CLog::LogF(LOGERROR,
               "Invalid data (addon='{}', file='{}', name='{}', "
               "numValues='{}')",
               universalmediacenterBase, file, static_cast<const void*>(name), static_cast<void*>(numValues));
    return nullptr;
  }

  XFILE::FileProperty internalType;
  switch (type)
  {
    case ADDON_FILE_PROPERTY_RESPONSE_PROTOCOL:
      internalType = XFILE::FileProperty::RESPONSE_PROTOCOL;
      break;
    case ADDON_FILE_PROPERTY_RESPONSE_HEADER:
      internalType = XFILE::FileProperty::RESPONSE_HEADER;
      break;
    case ADDON_FILE_PROPERTY_CONTENT_TYPE:
      internalType = XFILE::FileProperty::CONTENT_TYPE;
      break;
    case ADDON_FILE_PROPERTY_CONTENT_CHARSET:
      internalType = XFILE::FileProperty::CONTENT_CHARSET;
      break;
    case ADDON_FILE_PROPERTY_MIME_TYPE:
      internalType = XFILE::FileProperty::MIME_TYPE;
      break;
    case ADDON_FILE_PROPERTY_EFFECTIVE_URL:
      internalType = XFILE::FileProperty::EFFECTIVE_URL;
      break;
    default:
      CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
      return nullptr;
  };

  const std::vector<std::string> values{
      static_cast<CFile*>(file)->GetPropertyValues(internalType, name)};
  *numValues = static_cast<int>(values.size());
  char** ret = static_cast<char**>(malloc(sizeof(char*) * values.size()));
  for (int i = 0; i < *numValues; ++i)
  {
    ret[i] = strdup(values[i].c_str());
  }
  return ret;
}

void* Interface_Filesystem::curl_create(void* universalmediacenterBase, const char* url)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !url)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', url='{}')", universalmediacenterBase,
               static_cast<const void*>(url));
    return nullptr;
  }

  auto file{std::make_unique<CFile>()};
  if (!file->CURLCreate(url))
    return nullptr;

  return static_cast<void*>(file.release());
}

bool Interface_Filesystem::curl_add_option(
    void* universalmediacenterBase, void* file, int type, const char* name, const char* value)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file || !name || !value)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}', name='{}', value='{}')", universalmediacenterBase,
               file, static_cast<const void*>(name), static_cast<const void*>(value));
    return false;
  }

  XFILE::CURLOptionType internalType;
  switch (type)
  {
    case ADDON_CURL_OPTION_OPTION:
      internalType = XFILE::CURLOptionType::OPTION;
      break;
    case ADDON_CURL_OPTION_PROTOCOL:
      internalType = XFILE::CURLOptionType::PROTOCOL;
      break;
    case ADDON_CURL_OPTION_CREDENTIALS:
      internalType = XFILE::CURLOptionType::CREDENTIALS;
      break;
    case ADDON_CURL_OPTION_HEADER:
      internalType = XFILE::CURLOptionType::HEADER;
      break;
    default:
      throw std::logic_error("Interface_Filesystem::curl_add_option - invalid curl option type");
      return false;
  }

  return static_cast<CFile*>(file)->CURLAddOption(internalType, name, value);
}

bool Interface_Filesystem::curl_open(void* universalmediacenterBase, void* file, unsigned int flags)
{
  const auto* addon = static_cast<const CAddonDll*>(universalmediacenterBase);
  if (!addon || !file)
  {
    CLog::LogF(LOGERROR, "Invalid data (addon='{}', file='{}')", universalmediacenterBase, file);
    return false;
  }

  return static_cast<CFile*>(file)->CURLOpen(TranslateFileReadBitsToUniversal Media Center(flags));
}

} /* namespace ADDON */
