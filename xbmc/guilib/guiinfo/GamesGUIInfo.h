/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "guilib/guiinfo/GUIInfoProvider.h"
namespace UNIVERSAL MEDIA CENTER::GAME
{
class CAchievementRuntime;
} // namespace UNIVERSAL MEDIA CENTER::GAME

namespace UNIVERSAL MEDIA CENTER::GUILIB::GUIINFO
{

class CGUIInfo;

class CGamesGUIInfo : public CGUIInfoProvider
{
public:
  CGamesGUIInfo() = default;
  explicit CGamesGUIInfo(const UNIVERSAL MEDIA CENTER::GAME::CAchievementRuntime& achievementRuntime)
    : m_achievementRuntime(&achievementRuntime)
  {
  }
  ~CGamesGUIInfo() override = default;

  // UNIVERSAL MEDIA CENTER::GUILIB::GUIINFO::IGUIInfoProvider implementation
  bool InitCurrentItem(CFileItem* item) override;
  bool GetLabel(std::string& value,
                const CFileItem* item,
                int contextWindow,
                const CGUIInfo& info,
                std::string* fallback) const override;
  bool GetInt(int& value,
              const CGUIListItem* item,
              int contextWindow,
              const CGUIInfo& info) const override;
  bool GetBool(bool& value,
               const CGUIListItem* item,
               int contextWindow,
               const CGUIInfo& info) const override;

private:
  const UNIVERSAL MEDIA CENTER::GAME::CAchievementRuntime& AchievementRuntime() const;

  const UNIVERSAL MEDIA CENTER::GAME::CAchievementRuntime* m_achievementRuntime{nullptr};
};

} // namespace UNIVERSAL MEDIA CENTER::GUILIB::GUIINFO
