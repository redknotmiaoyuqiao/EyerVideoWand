//
// Created by redknot on 2020/1/5.
//

#ifndef EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H
#define EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H

#include <gtest/gtest.h>
#include "EyerVideoProcess/EyerVideoProcess.hpp"

TEST(EyerVideoWand, Video){
    Eyer::EyerAVWriter writer("/home/redknot/Videos/number.mp4");

    writer.Open();

    Eyer::EyerAVEncoder encoder;
    Eyer::EncoderParam param;
    param.codecId = Eyer::CodecId::CODEC_ID_H264;
    param.width = 1920;
    param.height = 1080;
    encoder.Init(&param);

    int streamId = writer.AddStream(&encoder);

    writer.Close();
}

TEST(GenVideo, GenVideo){

}

#endif //EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H
