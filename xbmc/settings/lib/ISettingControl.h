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

class ISettingControl
{
public:
  ISettingControl();
  virtual ~ISettingControl() = default;

  virtual std::string GetType() const = 0;
  const std::string& GetFormat() const { return m_format; }
  bool GetDelayed() const { return m_delayed; }
  void SetDelayed(bool delayed) { m_delayed = delayed; }

  virtual bool Deserialize(const TiXmlNode *node, bool update = false);
  virtual bool SetFormat(const std::string &format) { return true; }

protected:
  bool m_delayed = false;
  std::string m_format;

  static Logger s_logger;
};
