#ifndef	EYER_LIB_AV_AUDIO_TRACK_H
#define	EYER_LIB_AV_AUDIO_TRACK_H

#include <gtest/gtest.h>
#include "EyerVideoProcess/EyerVideoProcess.hpp"

TEST(EyerVideoWand, EyerVPAudioTrack_Base){
    Eyer::EyerVPAudioTrack audioTrack;
    {
        Eyer::EyerVPAudioRes audioRes;
        audioRes.SetPath("/Users/yuqiaomiao/Video/A/1403_20_4434.aac");
        audioTrack.AddAudioRes(audioRes);
    }
    {
        Eyer::EyerVPAudioRes audioRes;
        audioRes.SetPath("/Users/yuqiaomiao/Video/A/1403_20_4433.aac");
        audioTrack.AddAudioRes(audioRes);
    }

    double duration = audioTrack.GetDuration();
    printf("Duration:%f\n", duration);
}

#endif
