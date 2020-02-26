#include "EyerWand.hpp"

namespace Eyer
{
    EyerVideoLayout::EyerVideoLayout()
    {

    }

    EyerVideoLayout::~EyerVideoLayout()
    {
        for(int i=0;i<videoFragmentList.getLength();i++){
            EyerVideoFragment * vf = nullptr;
            videoFragmentList.find(i, vf);
            if(vf != nullptr){
                delete vf;
            }
        }

        videoFragmentList.clear();
    }

    int EyerVideoLayout::SetFrame(int _startFrameIndex, int _endFrameIndex)
    {
        startFrameIndex = _startFrameIndex;
        endFrameIndex = _endFrameIndex;
        return 0;
    }

    EyerVideoLayout::EyerVideoLayout(const EyerVideoLayout & layout)
    {
        *this = layout;
    }

    EyerVideoLayout & EyerVideoLayout::operator = (const EyerVideoLayout & layout)
    {
        if(this == &layout){
            return *this;
        }

        startFrameIndex = layout.startFrameIndex;
        endFrameIndex = layout.endFrameIndex;

        for(int i=0;i<layout.videoFragmentList.getLength();i++){
            EyerVideoFragment * vf = nullptr;
            layout.videoFragmentList.find(i, vf);
            if(vf != nullptr){
                EyerVideoFragment * f = new EyerVideoFragment(*vf);
                videoFragmentList.insertBack(f);
            }
        }

        return *this;
    }

    int EyerVideoLayout::GetStartFrameIndex()
    {
        return startFrameIndex;
    }

    int EyerVideoLayout::GetEndFrameIndex()
    {
        return endFrameIndex;
    }

    int EyerVideoLayout::AddVideoFragment(const EyerVideoFragment & fragment)
    {
        EyerVideoFragment * f = new EyerVideoFragment(fragment);

        videoFragmentList.insertBack(f);

        return 0;
    }

    int EyerVideoLayout::GetVideoFragmentCount()
    {
        return videoFragmentList.getLength();
    }

    int EyerVideoLayout::GetVideoPanel(EyerVideoPanel & panel, int videoFragmentIndex, int layoutFrameIndex, int fps)
    {
        EyerVideoFragment * fragment = nullptr;
        videoFragmentList.find(videoFragmentIndex, fragment);

        if(fragment == nullptr){
            return -1;
        }

        EyerString path = fragment->GetPath();

        EyerWandVideoResource videoResource;
        videoResource.SetPath(path);

        EyerAVFrame avFrame;
        // double ts = 0.0;
        double ts = 1000 * 1.0 / fps * layoutFrameIndex;
        ts = ts / 1000.0;
        // EyerLog("Ts:%f\n", ts);
        int ret = videoResource.GetVideoFrame(avFrame, ts);
        if(ret){
            return -1;
        }

        // avFrame.GetInfo();
        panel.SetData(avFrame);

        return 0;
    }
}