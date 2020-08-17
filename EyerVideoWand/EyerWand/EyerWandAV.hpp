#ifndef	EYER_LIB_AV_EYER_WAND_AV_H
#define	EYER_LIB_AV_EYER_WAND_AV_H

#include "EyerAV/EyerAV.hpp"
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"
#include "EyerVideoTweenAnimation/EyerVideoTweenAnimation.hpp"

#define EYER_WAND_VERSION "EyerWand 1.0.0"


// #ifdef EYER_PLATFORM_ANDROID
#include "EyerGLContext/EyerGLContext.hpp"
#include "EyerVideoLayer.hpp"
// #else
// #include "EyerGLWindow/EyerGLWindow.hpp"
// #include "EyerImg/stb_image.h"
// #define STB_IMAGE_IMPLEMENTATION
// #endif

namespace Eyer {
    class EyerWandDebug;

    class EyerWandDebug
    {
    public:
        static long long DecoderTime;
        static long long RenderTime;
    };
}

#endif
