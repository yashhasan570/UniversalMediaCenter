/*
 *  Copyright (C) 2012-2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIConnectivityManagerNetworkCallback.h"

#include "CompileInfo.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

namespace
{

static std::string className =
    std::string(CCompileInfo::GetClass()) + "/interfaces/ConnectivityManagerNetworkCallback";

} // namespace

CJNIConnectivityManagerNetworkCallback::CJNIConnectivityManagerNetworkCallback()
  : CJNIBase(className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNIConnectivityManagerNetworkCallback::~CJNIConnectivityManagerNetworkCallback()
{
  remove_instance(this);
}

void CJNIConnectivityManagerNetworkCallback::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(className.c_str());
  if (cClass)
  {
    JNINativeMethod methods[] = {
        {"_onAvailable", "(Landroid/net/Network;)V",
         reinterpret_cast<void*>(&CJNIConnectivityManagerNetworkCallback::_onAvailable)},
        {"_onLost", "(Landroid/net/Network;)V",
         reinterpret_cast<void*>(&CJNIConnectivityManagerNetworkCallback::_onLost)},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods) / sizeof(methods[0]));
  }
}

void CJNIConnectivityManagerNetworkCallback::_onAvailable(JNIEnv* env,
                                                              jobject thiz,
                                                              jobject network)
{
  CJNIConnectivityManagerNetworkCallback* inst = find_instance(thiz);
  if (inst)
    inst->onAvailable(CJNINetwork(jhobject::fromJNI(network)));
}

void CJNIConnectivityManagerNetworkCallback::_onLost(JNIEnv* env, jobject thiz, jobject network)
{
  CJNIConnectivityManagerNetworkCallback* inst = find_instance(thiz);
  if (inst)
    inst->onLost(CJNINetwork(jhobject::fromJNI(network)));
}
