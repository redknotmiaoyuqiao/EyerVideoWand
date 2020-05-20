#include "EyerWandContext.hpp"

namespace Eyer
{
    EyerWandContext::EyerWandContext(int w, int h, int _fps)
    {
        width = w;
        height = h;
        fps = _fps;

        videoTrack.SetTargetVideoWH(width, height);

        {
            EyerVideoFragmentVideo fragmentVideo;
            fragmentVideo.LoadVideoFile("/storage/emulated/0/ST/time_clock_1min_720x1280_30fps.mp4");
        
            EyerVideoLayer layer;
            layer.SetFrame(0, 100);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }

        {
            EyerVideoFragmentVideo fragmentVideo;
            fragmentVideo.LoadVideoFile("/storage/emulated/0/ST/time_clock_1min_1280x720_30fps.mp4");
        
            EyerVideoLayer layer;
            layer.SetFrame(101, 200);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }
        
    }

    EyerWandContext::~EyerWandContext()
    {
    }

    int EyerWandContext::SetGLCtx(EyerGLContextThread * _glCtx)
    {
        glCtx = _glCtx;
        return 0;
    }

    int EyerWandContext::RenderFrame(double time)
    {
        if(glCtx != nullptr){
            /*
            Eyer::EyerAVFrame frame;
            int ret = decoderLine->GetFrame(frame, time);
            if(ret){
                EyerLog("GetFrame Fail: %d\n", ret);
            }

            int w = frame.GetWidth();
            int h = frame.GetHeight();

            unsigned char * y = (unsigned char *)malloc(w * h);
            frame.GetYData(y);
            unsigned char * u = (unsigned char *)malloc(w / 2 * h / 2);
            frame.GetUData(u);
            unsigned char * v = (unsigned char *)malloc(w / 2 * h / 2);
            frame.GetVData(v);

            EyerLog("Frame W: %d, H: %d\n", w, h);

            renderTask->SetY(y, w, h);
            renderTask->SetU(u, w / 2, h / 2);
            renderTask->SetV(v, w / 2, h / 2);

            glCtx->AddTaskToRenderQueue(renderTask);

            free(y);
            free(u);
            free(v);
            */
        }
    
        return 0;
    }

    int EyerWandContext::RenderFrameByIndex(int frameIndex)
    {
        return videoTrack.RenderFrame2(frameIndex, fps, glCtx);
    }

    int EyerWandContext::UpdateScreenWH(int _screenW, int _screenH)
    {
        screenW = _screenW;
        screenH = _screenH;
        return 0;
    }
}