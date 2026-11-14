/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "DVDVideoCodec.h"
#include "addons/AddonProvider.h"
#include "addons/binary-addons/AddonInstanceHandler.h"
#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/addon-instance/VideoCodec.h"

class BufferPool;

class CAddonVideoCodec
  : public CDVDVideoCodec
  , public ADDON::IAddonInstanceHandler
{
public:
  CAddonVideoCodec(CProcessInfo& processInfo,
                   ADDON::AddonInfoPtr& addonInfo,
                   UNIVERSALMEDIA_HANDLE parentInstance);
  ~CAddonVideoCodec() override;

  bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options) override;
  bool Reconfigure(CDVDStreamInfo &hints) override;
  bool AddData(const DemuxPacket &packet) override;
  void Reset() override;
  VCReturn GetPicture(VideoPicture* pVideoPicture) override;
  const char* GetName() override;
  void SetCodecControl(int flags) override { m_codecFlags = flags; }

private:
  bool CopyToInitData(VIDEOCODEC_INITDATA &initData, CDVDStreamInfo &hints);

  /*!
   * @brief All picture members can be expected to be set correctly except decodedData and pts.
   * GetFrameBuffer has to set decodedData to a valid memory address and return true.
   * In case buffer allocation fails, return false.
   */
  bool GetFrameBuffer(VIDEOCODEC_PICTURE &picture);
  void ReleaseFrameBuffer(UNIVERSALMEDIA_HANDLE videoBufferHandle);
  bool GetFrameBufferPlatformHandle(UNIVERSALMEDIA_HANDLE videoBufferHandle,
                                    VIDEOCODEC_PLATFORM_BUFFER& platformBuffer);

  static bool get_frame_buffer(void* universalmediacenterInstance, VIDEOCODEC_PICTURE *picture);
  static void release_frame_buffer(void* universalmediacenterInstance, UNIVERSALMEDIA_HANDLE videoBufferHandle);
  static bool get_frame_buffer_platform_handle(void* universalmediacenterInstance,
                                               UNIVERSALMEDIA_HANDLE videoBufferHandle,
                                               VIDEOCODEC_PLATFORM_BUFFER* platformBuffer);

  int m_codecFlags = 0;
  VIDEOCODEC_FORMAT m_formats[VIDEOCODEC_FORMAT_MAXFORMATS + 1];
  float m_displayAspect = 0.0f;
  unsigned int m_width, m_height;
  AVColorSpace m_colorSpace = AVCOL_SPC_UNSPECIFIED;
  AVColorRange m_colorRange = AVCOL_RANGE_UNSPECIFIED;
  AVColorPrimaries m_colorPrimaries = AVCOL_PRI_UNSPECIFIED;
  AVColorTransferCharacteristic m_colorTransfer = AVCOL_TRC_UNSPECIFIED;
  std::shared_ptr<AVMasteringDisplayMetadata> m_masteringMetadata;
  std::shared_ptr<AVContentLightMetadata> m_contentLightMetadata;
  StreamHdrType m_hdrType = StreamHdrType::HDR_TYPE_NONE;

  // Scratch descriptor filled by GetFrameBufferPlatformHandle and pointed at
  // via VIDEOCODEC_PLATFORM_BUFFER::handle. Keeps the addon API free of
  // ffmpeg types (see UNIVERSALMEDIA_DRM_FRAME_DESCRIPTOR in video_codec.h).
  UNIVERSALMEDIA_DRM_FRAME_DESCRIPTOR m_drmFrameDesc{};
};
