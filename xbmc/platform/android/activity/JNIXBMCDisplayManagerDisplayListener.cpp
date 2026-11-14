/*
 *  Copyright (C) 2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIDisplayManagerDisplayListener.h"

#include "CompileInfo.h"
#include "App.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/interfaces/DisplayManagerDisplayListener";

CJNIDisplayManagerDisplayListener::CJNIDisplayManagerDisplayListener()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();
}

void CJNIDisplayManagerDisplayListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onDisplayAdded", "(I)V", reinterpret_cast<void*>(&CJNIDisplayManagerDisplayListener::_onDisplayAdded)},
      {"_onDisplayChanged", "(I)V", reinterpret_cast<void*>(&CJNIDisplayManagerDisplayListener::_onDisplayChanged)},
      {"_onDisplayRemoved", "(I)V", reinterpret_cast<void*>(&CJNIDisplayManagerDisplayListener::_onDisplayRemoved)},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNIDisplayManagerDisplayListener::_onDisplayAdded(JNIEnv *env, jobject context, jint displayId)
{
  static_cast<void>(env);
  static_cast<void>(context);

  CApp::Get().onDisplayAdded(displayId);
}

void CJNIDisplayManagerDisplayListener::_onDisplayChanged(JNIEnv *env, jobject context, jint displayId)
{
  static_cast<void>(env);
  static_cast<void>(context);

  CApp::Get().onDisplayChanged(displayId);
}

void CJNIDisplayManagerDisplayListener::_onDisplayRemoved(JNIEnv *env, jobject context, jint displayId)
{
  static_cast<void>(env);
  static_cast<void>(context);

  CApp::Get().onDisplayRemoved(displayId);
}
