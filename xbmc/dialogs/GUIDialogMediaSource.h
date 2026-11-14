/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/GUIDialog.h"
#include "media/MediaSection.h"

#include <memory>
#include <string>
#include <vector>

class CFileItemList;
class CMediaSource;

class CGUIDialogMediaSource :
      public CGUIDialog
{
public:
  CGUIDialogMediaSource(void);
  ~CGUIDialogMediaSource(void) override;
  bool OnMessage(CGUIMessage& message) override;
  void OnDeinitWindow(int nextWindowID) override;
  bool OnBack(int actionID) override;
  static bool ShowAndAddMediaSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section);
  static bool ShowAndEditMediaSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section, const CMediaSource &share);
  static bool ShowAndEditMediaSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section, const std::string &share);

  bool IsConfirmed() const { return m_confirmed; }

  void SetShare(const CMediaSource &share);
  void SetTypeOfMedia(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section, bool editNotAdd = false);
protected:
  void OnPathBrowse(int item);
  void OnPath(int item);
  void OnPathAdd();
  void OnPathRemove(int item);
  void OnOK();
  void OnCancel();
  void UpdateButtons();
  int GetSelectedItem();
  void HighlightItem(int item);
  std::string GetUniqueMediaSourceName();
  static void OnMediaSourceChanged(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                                   const std::string& oldName,
                                   const CMediaSource& share);

  std::vector<std::string> GetPaths() const;

  UNIVERSAL MEDIA CENTER::MEDIA::MediaSection m_section{UNIVERSAL MEDIA CENTER::MEDIA::MediaSection::FILES};
  std::string m_name;
  std::unique_ptr<CFileItemList> m_paths;
  bool m_confirmed = false;
  bool m_bNameChanged = false;
};
