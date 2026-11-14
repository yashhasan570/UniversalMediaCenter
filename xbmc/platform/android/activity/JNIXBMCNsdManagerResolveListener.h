/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <androidjni/JNIBase.h>
#include <androidjni/NsdManager.h>

namespace jni
{

class CJNINsdManagerResolveListener : public CJNINsdManagerResolveListener, public CJNIInterfaceImplem<CJNINsdManagerResolveListener>
{
public:
public:
  CJNINsdManagerResolveListener();
  CJNINsdManagerResolveListener(const CJNINsdManagerResolveListener& other);
  explicit CJNINsdManagerResolveListener(const jni::jhobject &object) : CJNIBase(object) {}
  ~CJNINsdManagerResolveListener() override;

  static void RegisterNatives(JNIEnv* env);

  // CJNINsdManagerResolveListener interface
  void onResolveFailed(const CJNINsdServiceInfo& serviceInfo, int errorCode) override = 0;
  void onServiceResolved(const CJNINsdServiceInfo& serviceInfo) override = 0;

protected:
  static void _onResolveFailed(JNIEnv* env, jobject thiz, jobject serviceInfo, jint errorCode);
  static void _onServiceResolved(JNIEnv* env, jobject thiz, jobject serviceInfo);

};

}

