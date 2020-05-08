#include <EyerGL/EyerGL.hpp>
#include <math.h>

#include "EyerWand.hpp"
#include "EyerAV/EyerAV.hpp"
#include "EyerYUV/EyerYUV.hpp"

namespace Eyer
{
    EyerWandBuilder::EyerWandBuilder(EyerString _path)
    {
        path = _path;
        EyerLog("EyerWandBuilder Init, Path: %s\n", path.str);
    }

    EyerWandBuilder::~EyerWandBuilder()
    {

    }
    
    int EyerWandBuilder::SetVideoWH(int w, int h)
    {
        videoWidth = w;
        videoHeight = h;
        EyerLog("EyerWandBuilder Init, W: %d, H:%d\n", videoWidth, videoHeight);
        return 0;
    }

    int EyerWandBuilder::SetVideoFPS(int fps)
    {
        videoFps = fps;
        EyerLog("EyerWandBuilder Init, FPS: %d\n", videoFps);
        return 0;
    }

    int EyerWandBuilder::AddVideoTrack(const EyerVideoTrack & _videoTrack)
    {
        videoTrack = _videoTrack;
        return 0;
    }

    int EyerWandBuilder::AddAudioTrack(const EyerAudioTrack & _audioTrack)
    {
        audioTrack = _audioTrack;
        return 0;
    }

    int EyerWandBuilder::Process()
    {
        Eyer::EyerAVWriter writer(path);
        writer.Open();

        // AddVideoStream
        Eyer::EyerAVEncoder encoder;
        Eyer::EncoderParam encoderParam;
        encoderParam.width = videoWidth;
        encoderParam.height = videoHeight;
        encoderParam.fps = videoFps;
        encoderParam.codecId = Eyer::CodecId::CODEC_ID_H264;
        encoder.Init(&encoderParam);

        int videoStreamIndex = writer.AddStream(&encoder);

        // AddAudioStream
        Eyer::EyerAVEncoder audioEncoder;
        EncoderParam audioEncoderParam;
        audioEncoderParam.codecId = CodecId::CODEC_ID_AAC;
        audioEncoder.Init(&audioEncoderParam);

        int audioStreamIndex = writer.AddStream(&audioEncoder);

        writer.WriteHand();

        // Video
        VideoTrackProcess(&writer, &encoder, videoStreamIndex);

        // Audio
        AudioTrackProcess(&writer, &audioEncoder, audioStreamIndex);

        writer.Close();

        return 0;
    }

    int EyerWandBuilder::VideoTrackProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug)
    {
        // 获取 VideoTrack
        // 从layout中获取总帧数
        int frameCount = videoTrack.GetFrameCount();
        EyerLog("Frame Count: %d\n", frameCount);

        int width = videoWidth;
        int height = videoHeight;

        Eyer::EyerGLWindow windows("Eyer Wand", width, height);
        windows.Open();
        // windows.SetBGColor(1.0, 1.0, 1.0, 1.0);
        windows.SetBGColor(0.0, 0.0, 0.0, 1.0);


        Eyer::EyerGLFrameBuffer windowsFrameBuffer(width, height);
        // Eyer::EyerGLTextDraw textProgressDraw("./han_yi_xing_kai_jian.ttf");
        Eyer::EyerGLTextDraw textProgressDraw("./xiao_xiao_yuan_pin_ying.ttf");
        textProgressDraw.SetText("Redknot Miaomiao ABC GL gg");
        textProgressDraw.SetColor(0.0, 0.0, 0.0);
        textProgressDraw.SetSize(50);
        textProgressDraw.SetPos(0, height / 2);


        EyerGLTexture canvasRenderTarget;
        Eyer::EyerGLFrameBuffer frameBuffer(width, height, &canvasRenderTarget);

        Eyer::EyerGLTextDraw textDraw("./xiao_xiao_yuan_pin_ying.ttf");
        textDraw.SetText("Redknot Miaomiao ABC GL gg");
        textDraw.SetColor(0.0, 1.0, 0.0);
        textDraw.SetSize(50);
        textDraw.SetPos(0, 0 + 50);

        textDraw.SetSize(height / 5.0);
    
        textDraw.SetColor(1.0, 1.0, 1.0);

        textDraw.SetText("00:00:00:000");
        int textWidth = textDraw.GetTextWidth();
        textDraw.SetPos(width / 2.0 - textWidth / 2.0, height / 2.0);
        // textDraw.SetPos(width / 4.0, height / 2.0);


        frameBuffer.AddComponent(&textDraw);



        EyerGLTexture outRenderTarget;
        Eyer::EyerGLFrameBuffer outFrameBuffer(width, height, &outRenderTarget);

        Eyer::EyerGLSingleTextureDraw canvasDraw;
        canvasDraw.SetTexture(&canvasRenderTarget);

        outFrameBuffer.AddComponent(&canvasDraw);

        for(int frameIndex = 0; frameIndex < frameCount; frameIndex++){
            printf("Now Frame Id: %d / %d\n", frameIndex, frameCount);


            windows.Clear();

            textProgressDraw.SetColor(1.0, 1.0, 1.0);
            textProgressDraw.SetText(EyerString("Eyer Wand 正 在 生 成 视 频 ： ") + EyerString::Number((int)(frameIndex * 1.0 / frameCount * 100)) + " %");
            int progressWidth = textProgressDraw.GetTextWidth();
            textProgressDraw.SetPos((width - progressWidth) / 2, height / 2);

            windowsFrameBuffer.Clear();
            windowsFrameBuffer.AddComponent(&textProgressDraw);
            windowsFrameBuffer.Draw();
            windowsFrameBuffer.ClearAllComponent();


            int msec = (int)(frameIndex * 1.0 / encoder->GetFPS() * 1000);

           /* textDraw.SetText(Eyer::EyerString("Eyer Wand 基情支持") + Eyer::EyerString::Number(msec / 1000 / 60 / 60, "%02d") + ":" +
                                  Eyer::EyerString::Number(msec / 1000 / 60 % 60, "%02d") + ":" +
                                  Eyer::EyerString::Number(msec / 1000 % 60, "%02d") + ":" +
                                  Eyer::EyerString::Number(msec % 1000, "%03d"));*/
            textDraw.SetText("");
            textDraw.SetPos(0, 0 + 50);
            textDraw.SetColor(1.0, 0.0, 0.0);
            textDraw.Viewport(width, height);


            EyerVideoTrackRenderParams params;
            params.videoW = width;
            params.videoH = height;
            params.frameBuffer = &frameBuffer;
            params.titleTextDraw = &textDraw;

            videoTrack.RenderFrame(frameIndex, &params, videoFps);

            outFrameBuffer.Draw();

            unsigned char * rgbData = (unsigned char * )malloc(videoWidth * videoHeight * 3);
            outFrameBuffer.ReadPixel(0, 0, videoWidth, videoHeight, rgbData);

            unsigned char * y = (unsigned char *)malloc(videoWidth * videoHeight);
            unsigned char * u = (unsigned char *)malloc(videoWidth * videoHeight / 4);
            unsigned char * v = (unsigned char *)malloc(videoWidth * videoHeight / 4);

            Eyer::EyerYUV yuvCon;
            yuvCon.RGB2YUV420(videoWidth, videoHeight, rgbData, y, u, v);

            Eyer::EyerAVFrame frame;
            frame.SetPTS(frameIndex);
            frame.SetVideoData420P(y, u, v, videoWidth, videoHeight);

            encoder->SendFrame(&frame);
            while(1){
                Eyer::EyerAVPacket pkt;
                int ret = encoder->RecvPacket(&pkt);
                if(ret){
                    break;
                }

                Eyer::EyerAVRational encoderTimebase;
                encoder->GetTimeBase(encoderTimebase);

                Eyer::EyerAVRational streamTimebase;
                writer->GetStreamTimeBase(streamTimebase, streamIndex);

                pkt.RescaleTs(encoderTimebase, streamTimebase);

                pkt.SetStreamId(streamIndex);
                writer->WritePacket(&pkt);
            }

            free(y);
            free(u);
            free(v);

            free(rgbData);

            windows.Loop();
        }

        encoder->SendFrame(nullptr);
        while(1){
            Eyer::EyerAVPacket pkt;
            int ret = encoder->RecvPacket(&pkt);
            if(ret){
                break;
            }

            Eyer::EyerAVRational encoderTimebase;
            encoder->GetTimeBase(encoderTimebase);

            Eyer::EyerAVRational streamTimebase;
            writer->GetStreamTimeBase(streamTimebase, streamIndex);

            pkt.RescaleTs(encoderTimebase, streamTimebase);

            pkt.SetStreamId(streamIndex);
            writer->WritePacket(&pkt);
        }

        windows.Close();

#ifdef EYER_DEBUG
        EyerLog("Decode Time Count : %lld\n", EyerWandDebug::DecoderTime);
#endif

        return 0;
    }

    int EyerWandBuilder::VideoProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug)
    {
        return 0;
    }

    int EyerWandBuilder::AudioTrackProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug)
    {
        // 记录当前写入的长度
        double wirteTime = 0.0;
        while(1){
            int bufferSize = encoder->GetBufferSize();
            int sampSize = bufferSize / 4 / 2;
            double dTime = sampSize * 1.0 / 44100;

            Eyer::EyerAVFrame avFrame;
            avFrame.InitAACFrame(6);

            audioTrack.RenderFrame(wirteTime, avFrame);

            encoder->SendFrame(&avFrame);
            while(1){
                Eyer::EyerAVPacket pkt;
                int ret = encoder->RecvPacket(&pkt);
                if(ret){
                    break;
                }

                Eyer::EyerAVRational encoderTimebase;
                encoder->GetTimeBase(encoderTimebase);

                Eyer::EyerAVRational streamTimebase;
                writer->GetStreamTimeBase(streamTimebase, streamIndex);

                pkt.RescaleTs(encoderTimebase, streamTimebase);

                pkt.SetStreamId(streamIndex);
                writer->WritePacket(&pkt);

                wirteTime += dTime;
            }
            // EyerLog("Time: %f\n", wirteTime);

            if(wirteTime >= audioTrack.GetCountTime()){
                break;
            }
        }

        encoder->SendFrame(nullptr);
        while(1){
            Eyer::EyerAVPacket pkt;
            int ret = encoder->RecvPacket(&pkt);
            if(ret){
                break;
            }

            Eyer::EyerAVRational encoderTimebase;
            encoder->GetTimeBase(encoderTimebase);

            Eyer::EyerAVRational streamTimebase;
            writer->GetStreamTimeBase(streamTimebase, streamIndex);

            pkt.RescaleTs(encoderTimebase, streamTimebase);

            pkt.SetStreamId(streamIndex);
            writer->WritePacket(&pkt);
        }

        return 0;
    }
}