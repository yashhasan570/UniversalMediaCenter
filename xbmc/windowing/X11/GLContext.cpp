/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "GLContext.h"

bool CGLContext::IsExtSupported(const char* extension) const
{
  std::string name;

  name  = " ";
  name += extension;
  name += " ";

  return m_extensions.find(name) != std::string::npos;
}
