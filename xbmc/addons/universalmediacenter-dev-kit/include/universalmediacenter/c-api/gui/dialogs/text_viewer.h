/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_GUI_DIALOGS_TEXT_VIEWER_H
#define C_API_GUI_DIALOGS_TEXT_VIEWER_H

#include "../definitions.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef struct AddonToUniversal Media CenterFuncTable__dialogTextViewer
  {
    void (*open)(UNIVERSALMEDIA_HANDLE universalmediacenterBase, const char* heading, const char* text);
  } AddonToUniversal Media CenterFuncTable__dialogTextViewer;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_GUI_DIALOGS_TEXT_VIEWER_H */
