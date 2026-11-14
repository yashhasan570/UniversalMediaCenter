/*
 *  Copyright (C) 2017-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace tinyxml2
{
class XMLNode;
}

namespace UNIVERSAL MEDIA CENTER
{
namespace KEYMAP
{
/*!
 * \ingroup keymap
 *
 * \brief Interface for classes that can map buttons to Universal Media Center actions
 */
class IKeyMapper
{
public:
  virtual ~IKeyMapper() = default;

  virtual void MapActions(int windowId, const tinyxml2::XMLNode* pDevice) = 0;

  virtual void Clear() = 0;
};
} // namespace KEYMAP
} // namespace UNIVERSAL MEDIA CENTER
