/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIAudioManagerOnAudioFocusChangeListener.h"

#include "CompileInfo.h"
#include "App.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/interfaces/AudioManagerOnAudioFocusChangeListener";

CJNIAudioManagerOnAudioFocusChangeListener::CJNIAudioManagerOnAudioFocusChangeListener()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNIAudioManagerOnAudioFocusChangeListener::CJNIAudioManagerOnAudioFocusChangeListener(const CJNIAudioManagerOnAudioFocusChangeListener& other)
  : CJNIBase(other)
{
  add_instance(m_object, this);
}

CJNIAudioManagerOnAudioFocusChangeListener::~CJNIAudioManagerOnAudioFocusChangeListener()
{
  remove_instance(this);
}

void CJNIAudioManagerOnAudioFocusChangeListener::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onAudioFocusChange", "(I)V", (void*)&CJNIAudioManagerOnAudioFocusChangeListener::_onAudioFocusChange},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNIAudioManagerOnAudioFocusChangeListener::_onAudioFocusChange(JNIEnv *env, jobject thiz, jint focusChange)
{
  (void)env;

  CJNIAudioManagerOnAudioFocusChangeListener *inst = find_instance(thiz);
  if (inst)
    inst->onAudioFocusChange(focusChange);
}

void CJNIAudioManagerOnAudioFocusChangeListener::onAudioFocusChange(int focusChange)
{
  CApp::Get().onAudioFocusChange(focusChange);
}
