#include "WandRenderTask.hpp"
#include "EyerCrop/EyerCrop.hpp"

namespace Eyer
{
    VideoTrackRenderTask::VideoTrackRenderTask(EyerVideoTrack * _videoTrack)
    {
        videoTrack = _videoTrack;
    }

    VideoTrackRenderTask::~VideoTrackRenderTask()
    {

    }

    int VideoTrackRenderTask::Render()
    {
        return 0;
    }

    int VideoTrackRenderTask::Init()
    {
        return 0;
    }
    
    int VideoTrackRenderTask::Destory()
    {
        return 0;
    }
}