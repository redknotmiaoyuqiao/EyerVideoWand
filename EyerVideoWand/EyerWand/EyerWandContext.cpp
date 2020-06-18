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
        videoTrack.SetTargetVideoFPS(fps);
        
        {
            EyerVideoFragmentVideo fragmentVideo1;
            fragmentVideo1.LoadVideoFile("/storage/emulated/0/ST/time_clock_1min_720x1280_30fps.mp4");

            EyerVideoFragmentVideo fragmentVideo2;
            fragmentVideo2.LoadVideoFile("/storage/emulated/0/ST/fashi.mp4");

            EyerVideoFragmentVideo fragmentVideo3;
            fragmentVideo3.LoadVideoFile("/storage/emulated/0/ST/ads.mp4");

            videoTrack.VideoLayer_AddVideoFragment(fragmentVideo3);
            videoTrack.VideoLayer_AddVideoFragment(fragmentVideo1);
            videoTrack.VideoLayer_AddVideoFragment(fragmentVideo2);
            
        }

        /*
        {
            EyerVideoFragmentVideo fragmentVideo;
            fragmentVideo.LoadVideoFile("/storage/emulated/0/ST/time_clock_1min_1280x720_30fps.mp4");
        
            EyerVideoLayer layer;
            layer.SetFrame(200, 800);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }

        {
            EyerVideoFragmentVideo fragmentVideo;
            fragmentVideo.LoadVideoFile("/storage/emulated/0/ST/ads.mp4");
        
            EyerVideoLayer layer;
            layer.SetFrame(800, 1000);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }


        {
            EyerVideoFragmentVideo fragmentVideo;
            fragmentVideo.LoadVideoFile("/storage/emulated/0/ST/fashi.mp4");
        
            EyerVideoLayer layer;
            layer.SetFrame(1000, 2000);
            layer.AddVideoFragment(&fragmentVideo);

            videoTrack.AddLayer(layer);
        }
        */
        
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

    int EyerWandContext::GetVideoTrack(EyerVideoTrack & _videoTrack)
    {
        _videoTrack = videoTrack;
        return 0;
    }
}