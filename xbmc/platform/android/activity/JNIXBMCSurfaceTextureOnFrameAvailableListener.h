/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <androidjni/JNIBase.h>
#include <androidjni/SurfaceTexture.h>

namespace jni
{

class CJNISurfaceTextureOnFrameAvailableListener : public CJNISurfaceTextureOnFrameAvailableListener, public CJNIInterfaceImplem<CJNISurfaceTextureOnFrameAvailableListener>
{
public:
  CJNISurfaceTextureOnFrameAvailableListener();
  CJNISurfaceTextureOnFrameAvailableListener(const CJNISurfaceTextureOnFrameAvailableListener& other);
  CJNISurfaceTextureOnFrameAvailableListener(const jni::jhobject &object) : CJNIBase(object) {}
  ~CJNISurfaceTextureOnFrameAvailableListener() override;

  static void RegisterNatives(JNIEnv* env);

  void onFrameAvailable(CJNISurfaceTexture) override {}

protected:
  static void _onFrameAvailable(JNIEnv* env, jobject thiz, jobject surface);
};

} // namespace jni
