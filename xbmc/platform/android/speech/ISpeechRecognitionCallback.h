/*
 *  Copyright (C) 2012-2022 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

namespace jni
{
class CJNIXBMCSpeechRecognitionListener;
}

class ISpeechRecognitionCallback
{
public:
  virtual ~ISpeechRecognitionCallback() = default;
  virtual void SpeechRecognitionDone(jni::CJNIXBMCSpeechRecognitionListener* listener) = 0;
};
