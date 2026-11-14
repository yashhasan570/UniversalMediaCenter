/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <androidjni/AudioManager.h>
#include <androidjni/JNIBase.h>

namespace jni
{

class CJNIAudioManagerOnAudioFocusChangeListener : public CJNIAudioManagerAudioFocusChangeListener, public CJNIInterfaceImplem<CJNIAudioManagerOnAudioFocusChangeListener>
{
public:
  CJNIAudioManagerOnAudioFocusChangeListener();
  CJNIAudioManagerOnAudioFocusChangeListener(const CJNIAudioManagerOnAudioFocusChangeListener& other);
  explicit CJNIAudioManagerOnAudioFocusChangeListener(const jni::jhobject &object) : CJNIBase(object) {}
  ~CJNIAudioManagerOnAudioFocusChangeListener() override;

  static void RegisterNatives(JNIEnv* env);

  void onAudioFocusChange(int focusChange) override;

protected:
  static void _onAudioFocusChange(JNIEnv* env, jobject thiz, jint focusChange);
};

} // namespace jni
