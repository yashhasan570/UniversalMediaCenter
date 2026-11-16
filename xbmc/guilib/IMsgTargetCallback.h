/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

/*!
\file IMsgTargetCallback.h
\brief
*/

#include "GUIMessage.h"

/*!
 \ingroup winman
 \brief
 */
class IMsgTargetCallback
{
public:
  virtual bool OnMessage(CGUIMessage& message) = 0;
  virtual ~IMsgTargetCallback() = default;
};
