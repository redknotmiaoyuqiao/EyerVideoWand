#ifndef	EYER_LIB_AV_AUDIO_TRACK_H
#define	EYER_LIB_AV_AUDIO_TRACK_H

#include <gtest/gtest.h>
#include "EyerVideoProcess/EyerVideoProcess.hpp"

TEST(EyerVideoWand, EyerVPAudioTrack_Base){
    Eyer::EyerVPAudioTrack audioTrack;
    {
        Eyer::EyerVPAudioRes audioRes;
        audioRes.SetPath("/home/redknot/Videos/A/1403_20_4431.aac");
        // audioRes.SetPosition(5.0);
        audioTrack.AddAudioRes(audioRes);
    }
    
    double duration = audioTrack.GetDuration();
    printf("Duration:%f\n", duration);

    audioTrack.RenderToFile("/home/redknot/Videos/A/outout.aac");
}

#endif
