/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "SortUtils.h"

#include <map>

class ISortable
{
protected:
  /* make sure nobody deletes a pointer to this class */
  ~ISortable() = default;

public:
  virtual void ToSortable(SortItem& sortable, Field field) const = 0;
};
