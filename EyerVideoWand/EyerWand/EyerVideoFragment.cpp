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
        if(videoResource != nullptr){
            delete videoResource;
            videoResource = nullptr;
        }

        for(int i=0;i<transKeyList.getLength();i++){
            EyerTransKey * transKey = nullptr;
            transKeyList.find(i, transKey);
            if(transKey != nullptr){
                delete transKey;
            }
        }
        transKeyList.clear();
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

        videoResource = nullptr;

        return *this;
    }

    int EyerVideoFragment::GetVideoFrame(EyerAVFrame & avFrame, double ts)
    {
        if(videoResource == nullptr){
            videoResource = new EyerWandVideoResource();
            videoResource->SetPath(path);
        }

        return videoResource->GetVideoFrame(avFrame, ts);
    }

    int EyerVideoFragment::LoadVideoFile(EyerString _path)
    {
        path = _path;

        if(videoResource == nullptr){
            videoResource = new EyerWandVideoResource();
        }

        videoResource->SetPath(path);

        int ret = videoResource->GetVideoDuration(duration);
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


    int EyerVideoFragment::AddTransKey(double t, float x, float y, float z)
    {
        EyerTransKey * transKey = new EyerTransKey();
        transKey->x = x;
        transKey->y = y;
        transKey->z = z;
        transKey->t = t;
        transKeyList.insertBack(transKey);

        return 0;
    }

    int EyerVideoFragment::GetTrans(double t, float & x, float & y, float & z)
    {
        //

        return 0;
    }
}