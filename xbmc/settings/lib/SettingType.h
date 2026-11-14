/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

/*!
 \ingroup settings
 \brief Basic setting types available in the settings system.
 */
enum class SettingType {
  Unknown = 0,
  Boolean,
  Integer,
  Number,
  String,
  Action,
  List
};
