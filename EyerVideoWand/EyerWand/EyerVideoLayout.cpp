#include "EyerWand.hpp"
#include <math.h>

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

        EyerAVFrame avFrame;
        // double ts = 0.0;
        double ts = 1000 * 1.0 / fps * (layoutFrameIndex);
        ts = ts / 1000.0;
        // EyerLog("Ts:%f\n", ts);
        int ret = fragment->GetVideoFrame(avFrame, ts);
        if(ret){
            return -1;
        }

        // avFrame.GetInfo();
        panel.SetData(avFrame);

        EyerMat4x4 ortho;
        int width = 1920;
        int height = 1080;
        ortho.SetOrtho(- width / 2.0, width / 2.0, height / 2.0, - height / 2.0, 0.0f, 1000.0f);
        // ortho.SetOrtho(0.0, width, 0.0, - height, 0.0f, 1000.0f);

        EyerMat4x4 scale;
        scale.SetScale(width / 2.0, height / 2.0, 0.0);

        EyerMat4x4 trans;

        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
        fragment->GetTrans(ts, x, y, z);
        trans.SetTrans(x, y, z);

        panel.mvp = ortho * trans * scale ;
        // panel.mvp.SetTrans(0.03 * sinf(layoutFrameIndex * 1.0f), 0.0, 0.0);

        return 0;
    }
}