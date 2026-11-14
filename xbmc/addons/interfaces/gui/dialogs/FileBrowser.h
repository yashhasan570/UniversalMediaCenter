/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/gui/dialogs/filebrowser.h"

#include <string>
#include <string_view>
#include <vector>

class CMediaSource;

extern "C"
{

  struct AddonGlobalInterface;

  namespace ADDON
  {

  /*!
   * @brief Global gui Add-on to Universal Media Center callback functions
   *
   * To hold functions not related to a instance type and usable for
   * every add-on type.
   *
   * Related add-on header is ".//addons/universalmediacenter-dev-kit/include/universalmediacenter/gui/dialogs/FileBrowser.h"
   */
  struct Interface_GUIDialogFileBrowser
  {
    static void Init(AddonGlobalInterface* addonInterface);
    static void DeInit(AddonGlobalInterface* addonInterface);

    /*!
     * @brief callback functions from add-on to universalmediacenter
     *
     * @note To add a new function use the "_" style to directly identify an
     * add-on callback function. Everything with CamelCase is only to be used
     * in Universal Media Center.
     *
     * The parameter `universalmediacenterBase` is used to become the pointer for a `CAddonDll`
     * class.
     */
    //@{
    static bool show_and_get_directory(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                       const char* shares,
                                       const char* heading,
                                       const char* path_in,
                                       char** path_out,
                                       bool write_only);

    static bool show_and_get_file(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                  const char* shares,
                                  const char* mask,
                                  const char* heading,
                                  const char* path_in,
                                  char** path_out,
                                  bool use_thumbs,
                                  bool use_file_directories);

    static bool show_and_get_file_from_dir(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                           const char* directory,
                                           const char* mask,
                                           const char* heading,
                                           const char* path_in,
                                           char** path_out,
                                           bool use_thumbs,
                                           bool use_file_directories,
                                           bool singleList);

    static bool show_and_get_file_list(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                       const char* shares,
                                       const char* mask,
                                       const char* heading,
                                       char*** file_list,
                                       unsigned int* entries,
                                       bool use_thumbs,
                                       bool use_file_directories);

    static bool show_and_get_source(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    const char* path_in,
                                    char** path_out,
                                    bool allow_network_shares,
                                    const char* additional_share,
                                    const char* type);

    static bool show_and_get_image(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                   const char* shares,
                                   const char* heading,
                                   const char* path_in,
                                   char** path_out);

    static bool show_and_get_image_list(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                        const char* shares,
                                        const char* heading,
                                        char*** file_list,
                                        unsigned int* entries);

    static void clear_file_list(UNIVERSALMEDIA_HANDLE universalmediacenterBase, char*** file_list, unsigned int entries);
    //@}

  private:
    static void GetVECShares(std::vector<CMediaSource>& vecShares,
                             std::string_view strShares,
                             const std::string& strPath);
  };

  } /* namespace ADDON */
} /* extern "C" */
