/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_FILEBROWSER_H
#define C_API_GUI_DIALOGS_FILEBROWSER_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogFileBrowser
  {
    bool (*show_and_get_directory)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                   const char* shares,
                                   const char* heading,
                                   const char* path_in,
                                   char** path_out,
                                   bool writeOnly);
    bool (*show_and_get_file)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                              const char* shares,
                              const char* mask,
                              const char* heading,
                              const char* path_in,
                              char** path_out,
                              bool use_thumbs,
                              bool use_file_directories);
    bool (*show_and_get_file_from_dir)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                       const char* directory,
                                       const char* mask,
                                       const char* heading,
                                       const char* path_in,
                                       char** path_out,
                                       bool use_thumbs,
                                       bool use_file_directories,
                                       bool singleList);
    bool (*show_and_get_file_list)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                   const char* shares,
                                   const char* mask,
                                   const char* heading,
                                   char*** file_list,
                                   unsigned int* entries,
                                   bool use_thumbs,
                                   bool use_file_directories);
    bool (*show_and_get_source)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                const char* path_in,
                                char** path_out,
                                bool allow_network_shares,
                                const char* additional_share,
                                const char* type);
    bool (*show_and_get_image)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                               const char* shares,
                               const char* heading,
                               const char* path_in,
                               char** path_out);
    bool (*show_and_get_image_list)(UNIVERSALMEDIA_HANDLE universalmediacenterBase,
                                    const char* shares,
                                    const char* heading,
                                    char*** file_list,
                                    unsigned int* entries);
    void (*clear_file_list)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, char*** file_list, unsigned int entries);
  } AddonToUniversal Media CenterFuncTable_universalmediacenter_gui_dialogFileBrowser;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_FILEBROWSER_H */
