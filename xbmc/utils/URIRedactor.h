/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <string>
#include <string_view>

class CURL;

/*! \brief Universal Media Center credential removal and bounded inline-data redaction, including wrappers. */
class CURIRedactor final
{
public:
  static std::string GetRedacted(std::string_view path);
  static std::string GetWithoutUserDetails(const CURL& url, bool redact);

private:
  static std::string GetWithoutUserDetails(const CURL& url, bool redact, bool& credentialsRemoved);
};
