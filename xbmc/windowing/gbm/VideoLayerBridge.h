/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace GBM
{

class CVideoLayerBridge
{
public:
  virtual ~CVideoLayerBridge() = default;
  virtual void Disable() {}
};

} // namespace GBM
} // namespace WINDOWING
} // namespace UNIVERSAL MEDIA CENTER
