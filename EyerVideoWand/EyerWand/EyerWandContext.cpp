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
        // TODO 清空 layer map
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

    int EyerWandContext::AddFragment2Layer(EyerString layerName, EyerVideoFragment & fragment)
    {
        EyerVideoLayer * layer = nullptr;
        int ret = layerMap.Find(layerName, layer);
        if(layer == nullptr){
            layer = new EyerVideoLayer();
            layerMap.Insert(layerName, layer);
        }

        EyerLog("Layer Map Size: %d\n", layerMap.Size());

        layer->AddVideoFragment(&fragment);

        return 0;
    }

    int EyerWandContext::AddFragment2Layer(EyerString layerName, EyerVideoFragment & fragment, int startFrameIndex, int endFrameIndex)
    {
        return 0;
    }
}