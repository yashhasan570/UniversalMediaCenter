/*
 *  Copyright (C) 2025 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/addon-instance/pvr/pvr_general.h" // PVR_SETTING_TYPE
#include "utils/Variant.h"

#include <map>

namespace PVR
{
/*!
 * @brief custom property : type, value
 */
struct CustomProperty
{
  PVR_SETTING_TYPE type{PVR_SETTING_TYPE::INTEGER};
  CVariant value{int{0}};

  CustomProperty() = default;
  CustomProperty(PVR_SETTING_TYPE t, const CVariant& v) : type(t), value(v) {}
  bool operator==(const CustomProperty& right) const = default;
};

/*!
 * @brief custom properties map: property id, details
 */
using CustomPropertiesMap = std::map<unsigned int, CustomProperty>;

} // namespace PVR
