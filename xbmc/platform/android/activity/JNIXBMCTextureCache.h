/*
 *  Copyright (C) 2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <androidjni/JNIBase.h>

namespace jni
{

class CJNIXBMCTextureCache : public CJNIBase
{
public:
  CJNIXBMCTextureCache(const jni::jhobject& object) : CJNIBase(object) {}

  static void RegisterNatives(JNIEnv* env);

protected:
  ~CJNIXBMCTextureCache() override = default;

  static jstring _unwrapImageURL(JNIEnv* env, jobject thiz, jstring image);
};

} // namespace jni
