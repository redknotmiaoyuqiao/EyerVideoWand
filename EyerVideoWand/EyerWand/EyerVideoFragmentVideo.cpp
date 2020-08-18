#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragmentVideo::EyerVideoFragmentVideo() : EyerVideoFragment()
    {
        
    }

    EyerVideoFragmentVideo::~EyerVideoFragmentVideo()
    {

    }

    EyerVideoFragmentVideo::EyerVideoFragmentVideo(const EyerVideoFragmentVideo & fragment) : EyerVideoFragmentVideo()
    {
        *this = fragment;
    }

    EyerVideoFragmentVideo & EyerVideoFragmentVideo::operator = (const EyerVideoFragmentVideo & fragment)
    {
        startTime = fragment.startTime;
        endTime = fragment.endTime;

        // videoResource = fragment.videoResource;

        return *this;
    }

    EyerVideoFragmentType EyerVideoFragmentVideo::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO;
    }




    int EyerVideoFragmentVideo::Load(EyerString url)
    {
        videoResource.SetPath(url);

        double duration = 0.0;
        videoResource.GetVideoDuration(duration);

        startTime = 0.0;
        endTime = startTime + duration;

        return 0;
    }

    int EyerVideoFragmentVideo::SetTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;

        if(startTime <= 0.0){
            startTime = 0.0;
        }

        if(endTime <= startTime){
            endTime = startTime;
        }
        return 0;
    }

    int EyerVideoFragmentVideo::PrintInfo()
    {
        return 0;
    }

    int EyerVideoFragmentVideo::GetFrame(EyerAVFrame & frame, double ts)
    {
        return videoResource.GetVideoFrame(frame, ts);
    }
}