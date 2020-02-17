#include <EyerGL/EyerGL.hpp>
#include "EyerWand.hpp"

#include "EyerAV/EyerAV.hpp"
#include "EyerYUV/EyerYUV.hpp"

namespace Eyer
{
    EyerWandBuilder::EyerWandBuilder(EyerString _path)
    {
        path = _path;
    }

    EyerWandBuilder::~EyerWandBuilder()
    {

    }

    int EyerWandBuilder::SetVideoWH(int w, int h)
    {
        videoWidth = w;
        videoHeight = h;
        return 0;
    }

    int EyerWandBuilder::SetVideoFPS(int fps)
    {
        videoFps = fps;
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

        writer.WriteHand();

        // Video
        VideoProcess(&writer, &encoder, videoStreamIndex, 1);
        // Audio

        writer.Close();

        return 0;
    }

    int EyerWandBuilder::VideoProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug)
    {
        Eyer::EyerGLWindow windows("WandBuilder", videoWidth, videoHeight);
        windows.Open();
        windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

        Eyer::EyerGLTexture firstRenderTarget;

        Eyer::EyerGLFrameBuffer frameBuffer(videoWidth, videoHeight, &firstRenderTarget);

        Eyer::EyerGLTextDraw titleTextDraw;
        titleTextDraw.SetText("Redknot Miaomiao ABC GL gg");
        titleTextDraw.SetColor(0.0, 1.0, 0.0);
        titleTextDraw.SetSize(50);
        titleTextDraw.SetPos(0, 50);

        frameBuffer.AddComponent(&titleTextDraw);


        Eyer::EyerGLTexture canvasRenderTarget;
        Eyer::EyerGLFrameBuffer canvasFrameBuffer(videoWidth, videoHeight, &canvasRenderTarget);

        Eyer::EyerGLSingleTextureDraw canvasDraw;
        canvasDraw.SetTexture(&firstRenderTarget);

        canvasFrameBuffer.AddComponent(&canvasDraw);

        int msec = 0;
        for(int i=0;i<encoder->GetFPS() * 60 * 1;i++){
            windows.Clear();

            frameBuffer.Clear();

            if(debug) {
                titleTextDraw.SetText(Eyer::EyerString::Number(msec / 1000 / 60 / 60, "%02d") + ":" +
                                      Eyer::EyerString::Number(msec / 1000 / 60 % 60, "%02d") + ":" +
                                      Eyer::EyerString::Number(msec / 1000 % 60, "%02d") + ":" +
                                      Eyer::EyerString::Number(msec % 1000, "%03d"));
            }
            else{
                titleTextDraw.SetText("");
            }
            titleTextDraw.SetColor(1.0, 0.0, 0.0);
            titleTextDraw.Viewport(videoWidth, videoHeight);
            frameBuffer.Draw();

            msec += 40;

            canvasFrameBuffer.Draw();

            unsigned char * rgbData = (unsigned char * )malloc(videoWidth * videoHeight * 3);
            canvasFrameBuffer.ReadPixel(0, 0, videoWidth, videoHeight, rgbData);

            unsigned char * y = (unsigned char *)malloc(videoWidth * videoHeight);
            unsigned char * u = (unsigned char *)malloc(videoWidth * videoHeight / 4);
            unsigned char * v = (unsigned char *)malloc(videoWidth * videoHeight / 4);

            Eyer::EyerYUV yuvCon;
            yuvCon.RGB2YUV420(videoWidth, videoHeight, rgbData, y, u, v);

            Eyer::EyerAVFrame frame;
            frame.SetPTS(i);
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

        return 0;
    }
}