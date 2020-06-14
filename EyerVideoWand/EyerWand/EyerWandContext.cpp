#include "EyerWandContext.hpp"
#include "EyerWandAV.hpp"

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
            layer.SetFrame(0, 200);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }

        {
            EyerVideoFragmentVideo fragmentVideo;
            fragmentVideo.LoadVideoFile("/storage/emulated/0/ST/time_clock_1min_1280x720_30fps.mp4");
        
            EyerVideoLayer layer;
            layer.SetFrame(200, 800);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }
        
    }

    EyerWandContext::~EyerWandContext()
    {
    }

    int EyerWandContext::GetFPS()
    {
        return fps;
    }

    int EyerWandContext::SetGLCtx(EyerGLContextThread * _glCtx)
    {
        glCtx = _glCtx;
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

    int EyerWandContext::GetLayerCount()
    {
        return videoTrack.GetLayerCount();
    }

    int EyerWandContext::GetLayer(EyerVideoLayer & layer, int index)
    {
        EyerVideoLayout * l = nullptr;
        videoTrack.GetLayer(l, index);
        if(l == nullptr){
            return -1;
        }

        layer = *l;

        return 0;
    }
}