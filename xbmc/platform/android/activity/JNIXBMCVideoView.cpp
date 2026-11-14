/*
 *  Copyright (C) 2016 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIVideoView.h"

#include "CompileInfo.h"
#include "utils/StringUtils.h"
#include "utils/log.h"

#include <algorithm>
#include <cassert>
#include <list>

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/VideoView";

void CJNIVideoView::RegisterNatives(JNIEnv* env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_surfaceChanged", "(Landroid/view/SurfaceHolder;III)V", (void*)&CJNIVideoView::_surfaceChanged},
      {"_surfaceCreated", "(Landroid/view/SurfaceHolder;)V", (void*)&CJNIVideoView::_surfaceCreated},
      {"_surfaceDestroyed", "(Landroid/view/SurfaceHolder;)V", (void*)&CJNIVideoView::_surfaceDestroyed}
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

CJNIVideoView::CJNIVideoView(const jni::jhobject &object)
  : CJNIBase(object)
{
}

CJNIVideoView* CJNIVideoView::createVideoView(CJNISurfaceHolderCallback* callback)
{
  std::string signature = "()L" + s_className + ";";

  CJNIVideoView* pvw = new CJNIVideoView(call_static_method<jhobject>(
      _jnienv(), CJNIContext::getClassLoader().loadClass(ToDotClassName(s_className)),
      "createVideoView", signature.c_str()));
  if (!*pvw)
  {
    CLog::Log(LOGERROR, "Cannot instantiate VideoView!!");
    delete pvw;
    return nullptr;
  }

  add_instance(pvw->get_raw(), pvw);
  pvw->m_callback = callback;
  if (pvw->isCreated())
    pvw->m_surfaceCreated.Set();
  pvw->add();

  return pvw;
}

void CJNIVideoView::_surfaceChanged(JNIEnv *env, jobject thiz, jobject holder, jint format, jint width, jint height )
{
  (void)env;

  CJNIVideoView *inst = find_instance(thiz);
  if (inst)
    inst->surfaceChanged(CJNISurfaceHolder(jhobject::fromJNI(holder)), format, width, height);
}

void CJNIVideoView::_surfaceCreated(JNIEnv* env, jobject thiz, jobject holder)
{
  (void)env;

  CJNIVideoView *inst = find_instance(thiz);
  if (inst)
    inst->surfaceCreated(CJNISurfaceHolder(jhobject::fromJNI(holder)));
}

void CJNIVideoView::_surfaceDestroyed(JNIEnv* env, jobject thiz, jobject holder)
{
  (void)env;

  CJNIVideoView *inst = find_instance(thiz);
  if (inst)
    inst->surfaceDestroyed(CJNISurfaceHolder(jhobject::fromJNI(holder)));
}

void CJNIVideoView::surfaceChanged(CJNISurfaceHolder holder, int format, int width, int height)
{
  if (m_callback)
    m_callback->surfaceChanged(holder, format, width, height);
}

void CJNIVideoView::surfaceCreated(CJNISurfaceHolder holder)
{
  if (m_callback)
    m_callback->surfaceCreated(holder);
  m_surfaceCreated.Set();
}

void CJNIVideoView::surfaceDestroyed(CJNISurfaceHolder holder)
{
  m_surfaceCreated.Reset();
  if (m_callback)
    m_callback->surfaceDestroyed(holder);
}

bool CJNIVideoView::waitForSurface(unsigned int millis)
{
  return m_surfaceCreated.Wait(std::chrono::milliseconds(millis));
}

void CJNIVideoView::add()
{
  call_method<void>(m_object,
                    "add", "()V");
}

void CJNIVideoView::release()
{
  remove_instance(this);
  call_method<void>(m_object,
                    "release", "()V");
}

CJNISurface CJNIVideoView::getSurface()
{
  return call_method<jhobject>(m_object,
                               "getSurface", "()Landroid/view/Surface;");
}

const CRect& CJNIVideoView::getSurfaceRect()
{
  return m_surfaceRect;
}

void CJNIVideoView::setSurfaceRect(const CRect& rect)
{
  call_method<void>(m_object,
                    "setSurfaceRect", "(IIII)V", int(rect.x1), int(rect.y1), int(rect.x2), int(rect.y2));
  m_surfaceRect = rect;
}

bool CJNIVideoView::isCreated() const
{
  return get_field<jboolean>(m_object, "mIsCreated");
}

