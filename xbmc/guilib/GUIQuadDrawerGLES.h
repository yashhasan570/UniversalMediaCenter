/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "utils/ColorUtils.h"
#include "utils/Geometry.h"

class CTexture;

// Used for control hit-rect/dirty-region debug overlays via CGUITexture::DrawQuad(). Owned by
// CRenderSystemGLES, which binds it as the DrawQuadFunc callback in CGUITextureGLES::Register().
class CGUIQuadDrawerGLES
{
public:
  void DrawQuad(const CRect& coords,
                KODI::UTILS::COLOR::Color color,
                CTexture* texture,
                const CRect* texCoords,
                float depth,
                bool blending);
};
