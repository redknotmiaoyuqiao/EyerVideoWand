#include "EyerWandContext.hpp"
#include "EyerWandAV.hpp"

namespace Eyer
{
    EyerWandContext::EyerWandContext(int w, int h, int _fps)
    {
        width = w;
        height = h;
        fps = _fps;
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
}