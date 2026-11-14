/*
 *  Copyright (C) 2005-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER
{
namespace MOUSE
{
/*!
 * \ingroup mouse
 *
 * \brief Simple class for mouse events
 */
class CMouseEvent
{
public:
  CMouseEvent(int actionID, int state = 0, float offsetX = 0, float offsetY = 0)
    : m_id(actionID),
      m_state(state),
      m_offsetX(offsetX),
      m_offsetY(offsetY)
  {
  }

  int m_id;
  int m_state;
  float m_offsetX;
  float m_offsetY;
};
} // namespace MOUSE
} // namespace UNIVERSAL MEDIA CENTER
