/*
 *  Copyright (C) 2012-2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNISpeechRecognitionListener.h"

#include "CompileInfo.h"
#include "utils/log.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className =
    std::string(CCompileInfo::GetClass()) + "/interfaces/SpeechRecognitionListener";

void CJNISpeechRecognitionListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if (cClass)
  {
    JNINativeMethod methods[] = {
        {"_onReadyForSpeech", "(Landroid/os/Bundle;)V",
         reinterpret_cast<void*>(&CJNISpeechRecognitionListener::_onReadyForSpeech)},
        {"_onError", "(I)V", reinterpret_cast<void*>(&CJNISpeechRecognitionListener::_onError)},
        {"_onResults", "(Landroid/os/Bundle;)V",
         reinterpret_cast<void*>(&CJNISpeechRecognitionListener::_onResults)},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods) / sizeof(methods[0]));
  }
}

CJNISpeechRecognitionListener::CJNISpeechRecognitionListener() : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(
      s_className))); // TODO: GetDotClassName cannot be used, something is preventing CJNIBase from setting the classname
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNISpeechRecognitionListener::~CJNISpeechRecognitionListener()
{
  remove_instance(this);
}

void CJNISpeechRecognitionListener::_onReadyForSpeech(JNIEnv* env, jobject thiz, jobject bundle)
{
  CJNISpeechRecognitionListener* inst = find_instance(thiz);
  if (inst)
    inst->onReadyForSpeech(CJNIBundle(jhobject::fromJNI(bundle)));
  else
    CLog::LogF(LOGERROR, "Cannot find speech recognizer listener instance");
}

void CJNISpeechRecognitionListener::_onError(JNIEnv* env, jobject thiz, jint i)
{
  CLog::LogF(LOGERROR, "Speech recognition error: {}", i);

  CJNISpeechRecognitionListener* inst = find_instance(thiz);
  if (inst)
    inst->onError(i);
  else
    CLog::LogF(LOGERROR, "Cannot find speech recognizer listener instance");
}

void CJNISpeechRecognitionListener::_onResults(JNIEnv* env, jobject thiz, jobject bundle)
{
  CJNISpeechRecognitionListener* inst = find_instance(thiz);
  if (inst)
    inst->onResults(CJNIBundle(jhobject::fromJNI(bundle)));
  else
    CLog::LogF(LOGERROR, "Cannot find speech recognizer listener instance");
}
