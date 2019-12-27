#include "EyerVideoProcess.hpp"

namespace Eyer
{
    EyerVPAudioRes::EyerVPAudioRes()
    {

    }

    EyerVPAudioRes::EyerVPAudioRes(EyerVPAudioRes & audioRes)
    {
        *this = audioRes;
    }

    EyerVPAudioRes::~EyerVPAudioRes()
    {

    }

    EyerVPAudioRes & EyerVPAudioRes::operator = (EyerVPAudioRes & audioRes)
    {
        resPath = audioRes.resPath;
        streamIndex = audioRes.streamIndex;
        position = audioRes.position;
        cutterStartTime = audioRes.cutterStartTime;
        cutterEndTime = audioRes.cutterEndTime;

        return *this;
    }

    int EyerVPAudioRes::SetPath(EyerString _resPath)
    {
        resPath = _resPath;
        return 0;
    }

    int EyerVPAudioRes::SetStream(int _streamIndex)
    {
        if(_streamIndex < 0){
            _streamIndex = 0;
        }
        streamIndex = _streamIndex;
        return 0;
    }

    int EyerVPAudioRes::SetPosition(long long startTime)
    {
        if(startTime < 0){
            startTime = 0;
        }
        position = startTime;
        return 0;
    }

    int EyerVPAudioRes::SetCutter(long long startTime, long long endTime)
    {
        if(startTime < 0){
            startTime = 0;
        }

        if(endTime < startTime){
            endTime = startTime;
        }
        cutterStartTime = startTime;
        cutterEndTime = endTime;
        return 0;
    }

    long long GetDur()
    {
        return 0;
    }

    EyerString EyerVPAudioRes::GetRes()
    {
        return resPath;
    }

    int EyerVPAudioRes::GetStreamIndex()
    {
        return streamIndex;
    }

    long long EyerVPAudioRes::GetPosition()
    {
        return position;
    }

    long long EyerVPAudioRes::GetCutterStartTime()
    {
        return cutterStartTime;
    }

    long long EyerVPAudioRes::GetCutterEndTime()
    {
        return cutterEndTime;
    }
}
