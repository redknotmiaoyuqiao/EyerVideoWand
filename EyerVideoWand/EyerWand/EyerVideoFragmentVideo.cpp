#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoFragmentVideo::EyerVideoFragmentVideo()
    {
        
    }

    EyerVideoFragmentVideo::EyerVideoFragmentVideo(const EyerVideoFragmentVideo & fragment)
    {
        *this = fragment;
    }

    EyerVideoFragmentVideo::~EyerVideoFragmentVideo()
    {
        
        if(videoResource != nullptr){
            delete videoResource;
            videoResource = nullptr;
        }
    }

    EyerVideoFragmentVideo & EyerVideoFragmentVideo::operator = (const EyerVideoFragmentVideo & fragment)
    {
        if(this == &fragment){
            return *this;
        }

        path = fragment.path;
        startIndex = fragment.startIndex;
        endIndex = fragment.endIndex;
        startTime = fragment.startTime;
        endTime = fragment.endTime;

        videoResource = nullptr;

        scaleAnimation = fragment.scaleAnimation;
        transAnimation = fragment.transAnimation;

        return *this;
    }

    int EyerVideoFragmentVideo::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        if(videoResource == nullptr){
            videoResource = new EyerWandVideoResource();
            videoResource->SetPath(path);
        }

        return videoResource->GetVideoFrame(avFrame, ts);
    }

    int EyerVideoFragmentVideo::LoadVideoFile(EyerString _path)
    {
        // TODO 验证资源

        path = _path;

        if(videoResource == nullptr){
            videoResource = new EyerWandVideoResource();
        }

        videoResource->SetPath(path);

        EyerLog("Start GetVideoDuration\n");
        int ret = videoResource->GetVideoDuration(duration);
        if(ret){
            EyerLog("GetVideoDuration Error\n");
        }
        EyerLog("End GetVideoDuration\n");
        EyerLog("Video Duration:%f\n", duration);

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

    int EyerVideoFragmentVideo::Print()
    {
        EyerLog("Video Duration:%f\n", duration);
        EyerLog("Start Index: %d, End Index: %d\n", startIndex, endIndex);
        EyerLog("Start Time: %f, End Time: %f\n", startTime, endTime);
        return 0;
    }

    double EyerVideoFragmentVideo::GetDuration()
    {
        return duration;
    }

    int EyerVideoFragmentVideo::SetFrameIndex(int _startIndex, int _endIndex)
    {
        startIndex = _startIndex;
        endIndex = _endIndex;
        return 0;
    }

    int EyerVideoFragmentVideo::SetFrameTime(double _startTime, double _endTime)
    {
        startTime = _startTime;
        endTime = _endTime;
        return 0;
    }

    EyerString EyerVideoFragmentVideo::GetPath()
    {
        // EyerLog("%s\n", path.str);
        return path;
    }


    int EyerVideoFragmentVideo::AddTransKey(double t, float x, float y, float z)
    {
        EyerVideoAnimationKey transAnimationKey(t, x, y, z);
        return transAnimation.AddKey(transAnimationKey);
    }

    int EyerVideoFragmentVideo::AddScaleKey(double t, float x, float y, float z)
    {
        EyerVideoAnimationKey scaleAnimationKey(t, x, y, z);
        return scaleAnimation.AddKey(scaleAnimationKey);
    }

    EyerVideoFragmentType EyerVideoFragmentVideo::GetType() const
    {
        return EyerVideoFragmentType::VIDEO_FRAGMENT_VIDEO;
    }
}