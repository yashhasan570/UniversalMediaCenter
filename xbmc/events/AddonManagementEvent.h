/*
 *  Copyright (C) 2015-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "events/AddonEvent.h"

class CAddonManagementEvent : public CAddonEvent
{
public:
  CAddonManagementEvent(const ADDON::AddonPtr& addon, const CVariant& description);
  CAddonManagementEvent(const ADDON::AddonPtr& addon,
                        const CVariant& description,
                        const CVariant& details);
  CAddonManagementEvent(const ADDON::AddonPtr& addon,
                        const CVariant& description,
                        const CVariant& details,
                        const CVariant& executionLabel);
  CAddonManagementEvent(const ADDON::AddonPtr& addon,
                        EventLevel level,
                        const CVariant& description);
  CAddonManagementEvent(const ADDON::AddonPtr& addon,
                        EventLevel level,
                        const CVariant& description,
                        const CVariant& details);
  CAddonManagementEvent(const ADDON::AddonPtr& addon,
                        EventLevel level,
                        const CVariant& description,
                        const CVariant& details,
                        const CVariant& executionLabel);
  ~CAddonManagementEvent() override = default;

  const char* GetType() const override { return "AddonManagementEvent"; }
  std::string GetExecutionLabel() const override;

  bool CanExecute() const override { return m_addon != NULL; }
  bool Execute() const override;
};
