#include "EyerWandContext.hpp"



namespace Eyer
{
    EyerWandContext::EyerWandContext(int w, int h, int _fps)
    {
        width = w;
        height = h;
        fps = _fps;

        renderTask = new Eyer::YUVRenderTask();
        decoderLine = new Eyer::EyerVideoDecoderLine("/storage/emulated/0/ST/time_clock_1min_720x1280_30fps.mp4", 0.0);
    }

    EyerWandContext::~EyerWandContext()
    {
        if(renderTask != nullptr){
            delete renderTask;
            renderTask = nullptr;
        }
        if(decoderLine != nullptr){
            delete decoderLine;
            decoderLine = nullptr;
        }
    }

    int EyerWandContext::SetGLCtx(EyerGLContextThread * _glCtx)
    {
        glCtx = _glCtx;
        glCtx->AddTaskToDestoryQueue(renderTask);

        return 0;
    }

    int EyerWandContext::RenderFrame(double time)
    {
        if(glCtx != nullptr){
            Eyer::EyerAVFrame frame;
            int ret = decoderLine->GetFrame(frame, time);
            if(ret){
                EyerLog("GetFrame Fail: %d\n", ret);
            }
            glCtx->AddTaskToRenderQueue(renderTask);
        }
    
        return 0;
    }
}