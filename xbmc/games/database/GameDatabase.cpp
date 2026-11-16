/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GameDatabase.h"

#include "DatabaseTypes.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace GAME;

CGameDatabase::CGameDatabase() : CDatabase(DATABASE::TYPE_GAMES)
{
}

CGameDatabase::~CGameDatabase() = default;

bool CGameDatabase::Open()
{
  return CDatabase::Open();
}

void CGameDatabase::CreateTables()
{
  m_gameClients.Create();
}

void CGameDatabase::CreateAnalytics()
{
  m_gameClients.CreateAnalytics();
}

void CGameDatabase::UpdateTables(int version)
{
  m_gameClients.UpdateTables(version);
}
