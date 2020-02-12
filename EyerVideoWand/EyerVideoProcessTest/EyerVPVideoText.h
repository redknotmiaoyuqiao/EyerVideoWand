//
// Created by redknot on 2020/1/5.
//

#ifndef EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H
#define EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H

#include <gtest/gtest.h>
#include "EyerVideoProcess/EyerVideoProcess.hpp"

#include "EyerGL/EyerGL.hpp"
#include "EyerYUV/EyerYUV.hpp"

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
    int width = 1280;
    int height = 720;

    Eyer::EyerAVWriter writer("/home/redknot/Videos/number_time.mp4");
    writer.Open();

    Eyer::EyerAVEncoder encoder;
    Eyer::EncoderParam param;
    param.codecId = Eyer::CodecId::CODEC_ID_H264;
    param.width = width;
    param.height = height;
    encoder.Init(&param);

    writer.WriteHand();

    int streamId = writer.AddStream(&encoder);


    Eyer::EyerGLWindow windows("GL Canvas", width, height);
    windows.Open();
    windows.SetBGColor(1.0, 1.0, 1.0, 1.0);


    Eyer::EyerGLFrameBuffer frameBuffer;

    Eyer::EyerGLTextDraw textDraw;
    // textDraw.SetText("abcdefghijklmnopqrstuvwxyz");
    textDraw.SetText("Redknot Miaomiao ABC GL gg");
    textDraw.SetColor(0.0, 1.0, 0.0);
    textDraw.SetSize(100);

    textDraw.SetPos(width / 2, height / 2);

    frameBuffer.AddComponent(&textDraw);

    // FILE * yuvFile = fopen("/home/redknot/yuvFile.yuv", "wb");

    for(int i=0;i<25 * 60;i++){
        // EyerLog("Frame Id:%d\n", i);

        windows.Clear();

        Eyer::EyerString timeStr = Eyer::EyerString::Number(i / 25) + "~~~" + Eyer::EyerString::Number(i % 25);
        textDraw.SetText(timeStr);
        textDraw.SetColor(1.0, 0.0, 0.0);
        textDraw.Viewport(width, height);
        frameBuffer.Draw();

        unsigned char * rgbData = (unsigned char * )malloc(width * height * 3);
        frameBuffer.ReadPixel(0, 0, width, height, rgbData);

        unsigned char * y = (unsigned char *)malloc(width * height);
        unsigned char * u = (unsigned char *)malloc(width * height / 4);
        unsigned char * v = (unsigned char *)malloc(width * height / 4);

        Eyer::EyerYUV yuvCon;
        yuvCon.RGB2YUV420(width, height, rgbData, y, u, v);

        Eyer::EyerAVFrame frame;
        frame.SetVideoData420P(y, u, v, width, height);

        int ret = encoder.SendFrame(&frame);
        if(!ret){
            while(1){
                Eyer::EyerAVPacket pkt;
                ret = encoder.RecvPacket(&pkt);
                if(ret){
                    break;
                }

                pkt.SetStreamId(streamId);
                writer.WritePacket(&pkt);
            }
        }
        encoder.SendFrame(NULL);



        /*
        fwrite(y, 1, width * height, yuvFile);
        fwrite(u, 1, width * height / 4, yuvFile);
        fwrite(v, 1, width * height / 4, yuvFile);
        */

        free(y);
        free(u);
        free(v);

        free(rgbData);

        windows.Loop();
    }


    writer.Close();
    // fclose(yuvFile);


    windows.Close();

    writer.Close();
}

#endif //EYE_VIDEO_WAND_EYERVPVIDEOTEXT_H
