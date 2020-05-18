#ifndef	EYER_LIB_AV_WAND_RENDER_TASK_H
#define	EYER_LIB_AV_WAND_RENDER_TASK_H

#include "EyerGL/EyerGLRenderTask/EyerGLRenderTask.hpp"
#include "EyerWand/EyerWandAV.hpp"

namespace Eyer {
    class LayerRenderTask : public EyerGLRenderTask
    {
    public:
        LayerRenderTask(EyerVideoLayer & layer);
        ~LayerRenderTask();

        virtual int Render();
        virtual int Init();
        virtual int Destory();

    private:
        EyerVideoLayer layer;
    };
}

#endif