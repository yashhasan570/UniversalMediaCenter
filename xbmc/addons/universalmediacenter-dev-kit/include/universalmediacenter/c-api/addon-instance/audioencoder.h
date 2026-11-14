/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#ifndef C_API_ADDONINSTANCE_AUDIO_ENCODER_H
#define C_API_ADDONINSTANCE_AUDIO_ENCODER_H

#include "../addon_base.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef UNIVERSALMEDIA_ADDON_INSTANCE_HDL UNIVERSALMEDIA_ADDON_AUDIOENCODER_HDL;

  struct UNIVERSALMEDIA_ADDON_AUDIOENCODER_INFO_TAG
  {
    const char* title;
    const char* artist;
    const char* album;
    const char* album_artist;
    const char* media_type;
    const char* genre;
    int duration;
    int track;
    int disc;
    const char* disc_subtitle;
    int disc_total;
    const char* release_date;
    const char* lyrics;
    int samplerate;
    int channels;
    int bits_per_sample;
    int track_length;
    const char* comment;
  };

  typedef bool(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_AUDIOENCODER_START_V1)(
      UNIVERSALMEDIA_ADDON_AUDIOENCODER_HDL hdl, const struct UNIVERSALMEDIA_ADDON_AUDIOENCODER_INFO_TAG* tag);
  typedef ssize_t(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_AUDIOENCODER_ENCODE_V1)(
      UNIVERSALMEDIA_ADDON_AUDIOENCODER_HDL hdl, const uint8_t* pbt_stream, size_t num_bytes_read);
  typedef bool(ATTR_APIENTRYP PFN_UNIVERSALMEDIA_ADDON_AUDIOENCODER_FINISH_V1)(
      UNIVERSALMEDIA_ADDON_AUDIOENCODER_HDL hdl);

  typedef struct AddonToUniversal Media CenterFuncTable_AudioEncoder
  {
    UNIVERSALMEDIA_HANDLE universalmediacenterInstance;
    ssize_t (*write)(UNIVERSALMEDIA_HANDLE universalmediacenterInstance, const uint8_t* data, size_t len);
    ssize_t (*seek)(UNIVERSALMEDIA_HANDLE universalmediacenterInstance, ssize_t pos, int whence);
  } AddonToUniversal Media CenterFuncTable_AudioEncoder;

  typedef struct Universal Media CenterToAddonFuncTable_AudioEncoder
  {
    PFN_UNIVERSALMEDIA_ADDON_AUDIOENCODER_START_V1 start;
    PFN_UNIVERSALMEDIA_ADDON_AUDIOENCODER_ENCODE_V1 encode;
    PFN_UNIVERSALMEDIA_ADDON_AUDIOENCODER_FINISH_V1 finish;
  } Universal Media CenterToAddonFuncTable_AudioEncoder;

  typedef struct AddonInstance_AudioEncoder
  {
    struct AddonToUniversal Media CenterFuncTable_AudioEncoder* toUniversal Media Center;
    struct Universal Media CenterToAddonFuncTable_AudioEncoder* toAddon;
  } AddonInstance_AudioEncoder;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_AUDIO_ENCODER_H */
