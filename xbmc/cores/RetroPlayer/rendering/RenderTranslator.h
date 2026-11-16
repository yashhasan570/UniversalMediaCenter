/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/GameSettings.h"

extern "C"
{
#include <libavutil/pixfmt.h>
}

namespace UNIVERSAL MEDIA CENTER
{
namespace RETRO
{
class CRenderTranslator
{
public:
  /*!
   * \brief Translate a pixel format to a string suitable for logging
   */
  static const char* TranslatePixelFormat(AVPixelFormat format);

  /*!
   * \brief Translate a scaling method to a string suitable for logging
   */
  static const char* TranslateScalingMethod(SCALINGMETHOD scalingMethod);

  /*!
   * \brief Translate a width in pixels to a width in bytes
   *
   * \param width The width in pixels
   * \param format The pixel format
   *
   * \return The width in bytes, or 0 if unknown
   */
  static unsigned int TranslateWidthToBytes(unsigned int width, AVPixelFormat format);
};
} // namespace RETRO
} // namespace UNIVERSAL MEDIA CENTER
