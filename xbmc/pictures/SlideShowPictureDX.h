/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "SlideShowPicture.h"
#include "guilib/GUIShaderDX.h"

#include <wrl/client.h>

class CTexture;

class CSlideShowPicDX : public CSlideShowPic
{
public:
  CSlideShowPicDX() = default;
  ~CSlideShowPicDX() override = default;

protected:
  void Render(float* x, float* y, CTexture* pTexture, UNIVERSAL MEDIA CENTER::UTILS::COLOR::Color color) override;

private:
  bool UpdateVertexBuffer(Vertex* vertices);

  Microsoft::WRL::ComPtr<ID3D11Buffer> m_vb;
};
