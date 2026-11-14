/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>
#include <utility>

#include <windows.h>

class win32_exception
{
public:
    typedef const void* Address; // OK on Win32 platform

    static void set_version(std::string version) { mVersion = std::move(version); }
    static void set_platformDirectories(const std::string& platformDir)
    {
      m_platformDir = platformDir;
    }
    static bool write_minidump(EXCEPTION_POINTERS* pEp);
    static bool write_stacktrace(EXCEPTION_POINTERS* pEp);
    static bool ShouldHook();
private:
    static std::string mVersion;
    static std::string m_platformDir;
};
