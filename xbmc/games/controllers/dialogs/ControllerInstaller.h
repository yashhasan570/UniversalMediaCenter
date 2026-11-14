/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "threads/Thread.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CControllerInstaller : public CThread
{
public:
  CControllerInstaller();
  ~CControllerInstaller() override = default;

protected:
  // implementation of CThread
  void Process() override;
};
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
