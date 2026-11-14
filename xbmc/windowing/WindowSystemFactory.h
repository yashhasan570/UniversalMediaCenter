/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "WinSystem.h"

#include <functional>
#include <list>
#include <map>
#include <memory>

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{

class CWindowSystemFactory
{
public:
  static std::unique_ptr<CWinSystemBase> CreateWindowSystem(const std::string& name);
  static std::list<std::string> GetWindowSystems();
  static void RegisterWindowSystem(
      const std::function<std::unique_ptr<CWinSystemBase>()>& createFunction,
      const std::string& name = "default");

private:
  static std::list<std::pair<std::string, std::function<std::unique_ptr<CWinSystemBase>()>>>
      m_windowSystems;
};

} // namespace WINDOWING
} // namespace UNIVERSAL MEDIA CENTER
