/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "IDirtyRegionSolver.h"

class CUnionDirtyRegionSolver : public IDirtyRegionSolver
{
public:
  void Solve(const CDirtyRegionList &input, CDirtyRegionList &output) override;
};

class CFillViewportAlwaysRegionSolver : public IDirtyRegionSolver
{
public:
  void Solve(const CDirtyRegionList &input, CDirtyRegionList &output) override;
};

class CFillViewportOnChangeRegionSolver : public IDirtyRegionSolver
{
public:
  void Solve(const CDirtyRegionList &input, CDirtyRegionList &output) override;
};

class CGreedyDirtyRegionSolver : public IDirtyRegionSolver
{
public:
  CGreedyDirtyRegionSolver();
  void Solve(const CDirtyRegionList &input, CDirtyRegionList &output) override;
private:
  float m_costNewRegion;
  float m_costPerArea;
};
