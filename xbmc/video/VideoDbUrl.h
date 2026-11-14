/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DbUrl.h"

class CVariant;

class CVideoDbUrl : public CDbUrl
{
public:
  CVideoDbUrl();
  ~CVideoDbUrl() override;

  const std::string& GetItemType() const { return m_itemType; }

protected:
  bool parse() override;
  bool validateOption(const std::string &key, const CVariant &value) override;

private:
  std::string m_itemType;
};
