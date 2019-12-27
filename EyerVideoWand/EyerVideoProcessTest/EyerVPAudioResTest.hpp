#ifndef	EYER_LIB_AV_AUDIO_RES_H
#define	EYER_LIB_AV_AUDIO_RES_H

#include <gtest/gtest.h>
#include "EyerVideoProcess/EyerVideoProcess.hpp"

TEST(EyerVideoWand, EyerVPAudioRes_Base){
    Eyer::EyerString pathRes = "/Users/yuqiaomiao/Video/1280_720.mp4";

    for(int i=-1000;i<1000;i++){
        Eyer::EyerVPAudioRes audioRes;
        audioRes.SetPath(pathRes);
        audioRes.SetStream(i);
        audioRes.SetPosition(i);
        audioRes.SetCutter(i, i + 1000);

        ASSERT_GE(audioRes.GetStreamIndex(), 0);
        ASSERT_GE(audioRes.GetPosition(), 0);
        ASSERT_GE(audioRes.GetCutterStartTime(), 0);
        ASSERT_GE(audioRes.GetCutterEndTime(), audioRes.GetCutterStartTime());

        // 测试拷贝构造方法
        Eyer::EyerVPAudioRes a = audioRes;
        ASSERT_TRUE(a.GetRes() == audioRes.GetRes()) << "Path Error";
        ASSERT_EQ(a.GetStreamIndex(), audioRes.GetStreamIndex()) << "Stream Index Error";
        ASSERT_EQ(a.GetPosition(), audioRes.GetPosition()) << "Position Error";
        ASSERT_EQ(a.GetCutterStartTime(), audioRes.GetCutterStartTime()) << "Cutter Start Time Error";
        ASSERT_EQ(a.GetCutterEndTime(), audioRes.GetCutterEndTime()) << "Cutter End Time Error";

        // 测试赋值运算符
        Eyer::EyerVPAudioRes b;
        b = audioRes;
        ASSERT_TRUE(b.GetRes() == audioRes.GetRes()) << "Path Error";
        ASSERT_EQ(b.GetStreamIndex(), audioRes.GetStreamIndex()) << "Stream Index Error";
        ASSERT_EQ(b.GetPosition(), audioRes.GetPosition()) << "Position Error";
        ASSERT_EQ(b.GetCutterStartTime(), audioRes.GetCutterStartTime()) << "Cutter Start Time Error";
        ASSERT_EQ(b.GetCutterEndTime(), audioRes.GetCutterEndTime()) << "Cutter End Time Error";
    }
}

#endif
