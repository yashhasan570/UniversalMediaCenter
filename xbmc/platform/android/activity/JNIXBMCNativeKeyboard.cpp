/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNINativeKeyboard.h"

#include "CompileInfo.h"
#include "utils/log.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/NativeKeyboard";

CJNINativeKeyboard::CJNINativeKeyboard(IKeyboardInputHandler* handler)
  : CJNIBase(s_className),
    m_handler(handler)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNINativeKeyboard::~CJNINativeKeyboard()
{
  remove_instance(this);
}

void CJNINativeKeyboard::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if (cClass)
  {
    JNINativeMethod methods[] = {
        {"_onTextChanged", "(Ljava/lang/String;)V",
         reinterpret_cast<void*>(&CJNINativeKeyboard::_onTextChanged)},
        {"_onInputFinished", "(Ljava/lang/String;)V",
         reinterpret_cast<void*>(&CJNINativeKeyboard::_onInputFinished)},
        {"_onInputCanceled", "()V",
         reinterpret_cast<void*>(&CJNINativeKeyboard::_onInputCanceled)},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods) / sizeof(methods[0]));
  }
}

void CJNINativeKeyboard::show(const std::string& heading,
                                  const std::string& initialText,
                                  bool hiddenInput)
{
  JNIEnv* env = _jnienv();
  jstring jHeading = env->NewStringUTF(heading.c_str());
  jstring jInitialText = env->NewStringUTF(initialText.c_str());

  call_method<void>(m_object, "show", "(Ljava/lang/String;Ljava/lang/String;Z)V", jHeading,
                    jInitialText, (jboolean)hiddenInput);

  env->DeleteLocalRef(jHeading);
  env->DeleteLocalRef(jInitialText);
}

void CJNINativeKeyboard::setText(const std::string& text)
{
  JNIEnv* env = _jnienv();
  jstring jText = env->NewStringUTF(text.c_str());

  call_method<void>(m_object, "setText", "(Ljava/lang/String;)V", jText);

  env->DeleteLocalRef(jText);
}

void CJNINativeKeyboard::hide()
{
  call_method<void>(m_object, "hide", "()V");
}

void CJNINativeKeyboard::_onTextChanged(JNIEnv* env, jobject thiz, jstring text)
{
  CJNINativeKeyboard* inst = find_instance(thiz);
  if (inst && inst->m_handler)
    inst->m_handler->OnTextChanged(jcast<std::string>(jhstring::fromJNI(text)));
  else
    CLog::LogF(LOGERROR, "Cannot find native keyboard instance");
}

void CJNINativeKeyboard::_onInputFinished(JNIEnv* env, jobject thiz, jstring text)
{
  CJNINativeKeyboard* inst = find_instance(thiz);
  if (inst && inst->m_handler)
    inst->m_handler->OnInputFinished(jcast<std::string>(jhstring::fromJNI(text)));
  else
    CLog::LogF(LOGERROR, "Cannot find native keyboard instance");
}

void CJNINativeKeyboard::_onInputCanceled(JNIEnv* env, jobject thiz)
{
  CJNINativeKeyboard* inst = find_instance(thiz);
  if (inst && inst->m_handler)
    inst->m_handler->OnInputCanceled();
  else
    CLog::LogF(LOGERROR, "Cannot find native keyboard instance");
}
