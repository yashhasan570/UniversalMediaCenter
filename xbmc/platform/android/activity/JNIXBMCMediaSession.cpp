/*
 *  Copyright (C) 2017 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIMediaSession.h"

#include "AndroidKey.h"
#include "CompileInfo.h"
#include "ServiceBroker.h"
#include "App.h"
#include "application/Application.h"
#include "application/ApplicationComponents.h"
#include "application/ApplicationPlayer.h"
#include "input/actions/Action.h"
#include "input/actions/ActionIDs.h"
#include "messaging/ApplicationMessenger.h"

#include <androidjni/Context.h>
#include <androidjni/KeyEvent.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/MediaSession";

CJNIMediaSession::CJNIMediaSession()
  : CJNIBase(s_className)
{
  m_object = new_object(CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)));
  m_object.setGlobal();

  add_instance(m_object, this);
}

CJNIMediaSession::CJNIMediaSession(const CJNIMediaSession& other)
  : CJNIBase(other)
{
  add_instance(m_object, this);
}

CJNIMediaSession::~CJNIMediaSession()
{
  remove_instance(this);
}

void CJNIMediaSession::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_onPlayRequested", "()V", (void*)&CJNIMediaSession::_onPlayRequested},
      {"_onPauseRequested", "()V", (void*)&CJNIMediaSession::_onPauseRequested},
      {"_onNextRequested", "()V", (void*)&CJNIMediaSession::_onNextRequested},
      {"_onPreviousRequested", "()V", (void*)&CJNIMediaSession::_onPreviousRequested},
      {"_onForwardRequested", "()V", (void*)&CJNIMediaSession::_onForwardRequested},
      {"_onRewindRequested", "()V", (void*)&CJNIMediaSession::_onRewindRequested},
      {"_onStopRequested", "()V", (void*)&CJNIMediaSession::_onStopRequested},
      {"_onSeekRequested", "(J)V", (void*)&CJNIMediaSession::_onSeekRequested},
      {"_onMediaButtonEvent", "(Landroid/content/Intent;)Z", (void*)&CJNIMediaSession::_onMediaButtonEvent},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

void CJNIMediaSession::activate(bool state)
{
  if (state == m_isActive)
    return;

  call_method<void>(m_object,
                    "activate", "(Z)V",
                    (jboolean)state);
  m_isActive = state;
}

void CJNIMediaSession::updatePlaybackState(const CJNIPlaybackState& state)
{
  call_method<void>(m_object,
                    "updatePlaybackState", "(Landroid/media/session/PlaybackState;)V",
                    state.get_raw());
}

void CJNIMediaSession::updateMetadata(const CJNIMediaMetadata& myData)
{
  call_method<void>(m_object,
                    "updateMetadata", "(Landroid/media/MediaMetadata;)V",
                    myData.get_raw());
}

void CJNIMediaSession::updateIntent(const CJNIIntent& intent)
{
  call_method<void>(m_object,
                    "updateIntent", "(Landroid/content/Intent;)V",
                    intent.get_raw());
}

void CJNIMediaSession::OnPlayRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
  {
    if (appPlayer->IsPaused())
      CServiceBroker::GetAppMessenger()->PostMsg(TMSG_GUI_ACTION, WINDOW_INVALID, -1,
                                                 static_cast<void*>(new CAction(ACTION_PAUSE)));
  }
}

void CJNIMediaSession::OnPauseRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
  {
    if (!appPlayer->IsPaused())
      CServiceBroker::GetAppMessenger()->PostMsg(TMSG_GUI_ACTION, WINDOW_INVALID, -1,
                                                 static_cast<void*>(new CAction(ACTION_PAUSE)));
  }
}

void CJNIMediaSession::OnNextRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
    CServiceBroker::GetAppMessenger()->PostMsg(TMSG_GUI_ACTION, WINDOW_INVALID, -1,
                                               static_cast<void*>(new CAction(ACTION_NEXT_ITEM)));
}

void CJNIMediaSession::OnPreviousRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
    CServiceBroker::GetAppMessenger()->PostMsg(TMSG_GUI_ACTION, WINDOW_INVALID, -1,
                                               static_cast<void*>(new CAction(ACTION_PREV_ITEM)));
}

void CJNIMediaSession::OnForwardRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
  {
    CServiceBroker::GetAppMessenger()->PostMsg(
        TMSG_GUI_ACTION, WINDOW_INVALID, -1,
        static_cast<void*>(new CAction(ACTION_PLAYER_FORWARD)));
  }
}

void CJNIMediaSession::OnRewindRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
  {
    CServiceBroker::GetAppMessenger()->PostMsg(
        TMSG_GUI_ACTION, WINDOW_INVALID, -1, static_cast<void*>(new CAction(ACTION_PLAYER_REWIND)));
  }
}

void CJNIMediaSession::OnStopRequested()
{
  const auto& components = CServiceBroker::GetAppComponents();
  const auto appPlayer = components.GetComponent<CApplicationPlayer>();
  if (appPlayer->IsPlaying())
    CServiceBroker::GetAppMessenger()->PostMsg(TMSG_GUI_ACTION, WINDOW_INVALID, -1,
                                               static_cast<void*>(new CAction(ACTION_STOP)));
}

void CJNIMediaSession::OnSeekRequested(int64_t pos)
{
  g_application.SeekTime(pos / 1000.0);
}

bool CJNIMediaSession::OnMediaButtonEvent(const CJNIIntent& intent)
{
  if (CApp::Get().HasFocus())
  {
    CApp::Get().onReceive(intent);
    return true;
  }
  return false;
}

bool CJNIMediaSession::isActive() const
{
  return m_isActive;
}

/**********************/

void CJNIMediaSession::_onPlayRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnPlayRequested();
}

void CJNIMediaSession::_onPauseRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnPauseRequested();
}

void CJNIMediaSession::_onNextRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnNextRequested();
}

void CJNIMediaSession::_onPreviousRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnPreviousRequested();
}

void CJNIMediaSession::_onForwardRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnForwardRequested();
}

void CJNIMediaSession::_onRewindRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnRewindRequested();
}

void CJNIMediaSession::_onStopRequested(JNIEnv* env, jobject thiz)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnStopRequested();
}

void CJNIMediaSession::_onSeekRequested(JNIEnv* env, jobject thiz, jlong pos)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    inst->OnSeekRequested(pos);
}

bool CJNIMediaSession::_onMediaButtonEvent(JNIEnv* env, jobject thiz, jobject intent)
{
  (void)env;

  CJNIMediaSession *inst = find_instance(thiz);
  if (inst)
    return inst->OnMediaButtonEvent(CJNIIntent(jhobject::fromJNI(intent)));
  return false;
}

