/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "Mmap.h"

#include <system_error>

using namespace UNIVERSAL MEDIA CENTER::UTILS::POSIX;

CMmap::CMmap(void* addr, std::size_t length, int prot, int flags, int fildes, off_t offset)
: m_size{length}, m_memory{mmap(addr, length, prot, flags, fildes, offset)}
{
  if (m_memory == MAP_FAILED)
  {
    throw std::system_error(errno, std::generic_category(), "mmap failed");
  }
}

CMmap::~CMmap()
{
  munmap(m_memory, m_size);
}