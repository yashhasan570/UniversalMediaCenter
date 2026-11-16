/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/Filesystem.h"

extern "C"
{

struct VFSDirEntry;
struct AddonGlobalInterface;

namespace ADDON
{

struct Interface_Filesystem
{
  static void Init(AddonGlobalInterface* addonInterface);
  static void DeInit(AddonGlobalInterface* addonInterface);

  static unsigned int TranslateFileReadBitsToUniversal Media Center(unsigned int addonFlags);

  /*!
   * @brief callback functions from add-on to universalmediacenter
   *
   * @note For add of new functions use the "_" style to identify direct a
   * add-on callback function. Everything with CamelCase is only for the
   * usage in Universal Media Center only.
   *
   * The parameter `universalmediacenterBase` is used to become the pointer for a `CAddonDll`
   * class.
   */
  ///@{
  static bool can_open_directory(void* universalmediacenterBase, const char* url);
  static bool create_directory(void* universalmediacenterBase, const char* path);
  static bool directory_exists(void* universalmediacenterBase, const char* path);
  static bool remove_directory(void* universalmediacenterBase, const char* path);
  static bool remove_directory_recursive(void* universalmediacenterBase, const char* path);
  static bool get_directory(void* universalmediacenterBase,
                            const char* path,
                            const char* mask,
                            struct VFSDirEntry** items,
                            unsigned int* num_items);
  static void free_directory(void* universalmediacenterBase, struct VFSDirEntry* items, unsigned int num_items);

  static bool file_exists(void* universalmediacenterBase, const char* filename, bool useCache);
  static bool stat_file(void* universalmediacenterBase, const char* filename, struct STAT_STRUCTURE* buffer);
  static bool delete_file(void* universalmediacenterBase, const char* filename);
  static bool rename_file(void* universalmediacenterBase, const char* filename, const char* newFileName);
  static bool copy_file(void* universalmediacenterBase, const char* filename, const char* dest);
  static char* get_file_md5(void* universalmediacenterBase, const char* filename);
  static char* get_cache_thumb_name(void* universalmediacenterBase, const char* filename);
  static char* make_legal_filename(void* universalmediacenterBase, const char* filename);
  static char* make_legal_path(void* universalmediacenterBase, const char* path);
  static char* translate_special_protocol(void* universalmediacenterBase, const char* strSource);
  static bool get_disk_space(
      void* universalmediacenterBase, const char* path, uint64_t* capacity, uint64_t* free, uint64_t* available);
  static bool is_internet_stream(void* universalmediacenterBase, const char* path, bool strictCheck);
  static bool is_on_lan(void* universalmediacenterBase, const char* path);
  static bool is_remote(void* universalmediacenterBase, const char* path);
  static bool is_local(void* universalmediacenterBase, const char* path);
  static bool is_url(void* universalmediacenterBase, const char* path);

  static bool get_http_header(void* universalmediacenterBase, const char* url, struct UNIVERSALMEDIA_HTTP_HEADER* headers);
  static bool get_mime_type(void* universalmediacenterBase, const char* url, char** content, const char* useragent);
  static bool get_content_type(void* universalmediacenterBase,
                               const char* url,
                               char** content,
                               const char* useragent);
  static bool get_cookies(void* universalmediacenterBase, const char* url, char** cookies);

  /*!
   * @brief Callback functions addon class universalmediacenter::vfs::CFile
   */
  ///@{
  static bool http_header_create(void* universalmediacenterBase, struct UNIVERSALMEDIA_HTTP_HEADER* headers);
  static void http_header_free(void* universalmediacenterBase, struct UNIVERSALMEDIA_HTTP_HEADER* headers);

  static char* http_header_get_value(void* universalmediacenterBase, void* handle, const char* param);
  static char** http_header_get_values(void* universalmediacenterBase,
                                       void* handle,
                                       const char* param,
                                       int* length);
  static char* http_header_get_header(void* universalmediacenterBase, void* handle);
  static char* http_header_get_mime_type(void* universalmediacenterBase, void* handle);
  static char* http_header_get_charset(void* universalmediacenterBase, void* handle);
  static char* http_header_get_proto_line(void* universalmediacenterBase, void* handle);
  ///@}

  /*!
   * @brief Callback functions addon class universalmediacenter::vfs::CFile
   */
  ///@{
  static void* open_file(void* universalmediacenterBase, const char* filename, unsigned int flags);
  static void* open_file_for_write(void* universalmediacenterBase, const char* filename, bool overwrite);
  static ssize_t read_file(void* universalmediacenterBase, void* file, void* ptr, size_t size);
  static bool read_file_string(void* universalmediacenterBase, void* file, char* szLine, int lineLength);
  static ssize_t write_file(void* universalmediacenterBase, void* file, const void* ptr, size_t size);
  static void flush_file(void* universalmediacenterBase, void* file);
  static int64_t seek_file(void* universalmediacenterBase, void* file, int64_t position, int whence);
  static int truncate_file(void* universalmediacenterBase, void* file, int64_t size);
  static int64_t get_file_position(void* universalmediacenterBase, void* file);
  static int64_t get_file_length(void* universalmediacenterBase, void* file);
  static double get_file_download_speed(void* universalmediacenterBase, void* file);
  static void close_file(void* universalmediacenterBase, void* file);
  static int get_file_chunk_size(void* universalmediacenterBase, void* file);
  static bool io_control_get_seek_possible(void* universalmediacenterBase, void* file);
  static bool io_control_get_cache_status(void* universalmediacenterBase,
                                          void* file,
                                          struct VFS_CACHE_STATUS_DATA* status);
  static bool io_control_set_cache_rate(void* universalmediacenterBase, void* file, uint32_t rate);
  static bool io_control_set_retry(void* universalmediacenterBase, void* file, bool retry);
  static char** get_property_values(
      void* universalmediacenterBase, void* file, int type, const char* name, int* numValues);

  static void* curl_create(void* universalmediacenterBase, const char* url);
  static bool curl_add_option(
      void* universalmediacenterBase, void* file, int type, const char* name, const char* value);
  static bool curl_open(void* universalmediacenterBase, void* file, unsigned int flags);
  ///@}
  ///@}
};

} /* namespace ADDON */
} /* extern "C" */
