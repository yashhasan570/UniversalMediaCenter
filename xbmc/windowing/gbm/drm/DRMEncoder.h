/*
 *  Copyright (C) 2005-2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DRMCrtc.h"
#include "DRMObject.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace WINDOWING
{
namespace GBM
{

class CDRMEncoder : public CDRMObject
{
public:
  explicit CDRMEncoder(int fd, uint32_t encoder);
  CDRMEncoder(const CDRMEncoder&) = delete;
  CDRMEncoder& operator=(const CDRMEncoder&) = delete;
  ~CDRMEncoder() = default;

  uint32_t GetEncoderId() const { return m_encoder->encoder_id; }
  uint32_t GetCrtcId() const { return m_encoder->crtc_id; }
  std::vector<CDRMCrtc*> GetPossibleCrtcs(const std::vector<std::unique_ptr<CDRMCrtc>>& crtcs,
                                          CDRMCrtc* preferred = nullptr) const;

private:
  struct DrmModeEncoderDeleter
  {
    void operator()(drmModeEncoder* p) { drmModeFreeEncoder(p); }
  };

  std::unique_ptr<drmModeEncoder, DrmModeEncoderDeleter> m_encoder;
};

} // namespace GBM
} // namespace WINDOWING
} // namespace UNIVERSAL MEDIA CENTER
