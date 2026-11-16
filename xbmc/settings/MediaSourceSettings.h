/*
 *  Copyright (C) 2013-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "MediaSource.h"
#include "media/MediaSection.h"
#include "settings/lib/ISettingsHandler.h"

#include <array>
#include <string>
#include <string_view>
#include <vector>

class CProfileManager;

namespace tinyxml2
{
class XMLNode;
}

class CMediaSourceSettings : public ISettingsHandler
{
public:
  static CMediaSourceSettings& GetInstance();

  static std::string GetSourcesFile();

  void OnSettingsLoaded() override;
  void OnSettingsUnloaded() override;

  bool Load();
  bool Load(const std::string &file);
  bool Save() const;
  bool Save(const std::string &file) const;
  void Clear();

  std::vector<CMediaSource>& GetSources(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section);
  const std::string& GetDefaultSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section) const;
  void SetDefaultSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section, std::string_view source);
  static bool HasDefaultSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section);

  bool UpdateSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                    std::string_view strOldName,
                    std::string_view strUpdateChild,
                    const std::string& strUpdateValue);
  bool DeleteSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                    std::string_view strName,
                    std::string_view strPath,
                    bool virtualSource = false);
  bool AddShare(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section, const CMediaSource& share);
  bool UpdateShare(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                   std::string_view oldName,
                   const CMediaSource& share);

protected:
  CMediaSourceSettings();
  CMediaSourceSettings(const CMediaSourceSettings&) = delete;
  CMediaSourceSettings& operator=(CMediaSourceSettings const&) = delete;
  ~CMediaSourceSettings() override;

private:
  struct SectionSources
  {
    std::vector<CMediaSource> sources;
    std::string defaultSource;
  };

  bool GetSource(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                 const tinyxml2::XMLNode* source,
                 CMediaSource& share) const;
  void GetSources(const tinyxml2::XMLNode* rootElement,
                  UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                  SectionSources& sources) const;
  bool SetSources(tinyxml2::XMLNode* rootNode,
                  UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section,
                  const SectionSources& sources) const;

  SectionSources& At(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section);
  const SectionSources& At(UNIVERSAL MEDIA CENTER::MEDIA::MediaSection section) const;

  std::array<SectionSources, UNIVERSAL MEDIA CENTER::MEDIA::MEDIA_SECTIONS.size()> m_sections;
};
