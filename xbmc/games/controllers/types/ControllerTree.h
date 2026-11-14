/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

//
// Note: Hierarchy of headers is:
//
//  - ControllerTree.h (this file)
//    - ControllerHub.h
//      - PortNode.h
//        - ControllerNode.h
//
#include "ControllerHub.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{

/*!
 * \ingroup games
 *
 * \brief Collection of ports on a console
 */
using CControllerTree = CControllerHub;

} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER
