#ifndef	EYER_LIB_AV_WAND_CONTEXT_H
#define	EYER_LIB_AV_WAND_CONTEXT_H

#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerWandAV.hpp"

namespace Eyer
{
    class EyerWandContext
    {
    public:
        EyerWandContext(int w, int h, int fps);
        ~EyerWandContext();

        int SetGLCtx(EyerGLContextThread * glCtx);
        int GetFPS();

        int AddFragment2Layer(EyerString layerName, EyerVideoFragment & fragment);
        int AddFragment2Layer(EyerString layerName, EyerVideoFragment & fragment, int startFrameIndex, int endFrameIndex);
    private:
        EyerGLContextThread * glCtx = nullptr;

        int width = 0;
        int height = 0;
        int fps = 25;

        EyerMap<Eyer::EyerString, Eyer::EyerVideoLayer *> layerMap;
    };
}

#endif