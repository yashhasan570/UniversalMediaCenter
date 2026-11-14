/*
 *  Copyright (C) 2012-2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "platform/android/activity/JNISpeechRecognitionListener.h"

#include <memory>

namespace speech
{
class ISpeechRecognitionListener;
}

class ISpeechRecognitionCallback;

class CSpeechRecognitionListenerAndroid : public jni::CJNISpeechRecognitionListener
{
public:
  CSpeechRecognitionListenerAndroid(
      const std::shared_ptr<speech::ISpeechRecognitionListener>& listener,
      ISpeechRecognitionCallback& callback);
  ~CSpeechRecognitionListenerAndroid() override;

  void onReadyForSpeech(CJNIBundle bundle) override;
  void onError(int error) override;
  void onResults(CJNIBundle bundle) override;

private:
  CSpeechRecognitionListenerAndroid() = delete;

  std::shared_ptr<speech::ISpeechRecognitionListener> m_listener;
  ISpeechRecognitionCallback& m_callback;
};
