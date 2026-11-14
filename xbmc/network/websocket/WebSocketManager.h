/*
 *  Copyright (C) 2011-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>

class CWebSocket;

class CWebSocketManager
{
public:
  static CWebSocket* Handle(const char* data, unsigned int length, std::string &response);
};
