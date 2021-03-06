/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_VOICE_ENGINE_VOE_STANDARD_TEST_H
#define WEBRTC_VOICE_ENGINE_VOE_STANDARD_TEST_H

#include <stdio.h>
#include <string>

#include "gflags/gflags.h"
#include "resource_manager.h"
#include "voe_audio_processing.h"
#include "voe_base.h"
#include "voe_dtmf.h"
#include "voe_errors.h"
#include "voe_file.h"
#include "voe_rtp_rtcp.h"
#include "voe_test_defines.h"
#include "voe_test_interface.h"
#ifdef WEBRTC_VOICE_ENGINE_CALL_REPORT_API
#include "voe_call_report.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_CODEC_API
#include "voe_codec.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_ENCRYPTION_API
#include "voe_encryption.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_EXTERNAL_MEDIA_API
#include "voe_external_media.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_HARDWARE_API
#include "voe_hardware.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_NETWORK_API
#include "voe_network.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_VIDEO_SYNC_API
#include "voe_video_sync.h"
#endif
#ifdef WEBRTC_VOICE_ENGINE_VOLUME_CONTROL_API
#include "voe_volume_control.h"
#endif

#ifdef _TEST_NETEQ_STATS_
namespace webrtc {
class CriticalSectionWrapper;
class ThreadWrapper;
class VoENetEqStats;
}
#endif

#if defined(WEBRTC_ANDROID)
extern char mobileLogMsg[640];
#endif

DECLARE_bool(include_timing_dependent_tests);

namespace voetest {

class SubAPIManager {
 public:
  SubAPIManager()
    : _base(true),
      _callReport(false),
      _codec(false),
      _dtmf(false),
      _encryption(false),
      _externalMedia(false),
      _file(false),
      _hardware(false),
      _netEqStats(false),
      _network(false),
      _rtp_rtcp(false),
      _videoSync(false),
      _volumeControl(false),
      _apm(false),
      _xsel(XSEL_Invalid) {
#ifdef WEBRTC_VOICE_ENGINE_CALL_REPORT_API
      _callReport = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_CODEC_API
      _codec = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_DTMF_API
      _dtmf = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_ENCRYPTION_API
      _encryption = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_EXTERNAL_MEDIA_API
      _externalMedia = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_FILE_API
      _file = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_HARDWARE_API
      _hardware = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_NETEQ_STATS_API
      _netEqStats = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_NETWORK_API
      _network = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_RTP_RTCP_API
      _rtp_rtcp = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_VIDEO_SYNC_API
      _videoSync = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_VOLUME_CONTROL_API
      _volumeControl = true;
#endif
#ifdef WEBRTC_VOICE_ENGINE_AUDIO_PROCESSING_API
      _apm = true;
#endif
  }

  void DisplayStatus() const;
  bool GetExtendedMenuSelection(ExtendedSelection& sel);

 private:
  bool _base, _callReport, _codec, _dtmf, _encryption;
  bool _externalMedia, _file, _hardware;
  bool _netEqStats, _network, _rtp_rtcp, _videoSync, _volumeControl, _apm;
  ExtendedSelection _xsel;
};

class VoETestManager {
 public:
  VoETestManager();
  ~VoETestManager();

  // Must be called after construction.
  bool Init();

  void GetInterfaces();
  int ReleaseInterfaces();

  const char* AudioFilename() const {
    const std::string& result = resource_manager_.long_audio_file_path();
    if (result.length() == 0) {
      TEST_LOG("ERROR: Failed to open input file!");
    }
    return result.c_str();
  }

  VoiceEngine* VoiceEnginePtr() const {
    return voice_engine_;
  }
  VoEBase* BasePtr() const {
    return voe_base_;
  }
  VoECodec* CodecPtr() const {
    return voe_codec_;
  }
  VoEVolumeControl* VolumeControlPtr() const {
    return voe_volume_control_;
  }
  VoEDtmf* DtmfPtr() const {
    return voe_dtmf_;
  }
  VoERTP_RTCP* RTP_RTCPPtr() const {
    return voe_rtp_rtcp_;
  }
  VoEAudioProcessing* APMPtr() const {
    return voe_apm_;
  }

  VoENetwork* NetworkPtr() const {
    return voe_network_;
  }

  VoEFile* FilePtr() const {
    return voe_file_;
  }

  VoEHardware* HardwarePtr() const {
    return voe_hardware_;
  }

  VoEVideoSync* VideoSyncPtr() const {
    return voe_vsync_;
  }

  VoEEncryption* EncryptionPtr() const {
    return voe_encrypt_;
  }

  VoEExternalMedia* ExternalMediaPtr() const {
    return voe_xmedia_;
  }

  VoECallReport* CallReportPtr() const {
    return voe_call_report_;
  }

#ifdef _TEST_NETEQ_STATS_
  VoENetEqStats* NetEqStatsPtr() const {
    return voe_neteq_stats_;
  }

#endif

 private:
  bool                   initialized_;

  VoiceEngine*           voice_engine_;
  VoEBase*               voe_base_;
  VoECallReport*         voe_call_report_;
  VoECodec*              voe_codec_;
  VoEDtmf*               voe_dtmf_;
  VoEEncryption*         voe_encrypt_;
  VoEExternalMedia*      voe_xmedia_;
  VoEFile*               voe_file_;
  VoEHardware*           voe_hardware_;
  VoENetwork*            voe_network_;
#ifdef _TEST_NETEQ_STATS_
  VoENetEqStats*         voe_neteq_stats_;
#endif
  VoERTP_RTCP*           voe_rtp_rtcp_;
  VoEVideoSync*          voe_vsync_;
  VoEVolumeControl*      voe_volume_control_;
  VoEAudioProcessing*    voe_apm_;

  ResourceManager        resource_manager_;
};

} // namespace voetest

#endif // WEBRTC_VOICE_ENGINE_VOE_STANDARD_TEST_H
