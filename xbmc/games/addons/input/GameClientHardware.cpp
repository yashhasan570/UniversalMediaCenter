/*
 *  Copyright (C) 2015-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GameClientHardware.h"

#include "games/addons/GameClient.h"
#include "utils/log.h"

using namespace UNIVERSAL MEDIA CENTER;
using namespace GAME;

CGameClientHardware::CGameClientHardware(CGameClient& gameClient) : m_gameClient(gameClient)
{
}

void CGameClientHardware::OnResetButton()
{
  CLog::Log(LOGDEBUG, "{}: Sending hardware reset", m_gameClient.ID());
  m_gameClient.Reset();
}
