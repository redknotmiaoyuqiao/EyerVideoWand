#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPAudioRes::EyerVPAudioRes()
    {

    }

    EyerVPAudioRes::~EyerVPAudioRes()
    {

    }

    int EyerVPAudioRes::SetPath(RedString _resPath)
    {
        resPath = _resPath;
        return 0;
    }

    int EyerVPAudioRes::SetStream(int _streamIndex)
    {
        streamIndex = _streamIndex;
        return 0;
    }

    int EyerVPAudioRes::SetPosition(long long startTime)
    {
        position = startTime;
        return 0;
    }

    int EyerVPAudioRes::SetCutter(long long startTime, long long endTime)
    {
        cutterStartTime = startTime;
        cutterEndTime = endTime;
        return 0;
    }

    long long GetDur()
    {
        return 0;
    }
}