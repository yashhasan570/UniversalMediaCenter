/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "SampledGeometry.h"

#include "video/geometry/GeometryTransforms.h"

#include <algorithm>

namespace UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY
{

ContentGeometryRecord MakeContentGeometryRecord(const SampledGeometry& scan,
                                                const FileIdentity& identity)
{
  ContentGeometryRecord record;
  record.identity = identity;

  if (!scan.succeeded || !scan.combined.hasReading)
    return record;

  const StreamGeometry stream{scan.coded, scan.displayAspect, 0};
  for (const CRectInt& shape : scan.combined.shapes)
  {
    const float aspect{StoredAspect(AspectOf(ToSquarePixels(shape, stream)))};
    if (std::find(record.aspects.begin(), record.aspects.end(), aspect) == record.aspects.end())
      record.aspects.push_back(aspect);
  }

  return record;
}

} // namespace UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY
