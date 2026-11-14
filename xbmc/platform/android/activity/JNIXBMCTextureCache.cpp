/*
 *  Copyright (C) 2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNITextureCache.h"

#include "CompileInfo.h"
#include "imagefiles/ImageFileURL.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/TextureCache";

void CJNITextureCache::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if (cClass)
  {
    JNINativeMethod methods[] = {
        {"_unwrapImageURL", "(Ljava/lang/String;)Ljava/lang/String;",
         (void*)&CJNITextureCache::_unwrapImageURL},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods) / sizeof(methods[0]));
  }
}

jstring CJNITextureCache::_unwrapImageURL(JNIEnv* env, jobject thiz, jstring image)
{
  std::string strImage = jcast<std::string>(jhstring::fromJNI(image));
  std::string responseData = IMAGE_FILES::ToCacheKey(strImage);

  jstring jres = env->NewStringUTF(responseData.c_str());
  return jres;
}
