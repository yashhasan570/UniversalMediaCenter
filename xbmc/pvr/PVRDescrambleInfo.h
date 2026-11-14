/*
 *  Copyright (C) 2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/c-api/addon-instance/pvr/pvr_channels.h"

#include <string>

namespace PVR
{

class CPVRDescrambleInfo
{
public:
  CPVRDescrambleInfo()
  {
    m_info.iPid = PVR_DESCRAMBLE_INFO_NOT_AVAILABLE;
    m_info.iCaid = PVR_DESCRAMBLE_INFO_NOT_AVAILABLE;
    m_info.iProvid = PVR_DESCRAMBLE_INFO_NOT_AVAILABLE;
    m_info.iEcmTime = PVR_DESCRAMBLE_INFO_NOT_AVAILABLE;
    m_info.iHops = PVR_DESCRAMBLE_INFO_NOT_AVAILABLE;
  }

  explicit CPVRDescrambleInfo(const PVR_DESCRAMBLE_INFO& info)
    : m_info(info),
      m_cardSystem(info.strCardSystem ? info.strCardSystem : ""),
      m_reader(info.strReader ? info.strReader : ""),
      m_from(info.strFrom ? info.strFrom : ""),
      m_protocol(info.strProtocol ? info.strProtocol : "")
  {
  }

  virtual ~CPVRDescrambleInfo() = default;

  //! @todo add other getters (currently not used).
  int Caid() const { return m_info.iCaid; }

private:
  PVR_DESCRAMBLE_INFO m_info{};
  std::string m_cardSystem;
  std::string m_reader;
  std::string m_from;
  std::string m_protocol;
};

} // namespace PVR
