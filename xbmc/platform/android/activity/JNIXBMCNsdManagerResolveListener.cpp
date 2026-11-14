/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNINsdManagerResolveListener.h"

#include "CompileInfo.h"

#include <androidjni/Context.h>
#include <androidjni/NsdServiceInfo.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;


static std::string s_className = std::string(CCompileInfo::GetClass()) + "/interfaces/NsdManagerResolveListener";

CJNINsdManagerResolveListener::CJNINsdManagerResolveListener()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNINsdManagerResolveListener::CJNINsdManagerResolveListener(const CJNINsdManagerResolveListener& other)
  : CJNIBase(other)
{
  add_instance(m_object, this);
}

CJNINsdManagerResolveListener::~CJNINsdManagerResolveListener()
{
  remove_instance(this);
}

void CJNINsdManagerResolveListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onResolveFailed", "(Landroid/net/nsd/NsdServiceInfo;I)V", (void*)&CJNINsdManagerResolveListener::_onResolveFailed},
      {"_onServiceResolved", "(Landroid/net/nsd/NsdServiceInfo;)V", (void*)&CJNINsdManagerResolveListener::_onServiceResolved},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNINsdManagerResolveListener::_onResolveFailed(JNIEnv* env, jobject thiz, jobject serviceInfo, jint errorCode)
{
  CJNINsdManagerResolveListener *inst = find_instance(thiz);
  if (inst)
    inst->onResolveFailed(CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo)), errorCode);
}

void CJNINsdManagerResolveListener::_onServiceResolved(JNIEnv* env, jobject thiz, jobject serviceInfo)
{
  CJNINsdManagerResolveListener *inst = find_instance(thiz);
  if (inst)
    inst->onServiceResolved(CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo)));
}
