/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

class CVideoBufferDRMPRIME;

namespace UNIVERSAL MEDIA CENTER
{
namespace RENDERING
{
namespace CAPTURE
{
struct CaptureSpec;
struct CaptureResult;
} // namespace CAPTURE
} // namespace RENDERING
} // namespace UNIVERSAL MEDIA CENTER

//! \brief Screencap a direct-to-plane DRMPRIME video buffer.
//!
//! The video is on a DRM plane, not in the framebuffer, so it is imported as a
//! GL_TEXTURE_EXTERNAL_OES texture (the driver does YUV-to-RGB and detile),
//! drawn full-frame into a private FBO at the requested size and depth with
//! CRendererDRMPRIMEGLES::DrawTexture, read back, and tagged with the source
//! colorimetry. Render thread only, GL context current. GLES only; returns
//! false on any failure.
bool CaptureDRMPRIMEVideo(CVideoBufferDRMPRIME* buffer,
                          const UNIVERSAL MEDIA CENTER::RENDERING::CAPTURE::CaptureSpec& spec,
                          UNIVERSAL MEDIA CENTER::RENDERING::CAPTURE::CaptureResult& result);
