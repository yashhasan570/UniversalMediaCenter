/*
 *  Copyright (C) 2017-2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace UNIVERSAL MEDIA CENTER::SHADER
{
/*!
 * \brief Interface for a shader texture
 *
 * The interface is left relatively generic. The implementation should be able
 * to manage any resources required by the texture.
 */
class IShaderTexture
{
public:
  virtual ~IShaderTexture() = default;

  /*!
   * \brief Return width of texture
   *
   * \return Width of the texture in texels
   */
  virtual float GetWidth() const = 0;

  /*!
   * \brief Return height of texture
   *
   * \return Height of the texture in texels
   */
  virtual float GetHeight() const = 0;
};
} // namespace UNIVERSAL MEDIA CENTER::SHADER
