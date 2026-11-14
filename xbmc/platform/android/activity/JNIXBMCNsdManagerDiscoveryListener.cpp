/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNINsdManagerDiscoveryListener.h"

#include "CompileInfo.h"
#include "utils/log.h"

#include <androidjni/Context.h>
#include <androidjni/NsdServiceInfo.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;


static std::string s_className = std::string(CCompileInfo::GetClass()) + "/interfaces/NsdManagerDiscoveryListener";

CJNINsdManagerDiscoveryListener::CJNINsdManagerDiscoveryListener()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNINsdManagerDiscoveryListener::CJNINsdManagerDiscoveryListener(const CJNINsdManagerDiscoveryListener& other)
  : CJNIBase(other)
{
  add_instance(m_object, this);
}

CJNINsdManagerDiscoveryListener::~CJNINsdManagerDiscoveryListener()
{
  remove_instance(this);
}

void CJNINsdManagerDiscoveryListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onDiscoveryStarted", "(Ljava/lang/String;)V", (void*)&CJNINsdManagerDiscoveryListener::_onDiscoveryStarted},
      {"_onDiscoveryStopped", "(Ljava/lang/String;)V", (void*)&CJNINsdManagerDiscoveryListener::_onDiscoveryStopped},
      {"_onServiceFound", "(Landroid/net/nsd/NsdServiceInfo;)V", (void*)&CJNINsdManagerDiscoveryListener::_onServiceFound},
      {"_onServiceLost", "(Landroid/net/nsd/NsdServiceInfo;)V", (void*)&CJNINsdManagerDiscoveryListener::_onServiceLost},
      {"_onStartDiscoveryFailed", "(Ljava/lang/String;I)V", (void*)&CJNINsdManagerDiscoveryListener::_onStartDiscoveryFailed},
      {"_onStopDiscoveryFailed", "(Ljava/lang/String;I)V", (void*)&CJNINsdManagerDiscoveryListener::_onStopDiscoveryFailed},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNINsdManagerDiscoveryListener::_onDiscoveryStarted(JNIEnv* env, jobject thiz, jstring serviceType)
{
  (void)env;
  (void)thiz;

  std::string st = jcast<std::string>(jhstring(serviceType));
  CLog::Log(LOGDEBUG, "CJNINsdManagerDiscoveryListener::onDiscoveryStarted type: {}", st);
}

void CJNINsdManagerDiscoveryListener::_onDiscoveryStopped(JNIEnv* env, jobject thiz, jstring serviceType)
{
  (void)env;
  (void)thiz;

  std::string st = jcast<std::string>(jhstring(serviceType));
  CLog::Log(LOGDEBUG, "CJNINsdManagerDiscoveryListener::onDiscoveryStopped type: {}", st);
}

void CJNINsdManagerDiscoveryListener::_onServiceFound(JNIEnv* env, jobject thiz, jobject serviceInfo)
{
  CJNINsdManagerDiscoveryListener *inst = find_instance(thiz);
  if (inst)
    inst->onServiceFound(CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo)));
}

void CJNINsdManagerDiscoveryListener::_onServiceLost(JNIEnv* env, jobject thiz, jobject serviceInfo)
{
  CJNINsdManagerDiscoveryListener *inst = find_instance(thiz);
  if (inst)
    inst->onServiceLost(CJNINsdServiceInfo(jhobject::fromJNI(serviceInfo)));
}

void CJNINsdManagerDiscoveryListener::_onStartDiscoveryFailed(JNIEnv* env, jobject thiz, jstring serviceType, jint errorCode)
{
  (void)env;

  CJNINsdManagerDiscoveryListener *inst = find_instance(thiz);
  if (inst)
    inst->onStartDiscoveryFailed(jcast<std::string>(jhstring(serviceType)), errorCode);
}

void CJNINsdManagerDiscoveryListener::_onStopDiscoveryFailed(JNIEnv* env, jobject thiz, jstring serviceType, jint errorCode)
{
  (void)env;

  CJNINsdManagerDiscoveryListener *inst = find_instance(thiz);
  if (inst)
    inst->onStopDiscoveryFailed(jcast<std::string>(jhstring(serviceType)), errorCode);
}
