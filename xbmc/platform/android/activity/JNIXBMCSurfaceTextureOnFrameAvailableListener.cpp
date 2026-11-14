/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNISurfaceTextureOnFrameAvailableListener.h"

#include "CompileInfo.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/interfaces/SurfaceTextureOnFrameAvailableListener";

CJNISurfaceTextureOnFrameAvailableListener::CJNISurfaceTextureOnFrameAvailableListener()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNISurfaceTextureOnFrameAvailableListener::CJNISurfaceTextureOnFrameAvailableListener(const CJNISurfaceTextureOnFrameAvailableListener& other)
  : CJNIBase(other)
{
  add_instance(m_object, this);
}

CJNISurfaceTextureOnFrameAvailableListener::~CJNISurfaceTextureOnFrameAvailableListener()
{
  remove_instance(this);
}

void CJNISurfaceTextureOnFrameAvailableListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onFrameAvailable", "(Landroid/graphics/SurfaceTexture;)V", (void*)&CJNISurfaceTextureOnFrameAvailableListener::_onFrameAvailable},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNISurfaceTextureOnFrameAvailableListener::_onFrameAvailable(JNIEnv* env, jobject thiz, jobject surface)
{
  (void)env;

  CJNISurfaceTextureOnFrameAvailableListener *inst = find_instance(thiz);
  if (inst)
    inst->onFrameAvailable(CJNISurfaceTexture(jhobject::fromJNI(surface)));
}
