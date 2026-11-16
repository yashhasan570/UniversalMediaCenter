/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "SlideShowPicture.h"

class CTexture;

class CSlideShowPicGLES : public CSlideShowPic
{
public:
  CSlideShowPicGLES() = default;
  ~CSlideShowPicGLES() override = default;

protected:
  void Render(float* x, float* y, CTexture* pTexture, UNIVERSAL MEDIA CENTER::UTILS::COLOR::Color color) override;
};
