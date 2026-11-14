/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "EventLoop.h"
#include "App.h"

#include "platform/android/activity/JNIMainActivity.h"
#include "platform/android/activity/JNIAudioManagerOnAudioFocusChangeListener.h"
#include "platform/android/activity/JNIBroadcastReceiver.h"
#include "platform/android/activity/JNIConnectivityManagerNetworkCallback.h"
#include "platform/android/activity/JNIDisplayManagerDisplayListener.h"
#include "platform/android/activity/JNIFile.h"
#include "platform/android/activity/JNIJsonHandler.h"
#include "platform/android/activity/JNIMainView.h"
#include "platform/android/activity/JNIMediaSession.h"
#include "platform/android/activity/JNINativeKeyboard.h"
#include "platform/android/activity/JNINsdManagerDiscoveryListener.h"
#include "platform/android/activity/JNINsdManagerRegistrationListener.h"
#include "platform/android/activity/JNINsdManagerResolveListener.h"
#include "platform/android/activity/JNISpeechRecognitionListener.h"
#include "platform/android/activity/JNISurfaceTextureOnFrameAvailableListener.h"
#include "platform/android/activity/JNITextureCache.h"
#include "platform/android/activity/JNIURIUtils.h"
#include "platform/android/activity/JNIVideoView.h"

#include <stdint.h>
#include <stdio.h>
#include <thread>

#include <android/log.h>
#include <unistd.h>

using namespace jni;

namespace
{

class LogRedirector
{
  // redirect stdout / stderr to logcat
  // based on https://codelab.wordpress.com/2014/11/03/how-to-use-standard-output-streams-for-logging-in-android-apps/

public:
  LogRedirector()
  {
    // make stdout line-buffered and stderr unbuffered
    setvbuf(stdout, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);

    // spawn the logging thread
    std::thread thread(&LogRedirector::Run);
    thread.detach();
  }

private:
  static void Run()
  {
    // create a pipe and redirect stdout and stderr
    int pfds[2];
    pipe(pfds);
    dup2(pfds[1], STDOUT_FILENO);
    dup2(pfds[1], STDERR_FILENO);

    ssize_t rdsz;
    char buf[128];
    while ((rdsz = read(pfds[0], buf, sizeof(buf) - 1)) > 0)
    {
      if (buf[rdsz - 1] == '\n')
        --rdsz;

      buf[rdsz] = 0; // add null-terminator
      __android_log_write(ANDROID_LOG_DEBUG, "Universal Media Center", buf);
    }
  }
};

LogRedirector g_LogRedirector;

} // namespace

extern void android_main(struct android_app* state)
{
  {
    CEventLoop eventLoop(state);
    IInputHandler inputHandler;
    CApp& theApp = CApp::Create(state->activity, inputHandler);
    if (theApp.isValid())
    {
      eventLoop.run(theApp, inputHandler);
      theApp.Quit();
    }
    else
      CApp::android_printf("android_main: setup failed");

    CApp::android_printf("android_main: Exiting");

    CApp::Destroy();
  }
  // We need to call exit() so that all loaded libraries are properly unloaded
  // otherwise on the next start of the Activity android will simply re-use
  // those loaded libs in the state they were in when we quit Universal Media Center last time
  // which will lead to crashes because of global/static classes that haven't
  // been properly uninitialized
  exit(0);
}

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
  jint version = JNI_VERSION_1_6;
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), version) != JNI_OK)
    return -1;

  CJNIMainActivity::RegisterNatives(env);
  CJNIAudioManagerOnAudioFocusChangeListener::RegisterNatives(env);
  CJNIBroadcastReceiver::RegisterNatives(env);
  CJNIConnectivityManagerNetworkCallback::RegisterNatives(env);
  CJNIDisplayManagerDisplayListener::RegisterNatives(env);
  CJNIFile::RegisterNatives(env);
  CJNIJsonHandler::RegisterNatives(env);
  CJNIMainView::RegisterNatives(env);
  CJNIMediaSession::RegisterNatives(env);
  CJNINativeKeyboard::RegisterNatives(env);
  CJNINsdManagerDiscoveryListener::RegisterNatives(env);
  CJNINsdManagerRegistrationListener::RegisterNatives(env);
  CJNINsdManagerResolveListener::RegisterNatives(env);
  CJNISpeechRecognitionListener::RegisterNatives(env);
  CJNISurfaceTextureOnFrameAvailableListener::RegisterNatives(env);
  CJNITextureCache::RegisterNatives(env);
  CJNIURIUtils::RegisterNatives(env);
  CJNIVideoView::RegisterNatives(env);

  return version;
}
