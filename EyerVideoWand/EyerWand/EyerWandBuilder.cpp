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

    int EyerWandBuilder::AddVideoTrack(const EyerVideoTrack & _videoTrack)
    {
        videoTrack = _videoTrack;
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
        VideoTrackProcess(&writer, &encoder, videoStreamIndex);
        // VideoProcess(&writer, &encoder, videoStreamIndex);
        // Audio

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

        Eyer::EyerGLWindow windows("miaowu", width, height);
        windows.Open();
        windows.SetBGColor(1.0, 1.0, 1.0, 1.0);





        EyerGLTexture canvasRenderTarget;
        Eyer::EyerGLFrameBuffer frameBuffer(width, height, &canvasRenderTarget);

        Eyer::EyerGLTextDraw textDraw("./Manjari-Bold.otf");
        textDraw.SetText("Redknot Miaomiao ABC GL gg");
        textDraw.SetColor(0.0, 1.0, 0.0);
        textDraw.SetSize(50);
        textDraw.SetPos(0, 0 + 50);

        frameBuffer.AddComponent(&textDraw);




        EyerGLTexture outRenderTarget;
        Eyer::EyerGLFrameBuffer outFrameBuffer(width, height, &outRenderTarget);

        Eyer::EyerGLSingleTextureDraw canvasDraw;
        canvasDraw.SetTexture(&canvasRenderTarget);

        outFrameBuffer.AddComponent(&canvasDraw);


        for(int frameIndex = 0; frameIndex < frameCount; frameIndex++){
            windows.Clear();

            int msec = (int)(frameIndex * 1.0 / encoder->GetFPS() * 1000);
            textDraw.SetText(Eyer::EyerString::Number(msec / 1000 / 60 / 60, "%02d") + ":" +
                                  Eyer::EyerString::Number(msec / 1000 / 60 % 60, "%02d") + ":" +
                                  Eyer::EyerString::Number(msec / 1000 % 60, "%02d") + ":" +
                                  Eyer::EyerString::Number(msec % 1000, "%03d"));
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

        return 0;
    }

    int EyerWandBuilder::VideoProcess(EyerAVWriter * writer, EyerAVEncoder * encoder, int streamIndex, int debug)
    {
        Eyer::EyerGLWindow windows("WandBuilder", videoWidth, videoHeight);
        windows.Open();
        windows.SetBGColor(1.0, 1.0, 1.0, 1.0);

        Eyer::EyerGLTexture firstRenderTarget;

        Eyer::EyerGLFrameBuffer frameBuffer(videoWidth, videoHeight, &firstRenderTarget);

        Eyer::EyerGLTextDraw titleTextDraw("/home/redknot/Manjari-Bold.otf");
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

        for(int i=0;i<encoder->GetFPS() * 30 * 1;i++){
            windows.Clear();

            frameBuffer.Clear();

            // int msec = (int)(1000 * 1.0 / encoder->GetFPS() * i);
            int msec = (int)(i * 1.0 / encoder->GetFPS() * 1000);

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