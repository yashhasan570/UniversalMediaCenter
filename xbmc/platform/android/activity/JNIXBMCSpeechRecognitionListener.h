/*
 *  Copyright (C) 2012-2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <androidjni/JNIBase.h>
#include <androidjni/SpeechRecognizer.h>

namespace jni
{

class CJNISpeechRecognitionListener
  : public CJNISpeechRecognitionListener,
    public CJNIInterfaceImplem<CJNISpeechRecognitionListener>
{
public:
  CJNISpeechRecognitionListener();
  ~CJNISpeechRecognitionListener() override;

  static void RegisterNatives(JNIEnv* env);

  void onReadyForSpeech(CJNIBundle bundle) override {}
  void onError(int error) override {}
  void onResults(CJNIBundle bundle) override {}

protected:
  static void _onReadyForSpeech(JNIEnv* env, jobject thiz, jobject bundle);
  static void _onError(JNIEnv* env, jobject thiz, jint i);
  static void _onResults(JNIEnv* env, jobject thiz, jobject bundle);
};

} // namespace jni
