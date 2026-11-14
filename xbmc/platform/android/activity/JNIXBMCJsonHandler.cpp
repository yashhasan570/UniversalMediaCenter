/*
 *  Copyright (C) 2018 Christian Browet
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "JNIJsonHandler.h"

#include "CompileInfo.h"
#include "interfaces/json-rpc/JSONRPC.h"
#include "interfaces/json-rpc/JSONServiceDescription.h"
#include "interfaces/json-rpc/JSONUtils.h"

#include <androidjni/Context.h>
#include <androidjni/jutils-details.hpp>

using namespace jni;

static std::string s_className = std::string(CCompileInfo::GetClass()) + "/JsonRPC";

void CJNIJsonHandler::RegisterNatives(JNIEnv *env)
{
  jclass cClass = env->FindClass(s_className.c_str());
  if(cClass)
  {
    JNINativeMethod methods[] =
    {
      {"_requestJSON", "(Ljava/lang/String;)Ljava/lang/String;", (void*)&CJNIJsonHandler::_requestJSON},
    };

    env->RegisterNatives(cClass, methods, sizeof(methods)/sizeof(methods[0]));
  }
}

jstring CJNIJsonHandler::_requestJSON(JNIEnv *env, jobject thiz, jstring request)
{
  CJNIClient client;
  CJNITransportLayer transportLayer;

  std::string strRequest = jcast<std::string>(jhstring::fromJNI(request));
  std::string responseData = JSONRPC::CJSONRPC::MethodCall(strRequest, &transportLayer, &client);

  jstring jres = env->NewStringUTF(responseData.c_str());
  return jres;
}

/**********************************/

bool CJNIJsonHandler::CJNITransportLayer::PrepareDownload(const char *path, CVariant &details, std::string &protocol)
{
  return false;
}

bool CJNIJsonHandler::CJNITransportLayer::Download(const char *path, CVariant &result)
{
  return false;
}

int CJNIJsonHandler::CJNITransportLayer::GetCapabilities()
{
  return JSONRPC::Response;
}

int CJNIJsonHandler::CJNIClient::GetPermissionFlags()
{
  return JSONRPC::OPERATION_PERMISSION_ALL;
}

int CJNIJsonHandler::CJNIClient::GetAnnouncementFlags()
{
  // Does not support broadcast
  return 0;
}

bool CJNIJsonHandler::CJNIClient::SetAnnouncementFlags(int flags)
{
  return false;
}
