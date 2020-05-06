#ifndef	EYER_LIB_AV_WAND_CONTEXT_H
#define	EYER_LIB_AV_WAND_CONTEXT_H

#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerWand.hpp"

namespace Eyer
{
    class EyerWandContext
    {
    public:
        EyerWandContext(int w, int h, int fps);
        ~EyerWandContext();

        int SetGLCtx(EyerGLContextThread * glCtx);

        int RenderFrame(double time);

    private:
        EyerGLContextThread * glCtx = nullptr;

        int width = 0;
        int height = 0;
        int fps = 25;

        Eyer::YUVRenderTask * renderTask = nullptr;

        Eyer::EyerVideoDecoderLine * decoderLine = nullptr;
    };
}

#endif