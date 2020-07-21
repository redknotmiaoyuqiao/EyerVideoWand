#ifndef	EYER_LIB_AV_WAND_RENDER_TASK_H
#define	EYER_LIB_AV_WAND_RENDER_TASK_H

#include "EyerGLRenderTask/EyerGLRenderTask.hpp"
#include "EyerWand/EyerWandAV.hpp"

namespace Eyer {
    class LayerRenderTask : public EyerGLRenderTask
    {
    public:
        LayerRenderTask(EyerVideoLayer * layer, int frameIndex, int fps);
        ~LayerRenderTask();

        int SetScreenWH(int w, int h);
        int SetVideoWH(int w, int h);

        virtual int Render();
        virtual int Init();
        virtual int Destory();

    private:
        EyerVideoLayer * layer = nullptr;

        int screenW = 0;
        int screenH = 0;

        int videoW = 0;
        int videoH = 0;

        int frameIndex = 0;
        int fps = 0;
    };

    class VideoTrackRenderTask : public EyerGLRenderTask
    {
    public:
        VideoTrackRenderTask(EyerVideoTrack * videoTrack, int frameIndex, int fps);
        ~VideoTrackRenderTask();

        int SetScreenWH(int w, int h);

        virtual int Render();
        virtual int Init();
        virtual int Destory();

    private:
        EyerVideoTrack * videoTrack = nullptr;

        int screenW = 0;
        int screenH = 0;

        int frameIndex = 0;
        int fps = 0;
    };
}

#endif