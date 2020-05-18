#include "WandRenderTask.hpp"

namespace Eyer
{
    LayerRenderTask::LayerRenderTask(EyerVideoLayer & _layer)
    {
        layer = _layer;
    }

    LayerRenderTask::~LayerRenderTask()
    {

    }

    int LayerRenderTask::Render()
    {
        EyerLog("Render\n\n");
        return 0;
    }

    int LayerRenderTask::Init()
    {
        return 0;
    }

    int LayerRenderTask::Destory()
    {
        return 0;
    }
}