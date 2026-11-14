/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNINsdManagerRegistrationListener.h"

#include "CompileInfo.h"
#include "utils/log.h"

#include <androidjni/Context.h>
#include <androidjni/NsdServiceInfo.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;


static std::string s_className = std::string(CCompileInfo::GetClass()) + "/interfaces/NsdManagerRegistrationListener";

CJNINsdManagerRegistrationListener::CJNINsdManagerRegistrationListener()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNINsdManagerRegistrationListener::CJNINsdManagerRegistrationListener(const CJNINsdManagerRegistrationListener& other)
  : CJNIBase(other)
{
  add_instance(m_object, this);
}

CJNINsdManagerRegistrationListener::~CJNINsdManagerRegistrationListener()
{
  remove_instance(this);
}

void CJNINsdManagerRegistrationListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onRegistrationFailed", "(Landroid/net/nsd/NsdServiceInfo;I)V", (void*)&CJNINsdManagerRegistrationListener::_onRegistrationFailed},
      {"_onServiceRegistered", "(Landroid/net/nsd/NsdServiceInfo;)V", (void*)&CJNINsdManagerRegistrationListener::_onServiceRegistered},
      {"_onServiceUnregistered", "(Landroid/net/nsd/NsdServiceInfo;)V", (void*)&CJNINsdManagerRegistrationListener::_onServiceUnregistered},
      {"_onUnregistrationFailed", "(Landroid/net/nsd/NsdServiceInfo;I)V", (void*)&CJNINsdManagerRegistrationListener::_onUnregistrationFailed},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNINsdManagerRegistrationListener::_onRegistrationFailed(JNIEnv* env, jobject thiz, jobject serviceInfo, jint errorCode)
{
  CJNINsdServiceInfo si = CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo));
  CLog::Log(LOGERROR, "ZeroconfAndroid: {}.{} registration failed: {}", si.getServiceName(),
            si.getServiceType(), errorCode);
}

void CJNINsdManagerRegistrationListener::_onServiceRegistered(JNIEnv* env, jobject thiz, jobject serviceInfo)
{
  CJNINsdServiceInfo si = CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo));
  CLog::Log(LOGINFO, "ZeroconfAndroid: {}.{} now registered and active", si.getServiceName(),
            si.getServiceType());
}

void CJNINsdManagerRegistrationListener::_onServiceUnregistered(JNIEnv* env, jobject thiz, jobject serviceInfo)
{
  CJNINsdServiceInfo si = CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo));
  CLog::Log(LOGINFO, "ZeroconfAndroid: {}.{} registration removed", si.getServiceName(),
            si.getServiceType());
}

void CJNINsdManagerRegistrationListener::_onUnregistrationFailed(JNIEnv* env, jobject thiz, jobject serviceInfo, jint errorCode)
{
  CJNINsdServiceInfo si = CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo));
  CLog::Log(LOGERROR, "ZeroconfAndroid: {}.{} unregistration failed: {}", si.getServiceName(),
            si.getServiceType(), errorCode);
}

