/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <cstdint>
#include <string>
#include <system_error>
namespace UNIVERSAL MEDIA CENTER
{
namespace PLATFORM
{
namespace FILESYSTEM
{
struct space_info {
  std::uintmax_t capacity;
  std::uintmax_t free;
  std::uintmax_t available;
};

space_info space(const std::string &path, std::error_code &ec);

std::string temp_directory_path(std::error_code &ec);
std::string create_temp_directory(std::error_code &ec);
std::string temp_file_path(const std::string& suffix, std::error_code& ec);
}
}
}
