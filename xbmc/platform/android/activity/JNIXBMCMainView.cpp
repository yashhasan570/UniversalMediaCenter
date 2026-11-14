/*
 *  Copyright (C) 2017 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIMainView.h"

#include "CompileInfo.h"
#include "utils/StringUtils.h"
#include "utils/log.h"

#include <algorithm>
#include <cassert>
#include <list>

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/MainView";
CEvent CJNIMainView::m_surfaceCreated;
CJNIMainView* CJNIMainView::m_instance = nullptr;

void CJNIMainView::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_attach", "()V", (void*)&CJNIMainView::_attach},
      {"_surfaceChanged", "(Landroid/view/SurfaceHolder;III)V", (void*)&CJNIMainView::_surfaceChanged},
      {"_surfaceCreated", "(Landroid/view/SurfaceHolder;)V", (void*)&CJNIMainView::_surfaceCreated},
      {"_surfaceDestroyed", "(Landroid/view/SurfaceHolder;)V", (void*)&CJNIMainView::_surfaceDestroyed}
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

CJNIMainView::CJNIMainView(CJNISurfaceHolderCallback* callback)
  : m_callback(callback)
{
  m_instance = this;
}

void CJNIMainView::_attach(JNIEnv* env, jobject thiz)
{
  (void)env;

  if (m_instance)
    m_instance->attach(thiz);
}

void CJNIMainView::_surfaceChanged(JNIEnv *env, jobject thiz, jobject holder, jint format, jint width, jint height )
{
  (void)env;

  if (m_instance)
    m_instance->surfaceChanged(CJNISurfaceHolder(jhobject(holder)), format, width, height);
}

void CJNIMainView::_surfaceCreated(JNIEnv* env, jobject thiz, jobject holder)
{
  (void)env;

  if (m_instance)
    m_instance->surfaceCreated(CJNISurfaceHolder(jhobject(holder)));
}

void CJNIMainView::_surfaceDestroyed(JNIEnv* env, jobject thiz, jobject holder)
{
  (void)env;

  if (m_instance)
    m_instance->surfaceDestroyed(CJNISurfaceHolder(jhobject(holder)));
}

void CJNIMainView::attach(const jobject& thiz)
{
  if (!m_object)
  {
    m_object = jhobject(thiz);
    m_object.setGlobal();
  }
}

void CJNIMainView::surfaceChanged(CJNISurfaceHolder holder, int format, int width, int height)
{
  if (m_callback)
    m_callback->surfaceChanged(holder, format, width, height);
}

void CJNIMainView::surfaceCreated(CJNISurfaceHolder holder)
{
  if (m_callback)
    m_callback->surfaceCreated(holder);
  m_surfaceCreated.Set();
}

void CJNIMainView::surfaceDestroyed(CJNISurfaceHolder holder)
{
  m_surfaceCreated.Reset();
  if (m_callback)
    m_callback->surfaceDestroyed(holder);
}

bool CJNIMainView::waitForSurface(unsigned int millis)
{
  return m_surfaceCreated.Wait(std::chrono::milliseconds(millis));
}

bool CJNIMainView::isCreated() const
{
  if (!m_object)
    return false;
  return get_field<jboolean>(m_object, "mIsCreated");

}

