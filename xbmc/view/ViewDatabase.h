/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "dbwrappers/Database.h"

#include <string>

class CViewState;

class CViewDatabase : public CDatabase
{
public:
  CViewDatabase();
  ~CViewDatabase() override;
  bool Open() override;

  bool GetViewState(const std::string &path, int windowID, CViewState &state, const std::string &skin);
  bool SetViewState(const std::string &path, int windowID, const CViewState &state, const std::string &skin);
  bool ClearViewStates(int windowID);

protected:
  void CreateTables() override;
  void CreateAnalytics() override;
  void UpdateTables(int version) override;
  int GetSchemaVersion() const override { return 6; }
  const char *GetBaseDBName() const override { return "ViewModes"; }
};
