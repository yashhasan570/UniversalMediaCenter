/*
 *  Copyright (C) 2013-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/logtypes.h"

#include <string>

class TiXmlNode;

enum class SettingUpdateType {
  Unknown = 0,
  Rename,
  Change
};

class CSettingUpdate
{
public:
  CSettingUpdate();
  virtual ~CSettingUpdate() = default;

  auto operator<=>(const CSettingUpdate&) const = default;

  virtual bool Deserialize(const TiXmlNode *node);

  SettingUpdateType GetType() const { return m_type; }
  const std::string& GetValue() const { return m_value; }

private:
  bool setType(const std::string &type);

  SettingUpdateType m_type = SettingUpdateType::Unknown;
  std::string m_value;

  static Logger s_logger;
};
