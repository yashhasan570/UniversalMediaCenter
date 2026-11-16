/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "video/geometry/FrameSampling.h"
#include "video/geometry/SampledGeometry.h"

#include <functional>

class CFileItem;
class CDVDStreamInfo;
struct VideoPicture;

namespace UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY
{
struct FrameRef;
struct ReducedFrame;
} // namespace UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY

//! \brief Decodes a file at several points and describes each picture to the detector.
class CVideoFileGeometry
{
public:
  //! \brief Whether ExtractContentGeometry() may open the item.
  static bool CanMeasure(const CFileItem& fileItem);

  //! \brief Sample a file at several points and work out its picture rectangle. Decodes in
  //! software with film grain synthesis off. \p cancelled is asked between positions, and a
  //! scan reporting itself cancelled must not be stored.
  static UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY::SampledGeometry ExtractContentGeometry(
      const CFileItem& fileItem,
      const UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY::SamplingParams& sampling = {},
      const UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY::CombinerParams& combining = {},
      const std::function<bool()>& cancelled = {});

  //! \brief Describe a decoded picture to the detector. Reads the layout from the pixel format
  //! descriptor, so an unfamiliar one is described correctly or refused. Fails for a picture
  //! whose buffer exposes no planes.
  static bool BuildGeometryFrameRef(const VideoPicture& picture,
                                    const CDVDStreamInfo& hint,
                                    UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY::FrameRef& frame);

  //! \brief Point a FrameRef at a reduced copy instead of the picture itself. What such a
  //! frame detects is in the reduction's coordinates, and scaling it back is the caller's job.
  static bool BuildGeometryFrameRef(const UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY::ReducedFrame& reduction,
                                    const VideoPicture& picture,
                                    const CDVDStreamInfo& hint,
                                    UNIVERSAL MEDIA CENTER::VIDEO::GEOMETRY::FrameRef& frame);
};
