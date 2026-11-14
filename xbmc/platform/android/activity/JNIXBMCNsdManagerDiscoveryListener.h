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

class CJNINsdManagerDiscoveryListener : public CJNINsdManagerDiscoveryListener, public CJNIInterfaceImplem<CJNINsdManagerDiscoveryListener>
{
public:
  CJNINsdManagerDiscoveryListener();
  CJNINsdManagerDiscoveryListener(const CJNINsdManagerDiscoveryListener& other);
  explicit CJNINsdManagerDiscoveryListener(const jni::jhobject &object) : CJNIBase(object) {}
  ~CJNINsdManagerDiscoveryListener() override;

  static void RegisterNatives(JNIEnv* env);

  // CJNINsdManagerDiscoveryListener interface
public:
  void onDiscoveryStarted(const std::string& serviceType) override = 0;
  void onDiscoveryStopped(const std::string& serviceType) override = 0;
  void onServiceFound(const CJNINsdServiceInfo& serviceInfo) override = 0;
  void onServiceLost(const CJNINsdServiceInfo& serviceInfo) override = 0;
  void onStartDiscoveryFailed(const std::string& serviceType, int errorCode) override = 0;
  void onStopDiscoveryFailed(const std::string& serviceType, int errorCode) override = 0;

protected:
  static void _onDiscoveryStarted(JNIEnv* env, jobject thiz, jstring serviceType);
  static void _onDiscoveryStopped(JNIEnv* env, jobject thiz, jstring serviceType);
  static void _onServiceFound(JNIEnv* env, jobject thiz, jobject serviceInfo);
  static void _onServiceLost(JNIEnv* env, jobject thiz, jobject serviceInfo);
  static void _onStartDiscoveryFailed(JNIEnv* env, jobject thiz, jstring serviceType, jint errorCode);
  static void _onStopDiscoveryFailed(JNIEnv* env, jobject thiz, jstring serviceType, jint errorCode);
};

}

