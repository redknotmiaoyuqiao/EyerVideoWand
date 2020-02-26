#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragment::EyerVideoFragment()
    {

    }

    EyerVideoFragment::EyerVideoFragment(const EyerVideoFragment & fragment)
    {
        *this = fragment;
    }

    EyerVideoFragment::~EyerVideoFragment()
    {
    }

    EyerVideoFragment & EyerVideoFragment::operator = (const EyerVideoFragment & fragment)
    {
        if(this == &fragment){
            return *this;
        }

        path = fragment.path;
        startIndex = fragment.startIndex;
        endIndex = fragment.endIndex;
        startTime = fragment.startTime;
        endTime = fragment.endTime;

        return *this;
    }

    int EyerVideoFragment::LoadVideoFile(EyerString _path)
    {
        path = _path;
        videoResource.SetPath(path);

        int ret = videoResource.GetVideoDuration(duration);
        if(ret){
            // RedLog("GetVideoDuration Error\n");
        }
        // RedLog("Video Duration:%f\n", duration);

        SetFrameTime(0.0, duration);

        // TODO DEBUG
        /*
        EyerAVFrame frame;
        ret = videoResource.GetVideoFrame(frame, 34.00);
        if(ret){
            EyerLog("Docoder Error");
        }
        EyerLog("Frame TS:%lld\n", frame.GetPTS());
        */

        return 0;
    }

    int EyerVideoFragment::Print()
    {
        RedLog("Video Duration:%f\n", duration);
        RedLog("Start Index: %d, End Index: %d\n", startIndex, endIndex);
        RedLog("Start Time: %f, End Time: %f\n", startTime, endTime);
        return 0;
    }

    double EyerVideoFragment::GetDuration()
    {
        return duration;
    }

    int EyerVideoFragment::SetFrameIndex(int _startIndex, int _endIndex)
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
        return 0;
    }

    int EyerVideoFragment::SetFrameTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }

    EyerString EyerVideoFragment::GetPath()
    {
        // EyerLog("%s\n", path.str);
        return path;
    }
}