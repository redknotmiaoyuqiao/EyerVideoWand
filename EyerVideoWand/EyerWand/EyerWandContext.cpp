#include "EyerWandContext.hpp"

namespace Eyer
{
    EyerWandContext::EyerWandContext(int w, int h, int _fps)
    {
        width = w;
        height = h;
        fps = _fps;

        renderTask = new Eyer::JuliaRenderTask();
    }

    EyerWandContext::~EyerWandContext()
    {
        if(renderTask != nullptr){
            delete renderTask;
            renderTask = nullptr;
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
            glCtx->AddTaskToRenderQueue(renderTask);
        }
    
        return 0;
    }
}