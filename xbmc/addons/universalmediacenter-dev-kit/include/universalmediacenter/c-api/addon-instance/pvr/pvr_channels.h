/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDONINSTANCE_PVR_CHANNELS_H
#define C_API_ADDONINSTANCE_PVR_CHANNELS_H

#include "pvr_defines.h"

#include <stdbool.h>

//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
// "C" Definitions group 2 - PVR channel
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  //============================================================================
  /// @ingroup cpp_pvr_Defs_Channel
  /// @brief Denotes that no channel uid is available.
  ///
  /// Special @ref addon::PVRTimer::SetClientChannelUid() and
  /// @ref addon::PVRRecording::SetChannelUid() value to indicate that no
  /// channel uid is available.
#define PVR_CHANNEL_INVALID_UID -1
  //----------------------------------------------------------------------------

  /*!
   * @brief "C" PVR add-on channel.
   *
   * Structure used to interface in "C" between Universal Media Center and Addon.
   *
   * See @ref addon::PVRChannel for description of values.
   */
  typedef struct PVR_CHANNEL
  {
    unsigned int iUniqueId;
    bool bIsRadio;
    unsigned int iChannelNumber;
    unsigned int iSubChannelNumber;
    const char* strChannelName;
    const char* strMimeType;
    unsigned int iEncryptionSystem;
    const char* strIconPath;
    bool bIsHidden;
    bool bHasArchive;
    int iOrder;
    int iClientProviderUid;
  } PVR_CHANNEL;

  /*!
   * @brief "C" PVR add-on signal status information.
   *
   * Structure used to interface in "C" between Universal Media Center and Addon.
   *
   * See @ref addon::PVRSignalStatus for description of values.
   */
  typedef struct PVR_SIGNAL_STATUS
  {
    const char* strAdapterName;
    const char* strAdapterStatus;
    const char* strServiceName;
    const char* strProviderName;
    const char* strMuxName;
    int iSNR;
    int iSignal;
    long iBER;
    long iUNC;
  } PVR_SIGNAL_STATUS;

  //============================================================================
  /// @ingroup cpp_pvr_Defs_Channel_PVRDescrambleInfo
  /// @brief Special @ref cpp_pvr_Defs_Channel_PVRDescrambleInfo
  /// value to indicate that a struct member's value is not available
  ///
#define PVR_DESCRAMBLE_INFO_NOT_AVAILABLE -1
  //----------------------------------------------------------------------------

  /*!
   * @brief "C" PVR add-on descramble information.
   *
   * Structure used to interface in "C" between Universal Media Center and Addon.
   *
   * See @ref addon::PVRDescrambleInfo for description of values.
   */
  typedef struct PVR_DESCRAMBLE_INFO
  {
    int iPid;
    int iCaid;
    int iProvid;
    int iEcmTime;
    int iHops;
    const char* strCardSystem;
    const char* strReader;
    const char* strFrom;
    const char* strProtocol;
  } PVR_DESCRAMBLE_INFO;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_PVR_CHANNELS_H */
