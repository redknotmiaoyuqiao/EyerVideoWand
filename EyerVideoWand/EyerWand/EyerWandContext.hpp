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
        
        int RenderFrameByIndex(int frameIndex);

        int UpdateScreenWH(int screenW, int screenH);



        int GetLayerCount();
        int GetLayer(EyerVideoLayer & layer, int index);

        int GetFPS();

    private:
        EyerGLContextThread * glCtx = nullptr;

        int width = 0;
        int height = 0;
        int fps = 25;

        int screenW = 0;
        int screenH = 0;

        EyerVideoTrack videoTrack;
        EyerAudioTrack audioTrack;
    };
}

#endif